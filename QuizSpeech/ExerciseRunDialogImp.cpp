#include "ExerciseRunDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "AudioPlayerPanelImp.h"
#include "DictationOverlayClientHelper.h"


ExerciseRunDialogImp::ExerciseRunDialogImp( wxWindow* parent, unsigned long quizId)
:
ExerciseRunDialog( parent ), viewModel(quizId), questionPlayer(this, std::wstring(L"")), answerPlayer(this, std::wstring(L"")), correctAnswerPlayer(this, std::wstring(L""))
{
	Init();
}

ExerciseRunDialogImp::ExerciseRunDialogImp(wxWindow* parent, QuizRunHeader& quizRunHeader) :
	ExerciseRunDialog(parent), viewModel(quizRunHeader), questionPlayer(this, std::wstring(L"")), answerPlayer(this, std::wstring(L"")), correctAnswerPlayer(this, std::wstring(L""))
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
		btnPlayAnswer->Enable();
		btnPlayCorrectAnswer->Enable();
	}
}

void ExerciseRunDialogImp::AudioPlayOnButtonClick(wxCommandEvent& event)
{
	/* play the question audio */
	PlayQuestion();
}

void ExerciseRunDialogImp::PlayAnswerOnButtonClick(wxCommandEvent& event)
{
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	answerPlayer.SetURL(currentQuestion->GetAnswerFile());
	answerPlayer.Play();
}

void ExerciseRunDialogImp::SkipOnButtonClick(wxCommandEvent& event)
{
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	currentQuestion->SetIsAnswered(false);
	bool retValue = Save();
	GoNextQuestion();
}

void ExerciseRunDialogImp::PlayCorrectAnswerOnButtonClick(wxCommandEvent& event)
{
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	correctAnswerPlayer.SetURL(currentQuestion->GetQuestion().GetAnswer()->GetAnswerFile());
	correctAnswerPlayer.Play();
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
	wxDataViewItem item = event.GetItem();
	if (item == nullptr)
	{
		return;
	}
	QuizRunQuestion* question = (QuizRunQuestion*)this->lstQuestions->GetItemData(item);

	viewModel.SetCurrentQuestionIndex(event.GetSelection());
	this->lblStatus->SetLabelText(wxString::Format(L"Question %i of %i", viewModel.GetCurrentQuestionIndex(), viewModel.GetRunQuestions().size()));
	SetQuestion(*question);
	HideComplete();
}


void ExerciseRunDialogImp::OnInitDialog(wxInitDialogEvent & event)
{
	deleteIcon.CopyFromBitmap(*wxGetApp().GetImages().delete_icon);
	//SetIcon(wxIcon(deleteIcon));
	
	taskCompleteIcon.CopyFromBitmap(*wxGetApp().GetImages().taskcomplete_icon);
	taskRejectIcon.CopyFromBitmap(*wxGetApp().GetImages().taskreject_icon);


	btnRecord->SetBitmap(*wxGetApp().GetImages().record_icon);
	btnNext->SetBitmap(*wxGetApp().GetImages().next_icon);
	btnAudioPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnPlayAnswer->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnPlayCorrectAnswer->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnSkip->SetBitmap(*wxGetApp().GetImages().next_icon);

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
		viewModel.SetCurrentQuestionIndex(0);
		lstQuestions->SelectRow(viewModel.GetCurrentQuestionIndex());
		SetQuestion(viewModel.GetRunQuestions().at(viewModel.GetCurrentQuestionIndex()));
		PlayQuestion();
	}

}

void ExerciseRunDialogImp::PlayQuestion()
{
	QuizRunQuestion* currentQuestion = viewModel.GetCurrentQuestion();
	questionPlayer.SetURL(currentQuestion->GetQuestion().GetQuestionFile());
	questionPlayer.Play();
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
		if (viewModel.IsAnswered())
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
			data.push_back(wxVariant(wxDataViewIconText(L"Yes", taskCompleteIcon)));
		}
		else
		{
			data.push_back(wxVariant(wxDataViewIconText(L"No", taskRejectIcon)));
		}
		lstQuestions->AppendItem(data, wxUIntPtr(&question));
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
	btnRecord->Disable();
	btnPlayAnswer->Disable();
	btnPlayCorrectAnswer->Disable();
	btnNext->Disable();
}

void ExerciseRunDialogImp::PlayCompleted()
{

}

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
		wxGetApp().GetProvider()->GetQuizProvider().Update(*question);
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
		lstQuestions->SelectRow(viewModel.GetCurrentQuestionIndex());
		SetQuestion(*viewModel.GetCurrentQuestion());
		PlayQuestion();
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
	ShowComplete();
}

void ExerciseRunDialogImp::ShowComplete()
{
	pnlEntries->Show(false);
	pnlComplete->Show(true);
}


void ExerciseRunDialogImp::HideComplete()
{
	pnlEntries->Show(true);
	pnlComplete->Show(false);
}

bool ExerciseRunDialogImp::MoreQuestions()
{
	return (viewModel.GetCurrentQuestionIndex() + 1) < viewModel.GetRunQuestions().size();
}


bool ExerciseRunDialogImp::IsFirstQuestion()
{
	return viewModel.GetCurrentQuestionIndex() == 1;
}
