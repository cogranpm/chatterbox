#include "ExerciseRunDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "AudioPlayerPanelImp.h"
#include "DictationOverlayClientHelper.h"


bool IsCorrect(QuizRunQuestion& question) {
	return question.GetIsCorrect();
}


struct findQuizRunQuestionByQuestionId
{
	findQuizRunQuestionByQuestionId(unsigned long id) : _id(id) {};
	const unsigned long _id;

	bool operator () (QuizRunQuestion& arg) const
	{
		return (_id == arg.GetQuestion().GetQuestionId());
	}
};

/*
ExerciseRunDialogImp::ExerciseRunDialogImp( wxWindow* parent, unsigned long quizId)
:
ExerciseRunDialog( parent ), viewModel(quizId), questionPlayer(playPanel, this), answerPlayer(this, std::wstring(L"")), correctAnswerPlayer(this, std::wstring(L""))
{
	Init();
}

ExerciseRunDialogImp::ExerciseRunDialogImp(wxWindow* parent, QuizRunHeader& quizRunHeader) :
	ExerciseRunDialog(parent), viewModel(quizRunHeader), questionPlayer(playPanel, this), answerPlayer(this, std::wstring(L"")), correctAnswerPlayer(this, std::wstring(L""))
{
	Init();
}
*/


ExerciseRunDialogImp::ExerciseRunDialogImp(wxWindow* parent, unsigned long quizId)
	:
	ExerciseRunDialog(parent), viewModel(quizId),
	playerAnswer(), playerCorrectAnswer(), playerPanelAnswer(nullptr), playerPanelCorrectAnswer(nullptr),
	playerQuestion(), playerPanelQuestion(nullptr)
{
	Init();
}

ExerciseRunDialogImp::ExerciseRunDialogImp(wxWindow* parent, QuizRunHeader& quizRunHeader) :
	ExerciseRunDialog(parent), viewModel(quizRunHeader), 
	playerAnswer(), playerCorrectAnswer(), playerPanelAnswer(nullptr), playerPanelCorrectAnswer(nullptr),
	playerQuestion(), playerPanelQuestion(nullptr)
{
	Init();
}


void ExerciseRunDialogImp::Init()
{

}

void ExerciseRunDialogImp::CloseOnButtonClick( wxCommandEvent& event )
{
	this->Close();
}

void ExerciseRunDialogImp::RecordOnButtonClick(wxCommandEvent& event)
{
	/* show the record dialog */
	std::wstring filePathBuffer(L"");
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(currentQuestion->GetAnswerFile(), this, txtAnswer, nullptr, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		currentQuestion->SetAnswerFile(filePathBuffer);
		currentQuestion->SetAnswerText(txtAnswer->GetValue().ToStdWstring());
		rdoEvaluation->Enable();
		btnNext->Enable();
		//playerPanelAnswer->Show(true);
		playerPanelAnswer->Enable(true);
		playerPanelCorrectAnswer->Enable(true);
		playerAnswer.SetURL(currentQuestion->GetAnswerFile());
		playerCorrectAnswer.SetURL(currentQuestion->GetQuestion().GetAnswer()->GetAnswerFile());
		txtCorrectAnswer->SetValue(currentQuestion->GetQuestion().GetAnswer()->GetAnswerText());
	}
}


void ExerciseRunDialogImp::SkipOnButtonClick(wxCommandEvent& event)
{
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	currentQuestion->SetIsAnswered(false);
	bool retValue = Save();
	GoNextQuestion();
}


void ExerciseRunDialogImp::EvaluationOnRadioBox(wxCommandEvent& event)
{

}

void ExerciseRunDialogImp::NextOnButtonClick(wxCommandEvent& event)
{
	bool updateResult = Save();
	if (!updateResult)
	{
		event.Skip();
	}
	else
	{
		GoNextQuestion();
	}
}

void ExerciseRunDialogImp::QuestionsSelectionChanged(wxDataViewEvent& event)
{
	wxDataViewItem item = lstQuestions->GetSelection();
	if (item.IsOk())
	{
		wxUIntPtr data = lstQuestions->GetItemData(item);
		QuizRunQuestion* foundItem = FindSelectedQuizRunQuestion(data);
		if (foundItem != nullptr)
		{
			int indexSelected = lstQuestions->GetSelectedRow();
			viewModel.SetCurrentQuestionIndex(indexSelected + 1);
			SetQuestion(*foundItem);
			HideComplete();
		}
	}
}

QuizRunQuestion* ExerciseRunDialogImp::FindSelectedQuizRunQuestion(long questionId)
{
	boost::ptr_vector<QuizRunQuestion>::iterator it = std::find_if(viewModel.GetRunQuestions().begin(),
		viewModel.GetRunQuestions().end(),
		findQuizRunQuestionByQuestionId(questionId));

	if (it != viewModel.GetRunQuestions().end())
	{
		size_t index = std::distance(viewModel.GetRunQuestions().begin(), it);
		return &viewModel.GetRunQuestions().at(index);
	}
	else
	{
		return nullptr;
	}
}


void ExerciseRunDialogImp::OnInitDialog(wxInitDialogEvent & event)
{
	deleteIcon.CopyFromBitmap(*wxGetApp().GetImages().delete_icon);
	//SetIcon(wxIcon(deleteIcon));
	
	taskCompleteIcon.CopyFromBitmap(*wxGetApp().GetImages().taskcomplete_icon);
	taskRejectIcon.CopyFromBitmap(*wxGetApp().GetImages().taskreject_icon);

	btnRecord->SetBitmap(*wxGetApp().GetImages().record_icon);
	btnNext->SetBitmap(*wxGetApp().GetImages().next_icon);
//	btnAudioPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	//btnPlayAnswer->SetBitmap(*wxGetApp().GetImages().start_icon);
	//btnPlayCorrectAnswer->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnSkip->SetBitmap(*wxGetApp().GetImages().next_icon);

	
	playerPanelQuestion = new AudioPlayerPanelImp(pnlPlayer, &playerQuestion);
	playerPanelCorrectAnswer = new AudioPlayerPanelImp(pnlCorrectAnswerPlayer, &playerCorrectAnswer);
	playerPanelAnswer = new AudioPlayerPanelImp(pnlAnswerPlayer, &playerAnswer);
	wxSizerItem* panelQ = this->szCorrectAnswerPlayer->Add(playerPanelCorrectAnswer, 1, wxALL | wxEXPAND, 0);
	wxSizerItem* panelA = this->szAnswerPlayer->Add(playerPanelAnswer, 1, wxALL | wxEXPAND, 0);
	wxSizerItem* panelB = this->szPlayer->Add(playerPanelQuestion, 1, wxALL | wxEXPAND, 0);

	
	/* load the data */
	if (viewModel.GetHeader().GetQuizRunHeaderId() > 0)
	{
		wxGetApp().GetProvider()->GetQuizProvider().GetQuizRunQuestionsByQuiz(viewModel.GetHeader().GetQuizId(), viewModel.GetHeader().GetQuizRunHeaderId(),
			&viewModel.GetRunQuestions());
	}
	else
	{
		wxGetApp().GetProvider()->GetQuizProvider().GetQuestionsByQuizId(viewModel.GetHeader().GetQuizId(), &viewModel.GetQuestions());
		viewModel.CreateRunQuestions();
	}
	size_t siz = viewModel.GetQuestions().size();
	RenderQuestions();

	if (viewModel.GetHeader().GetQuizRunHeaderId() > 0)
	{
		ShowComplete();
		return;
	}

	if (viewModel.GetRunQuestions().size() > 0)
	{
		viewModel.SetCurrentQuestionIndex(1);
		lstQuestions->SelectRow(0);
		SetQuestion(viewModel.GetRunQuestions().at(0));
		PlayQuestion();
	}

	this->Layout();
}

void ExerciseRunDialogImp::PlayQuestion()
{
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	playerQuestion.SetURLAsync(currentQuestion->GetQuestion().GetQuestionFile());
	//playerQuestion.Play();
//	questionPlayer.SetURL(currentQuestion->GetQuestion().GetQuestionFile());
//	questionPlayer.Play();
}

void ExerciseRunDialogImp::RenderQuestions()
{
	wxVector<wxVariant> data;
	lstQuestions->DeleteAllItems();
	for (int i = 0; i < viewModel.GetRunQuestions().size(); i++)
	{
		//	wxVariant temp;
		//	temp << wxDataViewIconText(L"", limeIcon);
		QuizRunQuestion question = viewModel.GetRunQuestions().at(i);
		data.push_back(wxVariant(boost::lexical_cast<std::wstring>(i)));
		data.push_back(wxVariant(question.GetQuestion().GetLimitedQuestionText()));
		//answered
		if (viewModel.IsAnswered(&question))
		{
			data.push_back(wxVariant(wxDataViewIconText(L"Yes", taskCompleteIcon)));
		}
		else
		{
			data.push_back(wxVariant(wxDataViewIconText(L"No", taskRejectIcon)));
		}
		//result
		if (question.GetIsCorrect())
		{
			data.push_back(wxVariant(wxDataViewIconText(L"Correct", taskCompleteIcon)));
		}
		else
		{
			data.push_back(wxVariant(wxDataViewIconText(L"Incorrect", taskRejectIcon)));
		}
		lstQuestions->AppendItem(data, question.GetQuestion().GetQuestionId());
		data.clear();
	}
}




void ExerciseRunDialogImp::SetQuestion(QuizRunQuestion& question)
{
	txtQuestion->SetValue(question.GetQuestion().GetQuestionText());
	int index = viewModel.GetCurrentQuestionIndex();
	size_t total = viewModel.GetRunQuestions().size();
	std::wstring sTotal = boost::lexical_cast<std::wstring>(total);
	this->lblStatus->SetLabelText(wxString::Format(L"Question %d of %s", index, sTotal));
	if (question.GetIsAnswered())
	{
		/* reviewing */
		btnRecord->Disable();
		//playerPanelAnswer->Show(true);
		playerPanelAnswer->Enable(true);
		playerPanelCorrectAnswer->Enable(true);
		btnNext->Enable();
		if (question.GetIsCorrect())
		{
			rdoEvaluation->Select(0);
		}
		else
		{
			rdoEvaluation->Select(1);
		}
		rdoEvaluation->Disable();
	}
	else
	{
		btnRecord->Enable();
		//playerPanelAnswer->Show(false);
		playerPanelAnswer->Disable();
		playerPanelCorrectAnswer->Disable();
		btnNext->Disable();
		rdoEvaluation->Select(0);
	}
}

//void ExerciseRunDialogImp::PlayCompleted()
//{
//
//}

bool ExerciseRunDialogImp::Save()
{
	QuizRunQuestion* question = viewModel.GetCurrentQuestion();
	question->SetIsCorrect(rdoEvaluation->GetSelection() == 0);
	question->SetIsAnswered(true);
	if (!Validate())
	{
		return false;
	}

	if (!(viewModel.GetHeader().GetQuizRunHeaderId() > 0))
	{
		wxGetApp().GetProvider()->GetQuizProvider().Insert(viewModel.GetHeader());
	}
	question->SetQuizRunHeaderId(viewModel.GetHeader().GetQuizRunHeaderId());
	if (question->GetQuizRunQuestionId() > 0)
	{
		//no updates of questions allowed
		//wxGetApp().GetProvider()->GetQuizProvider().Update(*question);
	}
	else
	{
		wxGetApp().GetProvider()->GetQuizProvider().Insert(*question);
	}
	return true;
}

bool ExerciseRunDialogImp::Validate()
{
	QuizRunQuestion* question = viewModel.GetCurrentQuestion();
	/* need answer text or answer file */
	if (question->GetAnswerFile().empty() && question->GetAnswerText().empty())
	{
		return false;
	}
	return true;
}

void ExerciseRunDialogImp::GoNextQuestion()
{
	if (MoreQuestions())
	{
		int nextQuestionIndex = viewModel.GetCurrentQuestionIndex() + 1;
		viewModel.SetCurrentQuestionIndex(nextQuestionIndex);
		RenderQuestions();
		lstQuestions->SelectRow(viewModel.GetCurrentQuestionIndex() - 1);
		SetQuestion(*viewModel.GetCurrentQuestion());
		if (!viewModel.GetCurrentQuestion()->GetIsAnswered())
		{
			PlayQuestion();
		}
	}
	else
	{
		RenderComplete();
	}
}


void ExerciseRunDialogImp::RenderComplete()
{
	/* update the questions */
	RenderQuestions();

	/* if none have been skipped then save the header */
	viewModel.GetHeader().SetIsComplete(true);
	wxGetApp().GetProvider()->GetQuizProvider().Update(viewModel.GetHeader());
	
	int correctCount = std::count_if(viewModel.GetRunQuestions().begin(), viewModel.GetRunQuestions().end(), IsCorrect);
	
	wxString score(L"Score: ");
	score.Append(wxString::Format(wxT("%i"), correctCount));
	score.Append(L" / ");
	int total = boost::lexical_cast<int>(viewModel.GetRunQuestions().size());
	score.Append(wxString::Format(wxT("%i"), total));
	double percent = (((double)correctCount / (double)total)) * 100.0;
	score.Append(L" ");
	score.Append(wxString::Format(wxT("%.2f"), percent));
	score.Append(L"%");
	lblScore->SetLabelText(score);
	ShowComplete();
}

void ExerciseRunDialogImp::ShowComplete()
{
	mainDisplayBook->ChangeSelection(1);
}


void ExerciseRunDialogImp::HideComplete()
{
	mainDisplayBook->ChangeSelection(0);
}

bool ExerciseRunDialogImp::MoreQuestions()
{
	return (viewModel.GetCurrentQuestionIndex()) < viewModel.GetRunQuestions().size();
}


bool ExerciseRunDialogImp::IsFirstQuestion()
{
	return viewModel.GetCurrentQuestionIndex() == 1;
}
