#include "ExercisePanelImp.h"
#include "ApplicationImages.h"
#include "GlobalConstants.h"
#include "MyApp.h"
#include <wx/app.h> 
#include <wx/log.h> 
#include "DictationOverlayDialogImp.h"
#include "DictationOverlayClientHelper.h"
#include "SAConfirmDialogImp.h"
#include "ActionCommandParser.h"
#include "SAConfirmDialogImp.h"

ExercisePanelImp::ExercisePanelImp( wxWindow* parent, Publication* publication )
:
ExercisePanel( parent ), viewModel(publication)
{

}

/* called when editing an existing quiz */
ExercisePanelImp::ExercisePanelImp(wxWindow* parent, Publication* publication, Quiz* quiz) :
	ExercisePanel(parent), viewModel(publication, quiz->GetQuizId())
{

}

void ExercisePanelImp::SetupSpeechHandlers()
{
	std::vector<std::wstring> ruleNames;
	ruleNames.push_back(MyApp::RULE_EXERCISE_DIALOG);
	ruleNames.push_back(MyApp::RULE_DIALOG_ACTIONS);

	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	boost::signals2::connection* commandConnection = wxGetApp().GetCommandReceivedConnection();
	*(commandConnection) = wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->onCommandRecognized(boost::bind(&ExercisePanelImp::OnCommandRecognized, this, _1, _2));
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->EnableRules(ruleNames);
}


void ExercisePanelImp::OnCommandRecognized(std::wstring& phrase, const std::vector<CommandProperty>& commandPropertyList)
{
	std::wstring actionName;
	std::wstring actionTarget;
	std::wstring targetValue;
	std::wstring ruleName;
	ActionCommandParser actionParser;
	actionParser.Parse(commandPropertyList, actionName, actionTarget, targetValue, ruleName);

	if (boost::algorithm::equals(actionName, MyApp::COMMAND_ACTION_CANCEL))
	{
		this->Close();
		return;
	}
	else if (boost::algorithm::equals(actionName, MyApp::CONTROL_ACTION_CLEAR))
	{
		if (this->txtName->HasFocus())
		{
			this->txtName->Clear();
		}
		return;
	}
	else if (boost::algorithm::equals(actionName, L"addquestion"))
	{
		AddQuestion();
		return;
	}
	else if (boost::algorithm::equals(actionName, L"deletequestion"))
	{
		DeleteQuestion();
		return;
	}
}



ExercisePanelImp::~ExercisePanelImp()
{
	wxGetApp().DisconnectSpeechHandler(wxGetApp().GetCommandReceivedConnection());
	wxGetApp().GetSpeechListener().GetSpeechRecognitionContext()->Disable();
}

void ExercisePanelImp::AddQuestion()
{
	viewModel.ResetNewQuestion();
	viewModel.SetCurrentQuestion(&viewModel.GetNewQuestion());
	RenderCurrentQuestion();
	RecordQuestion();
}

void ExercisePanelImp::RecordQuestion()
{
	std::wstring filePathBuffer(L"");
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(viewModel.GetCurrentQuestion()->GetQuestionFile(), this, questionText, &playerQuestion, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		viewModel.GetCurrentQuestion()->SetQuestionFile(filePathBuffer);
		RecordAnswer();
	}
}

void ExercisePanelImp::RecordAnswer()
{
	std::wstring filePathBuffer(L"");
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(viewModel.GetCurrentQuestion()->GetAnswer()->GetAnswerFile(), this, answerText, &playerAnswer, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		viewModel.GetCurrentQuestion()->GetAnswer()->SetAnswerFile(filePathBuffer);
		//lets auto save this question
		Update();
	}
}

void ExercisePanelImp::Update()
{
	/* called by the apply button */
	if (ValidateQuiz())
	{
		viewModel.GetQuiz().SetName(txtName->GetValue().ToStdWstring());
		if (cboTopics->GetSelection() > 0)
		{
			Topic* topic = reinterpret_cast<Topic*>(cboTopics->GetClientData(cboTopics->GetSelection()));
			if (topic != nullptr)
			{
				viewModel.GetQuiz().SetTopicId(topic->getTopicId());
			}
		}

		if (!viewModel.GetQuiz().IsNew())
		{
			wxGetApp().GetProvider()->GetQuizProvider().Update(&viewModel.GetQuiz());
		}
		else
		{
			wxGetApp().GetProvider()->GetQuizProvider().Insert(&viewModel.GetQuiz());
		}
	}
	else
	{
		//alert the user to the validation error, no name set for quiz
		txtName->SetFocus();
		return;
	}

	//if currentquestion null and data entered correctly then just create a new question
	if (viewModel.GetCurrentQuestion() == nullptr)
	{
		return;
	}

	if (ValidateQuestion())
	{
		//insert or update the current question
		BindQuestion();
		if (viewModel.GetCurrentQuestion()->GetQuestionId() > 0)
		{
			wxGetApp().GetProvider()->GetQuizProvider().Update(viewModel.GetCurrentQuestion());
		}
		else
		{
			Question* newQuestion = new Question(viewModel.GetNewQuestion());
			newQuestion->SetQuizId(viewModel.GetQuiz().GetQuizId());
			viewModel.SetCurrentQuestion(newQuestion);
			wxGetApp().GetProvider()->GetQuizProvider().Insert(viewModel.GetCurrentQuestion());
			viewModel.GetQuestionList()->push_back(viewModel.GetCurrentQuestion());
		}
		RenderQuestions();
	}
}

void ExercisePanelImp::RenderQuiz()
{
	txtName->SetValue(viewModel.GetQuiz().GetName());
	viewModel.GetQuiz().SetDirty(false);
}

void ExercisePanelImp::RenderTopics()
{
	cboTopics->Clear();
	cboTopics->Append(wxString(L""));
	for (int i = 0; i < viewModel.GetTopicList()->size(); i++)
	{
		Topic topic = viewModel.GetTopicList()->at(i);
		int index = cboTopics->Append(wxString(topic.getName()), &topic);
		if (viewModel.GetQuiz().GetTopicId() > 0)
		{
			if (topic.getTopicId() == viewModel.GetQuiz().GetTopicId())
			{
				cboTopics->SetSelection(index);
			}
		}
	}
}

void ExercisePanelImp::RenderQuestions()
{
	/* renders the list of questions */
	lstQuestions->DeleteAllItems();
	wxVector<wxVariant> data;
	for (int i = 0; i < viewModel.GetQuestionList()->size(); i++)
	{
		Question question = viewModel.GetQuestionList()->at(i);
		unsigned long questionId = question.GetQuestionId();
		std::wstring title = question.GetLimitedQuestionText();
		if (title.empty())
		{
			title = ::NULL_LIST_INDICATOR;
		}
		data.push_back(wxVariant(boost::lexical_cast<std::wstring>(i)));
		data.push_back(wxVariant(title));
		std::wstring answerText = question.GetAnswer()->GetShortAnswerText();
		data.push_back(wxVariant(answerText));
		lstQuestions->AppendItem(data, wxUIntPtr(&viewModel.GetQuestionList()->at(i)));
		data.clear();
		if (viewModel.GetCurrentQuestion() != nullptr && (question.GetQuestionId() == viewModel.GetCurrentQuestion()->GetQuestionId()))
		{
			lstQuestions->SelectRow(i);
		}

	}

}

void ExercisePanelImp::RenderCurrentQuestion()
{

	if (viewModel.GetCurrentQuestion() == nullptr)
	{
		playerQuestion.Clear();
		playerAnswer.Clear();
		questionText->Clear();
		answerText->Clear();
		return;
	}
	EnableQuestion();
	if (!viewModel.GetCurrentQuestion()->GetQuestionFile().empty())
	{
		//playerQuestion.SetURL(wxGetApp().GetFileHandler().GetFullAudioPathToFile(viewModel.GetCurrentQuestion()->GetQuestionFile()));
		playerQuestion.SetURLAsync(wxGetApp().GetFileHandler().GetFullAudioPathToFile(viewModel.GetCurrentQuestion()->GetQuestionFile()));
	}
	if (!viewModel.GetCurrentQuestion()->GetAnswer()->GetAnswerFile().empty())
	{
		playerAnswer.SetURLAsync(wxGetApp().GetFileHandler().GetFullAudioPathToFile(viewModel.GetCurrentQuestion()->GetAnswer()->GetAnswerFile()));
	}

	/* puts the values in the storage variables for question gui fields */
	questionText->SetValue(viewModel.GetCurrentQuestion()->GetQuestionText());

	/* puts the values in the storage variables for answer gui fields */
	answerText->SetValue(viewModel.GetCurrentQuestion()->GetAnswer()->GetAnswerText());
	viewModel.GetCurrentQuestion()->SetDirty(false);
	viewModel.GetCurrentQuestion()->GetAnswer()->SetDirty(false);
}


bool ExercisePanelImp::ValidateQuiz()
{
	if (txtName->GetValue().empty())
	{
		quizMessage->ShowMessage("You need to enter a Name for this Exercise");
		return false;
	}
	return true;
}

bool ExercisePanelImp::ValidateQuestion()
{
	bool returnValue;
	returnValue = true;
	if (viewModel.GetCurrentQuestion()->GetQuestionFile().empty() && viewModel.GetCurrentQuestion()->GetQuestionText().empty())
	{
		questionMessage->ShowMessage("You need to record the Question audio");
		returnValue = false;
	}
	if (viewModel.GetCurrentQuestion()->GetAnswer()->GetAnswerFile().empty() && viewModel.GetCurrentQuestion()->GetAnswer()->GetAnswerText().empty())
	{
		answerMessage->ShowMessage("You need to record the Answer audio");
		returnValue = false;
	}
	return returnValue;
}

bool ExercisePanelImp::SaveCheck()
{
	/* return false from this method if the triggering event
	such as clicking new button, edit, etc should be cancelled 
	because there are unsaved changes that couldn't be saved due to 
	validation errors
	*/
	if (viewModel.GetCurrentQuestion() == nullptr)
	{
		return true;
	}
	/* if question dirty and is valid then do auto save otherwise ask to discard changes */
	BindQuestion();
	if (viewModel.GetCurrentQuestion()->GetDirty() || viewModel.GetCurrentQuestion()->GetAnswer()->GetDirty())
	{
		if (ValidateQuestion() && ValidateQuiz())
		{
			Update();
			return true;
		}
		else
		{
			//question has errors would you like to discard changes
			SAConfirmDialogImp confirm(this);
			if (confirm.ShowModal() == wxYES)
			{
				return true;
			}
			else
			{
				//changes will be discarded
				return false;
			}
		}
	}
	return true;
}

void ExercisePanelImp::BindQuestion()
{
	viewModel.GetCurrentQuestion()->SetQuestionText(questionText->GetValue().ToStdWstring());
	viewModel.GetCurrentQuestion()->GetAnswer()->SetAnswerText(answerText->GetValue().ToStdWstring());
}

void ExercisePanelImp::DisableQuestion()
{
	questionText->Disable();
	answerText->Disable();
	btnRecordAnswer->Disable();
	btnClearAnswer->Disable();
	btnRecordQuestion->Disable();
	btnClearQuestion->Disable();
}

void ExercisePanelImp::EnableQuestion()
{
	questionText->Enable();
	answerText->Enable();
	btnRecordAnswer->Enable();
	btnClearAnswer->Enable();
	btnRecordQuestion->Enable();
	btnClearQuestion->Enable();
}

void ExercisePanelImp::ExercisePanelOnInitDialog( wxInitDialogEvent& event )
{
	btnAddQuestion->SetBitmap(*wxGetApp().GetImages().add_icon);
	btnDeleteQuestion->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnRecordQuestion->SetBitmap(*wxGetApp().GetImages().record_icon);
	btnClearAnswer->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnClearQuestion->SetBitmap(*wxGetApp().GetImages().delete_icon);
	btnRecordAnswer->SetBitmap(*wxGetApp().GetImages().record_icon);
	/* init the audio player and record modals for question and answer audio */
	playerPanelQuestion = new AudioPlayerPanelImp(pnlQuestionAudioPlayer, &playerQuestion);
	playerPanelAnswer = new AudioPlayerPanelImp(pnlAnswerAudioPlayer, &playerAnswer);
	wxSizerItem* panelQ = this->szQuestionAudioPlayer->Add(playerPanelQuestion, 1, wxALL | wxEXPAND, 0);
	wxSizerItem* panelA = this->szAnswerAudioPlayer->Add(playerPanelAnswer, 1, wxALL | wxEXPAND, 0);
	/*
	szAnswerAudioPlayer->Layout();
	szQuestionAudioPlayer->Layout();
	sizerAnswerHeader->Layout();
	sizerQuestionHeader->Layout();
	sizerEdit->Layout();
	*/

	if (!viewModel.GetQuiz().IsNew())
	{
		//load the quiz first time up
		wxGetApp().GetProvider()->GetQuizProvider().GetQuizById(viewModel.GetQuiz().GetQuizId(), &viewModel.GetQuiz());
		wxGetApp().GetProvider()->GetQuizProvider().GetQuestionsByQuiz(&viewModel.GetQuiz(), viewModel.GetQuestionList());
		DisableQuestion();
	}
	else
	{
		//go into new mode immediately
		viewModel.SetCurrentQuestion(new Question());
		EnableQuestion();
	}
	wxGetApp().GetProvider()->GetTopicsByPublication(viewModel.GetPublication(), viewModel.GetTopicList());

	RenderQuiz();
	RenderTopics();
	RenderQuestions();
	RenderCurrentQuestion();
	SetupSpeechHandlers();
	this->Layout();

}



void ExercisePanelImp::NameOnKillFocus( wxFocusEvent& event )
{
	event.Skip();
}

void ExercisePanelImp::NameOnSetFocus( wxFocusEvent& event )
{
	event.Skip();
}

void ExercisePanelImp::NameOnText(wxCommandEvent& event)
{
	viewModel.GetQuiz().SetDirty(true);
}

void ExercisePanelImp::AddQuestionOnButtonClick( wxCommandEvent& event )
{
	AddQuestion();
}

void ExercisePanelImp::DeleteQuestion()
{
	if (viewModel.GetCurrentQuestion() == nullptr)
	{
		return;
	}

	SAConfirmDialogImp confirmDlg(this);
	if (confirmDlg.ShowModal() == wxYES)
	{
		wxGetApp().GetProvider()->GetQuizProvider().Delete(viewModel.GetCurrentQuestion());
		boost::ptr_vector<Question>* list = viewModel.GetQuestionList();
		list->erase(std::find(list->begin(), list->end(), *viewModel.GetCurrentQuestion()));
		viewModel.SetCurrentQuestion(nullptr);
		RenderQuestions();
		RenderCurrentQuestion();
	}
	SetupSpeechHandlers();
}

void ExercisePanelImp::DeleteQuestionOnButtonClick( wxCommandEvent& event )
{
	DeleteQuestion();
}

void ExercisePanelImp::DeleteQuestionOnUpdateUI( wxUpdateUIEvent& event )
{
	if (viewModel.GetCurrentQuestion() != nullptr)
	{
		btnDeleteQuestion->Enable();
	}
	else
	{
		btnDeleteQuestion->Disable();
	}
}

void ExercisePanelImp::QuestionsSelectionChanged( wxDataViewEvent& event )
{
	if (!SaveCheck())
	{
		event.Veto();
		return;
	}
	wxUIntPtr data = lstQuestions->GetItemData(event.GetItem());
	Question* question = reinterpret_cast<Question*>(data);
	if (question != nullptr)
	{
		viewModel.SetCurrentQuestion(question);
		RenderCurrentQuestion();
	}
}

void ExercisePanelImp::RecordQuestionOnButtonClick( wxCommandEvent& event )
{
	RecordQuestion();
}

void ExercisePanelImp::ClearQuestionOnButtonClick( wxCommandEvent& event )
{

}

void ExercisePanelImp::RecordAnswerOnButtonClick( wxCommandEvent& event )
{
	RecordAnswer();
}

void ExercisePanelImp::ClearAnswerOnButtonClick( wxCommandEvent& event )
{
// TODO: Implement ClearAnswerOnButtonClick
}

void ExercisePanelImp::ApplyOnButtonClick( wxCommandEvent& event )
{
	Update();
}

void ExercisePanelImp::CancelOnButtonClick( wxCommandEvent& event )
{
	RenderQuiz();
	RenderQuestions();
	RenderCurrentQuestion();
}

void ExercisePanelImp::CancelOnUpdateUI(wxUpdateUIEvent& event)
{
	if (viewModel.IsDirty())
	{
		btnCancel->Enable();
	}
	else
	{
		btnCancel->Disable();
	}
}

void ExercisePanelImp::ApplyOnUpdateUI(wxUpdateUIEvent& event)
{
	if (viewModel.IsDirty())
	{
		btnApply->Enable();
	}
	else
	{
		btnApply->Disable();
	}
}

void ExercisePanelImp::TopicsOnCombobox(wxCommandEvent& event)
{
	viewModel.GetQuiz().SetDirty(true);
}

void ExercisePanelImp::QuestionOnText(wxCommandEvent& event)
{
	if (viewModel.GetCurrentQuestion() != nullptr)
	{
		viewModel.GetCurrentQuestion()->SetDirty(true);
	}
}

void ExercisePanelImp::AnswerOnText(wxCommandEvent& event)
{
	if (viewModel.GetCurrentQuestion() != nullptr)
	{
		viewModel.GetCurrentQuestion()->GetAnswer()->SetDirty(true);
	}
}



