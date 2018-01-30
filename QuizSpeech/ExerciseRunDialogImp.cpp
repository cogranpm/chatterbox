#include "ExerciseRunDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "AudioPlayerPanelImp.h"
#include "DictationOverlayClientHelper.h"


ExerciseRunDialogImp::ExerciseRunDialogImp( wxWindow* parent, unsigned long quizId)
:
ExerciseRunDialog( parent ), viewModel(quizId), questionPlayer(this, std::wstring(L"")), answerPlayer(this, std::wstring(L"")), correctAnswerPlayer(this, std::wstring(L""))
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
	QuizRunQuestion* currentQuestion = GetCurrentQuestion();
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
	QuizRunQuestion* currentQuestion = GetCurrentQuestion();
	questionPlayer.SetURL(currentQuestion->GetQuestion().GetQuestionFile());
	questionPlayer.Play();
}

void ExerciseRunDialogImp::PlayAnswerOnButtonClick(wxCommandEvent& event)
{
	QuizRunQuestion* currentQuestion = GetCurrentQuestion();
	answerPlayer.SetURL(currentQuestion->GetAnswerFile());
	answerPlayer.Play();
}

void ExerciseRunDialogImp::SkipOnButtonClick(wxCommandEvent& event)
{

}

void ExerciseRunDialogImp::PlayCorrectAnswerOnButtonClick(wxCommandEvent& event)
{
	QuizRunQuestion* currentQuestion = GetCurrentQuestion();
	correctAnswerPlayer.SetURL(currentQuestion->GetQuestion().GetAnswer()->GetAnswerFile());
	correctAnswerPlayer.Play();
}

void ExerciseRunDialogImp::EvaluationOnRadioBox(wxCommandEvent& event)
{

}

void ExerciseRunDialogImp::NextOnButtonClick(wxCommandEvent& event)
{

}


void ExerciseRunDialogImp::OnInitDialog(wxInitDialogEvent & event)
{
	deleteIcon.CopyFromBitmap(*wxGetApp().GetImages().delete_icon);
	SetIcon(wxIcon(deleteIcon));

	btnRecord->SetBitmap(*wxGetApp().GetImages().record_icon);
	btnNext->SetBitmap(*wxGetApp().GetImages().next_icon);
	btnAudioPlay->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnPlayAnswer->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnPlayCorrectAnswer->SetBitmap(*wxGetApp().GetImages().start_icon);
	btnSkip->SetBitmap(*wxGetApp().GetImages().next_icon);

	/* load the data */
	wxGetApp().GetProvider()->GetQuizProvider().Insert(viewModel.GetHeader());
	wxGetApp().GetProvider()->GetQuizProvider().GetQuestionsByQuizId(viewModel.GetHeader().GetQuizId(), &viewModel.GetQuestions());
	size_t siz = viewModel.GetQuestions().size();
	viewModel.CreateRunQuestions();
	RenderQuestions();


	if (viewModel.GetRunQuestions().size() > 0)
	{
		viewModel.SetCurrentQuestionIndex(0);
		lstQuestions->SelectRow(viewModel.GetCurrentQuestionIndex());
		SetQuestion(viewModel.GetRunQuestions().at(viewModel.GetCurrentQuestionIndex()));
	}

}

void ExerciseRunDialogImp::RenderQuestions()
{
	wxVector<wxVariant> data;
	for (int i = 0; i < viewModel.GetRunQuestions().size(); i++)
	{
		//	wxVariant temp;
		//	temp << wxDataViewIconText(L"", limeIcon);
		QuizRunQuestion question = viewModel.GetRunQuestions().at(i);
		data.push_back(wxVariant(boost::lexical_cast<std::wstring>(i)));
		data.push_back(wxVariant(question.GetQuestion().GetLimitedQuestionText()));
		//answered
		data.push_back(wxVariant(wxDataViewIconText(L"No", deleteIcon)));
		//result
		if (question.GetIsCorrect())
		{
			data.push_back(wxVariant(wxDataViewIconText(L"", deleteIcon)));
		}
		else
		{
			data.push_back(wxVariant(wxDataViewIconText(L"", deleteIcon)));
		}
		lstQuestions->AppendItem(data, wxUIntPtr(&question));
		data.clear();
	}
}

QuizRunQuestion* ExerciseRunDialogImp::GetCurrentQuestion()
{
	return &viewModel.GetRunQuestions().at(viewModel.GetCurrentQuestionIndex());
}


void ExerciseRunDialogImp::SetQuestion(QuizRunQuestion& question)
{
	txtQuestion->SetValue(question.GetQuestion().GetQuestionText());
	//if (!question.GetQuestion().GetQuestionFile().empty())
	//{
	//	questionPlayer.SetURL(question.GetQuestion().GetQuestionFile());
	//}
}

void ExerciseRunDialogImp::PlayCompleted()
{

}