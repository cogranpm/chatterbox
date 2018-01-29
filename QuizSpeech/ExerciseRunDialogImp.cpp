#include "ExerciseRunDialogImp.h"
#include "MyApp.h"
#include <wx/app.h> 
#include "AudioPlayerPanelImp.h"
#include "DictationOverlayClientHelper.h"


ExerciseRunDialogImp::ExerciseRunDialogImp( wxWindow* parent, unsigned long quizId)
:
ExerciseRunDialog( parent ), viewModel(quizId)
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
	QuizRunQuestion currentQuestion = viewModel.GetRunQuestions().at(viewModel.GetCurrentQuestionIndex());
	int returnValue = DictationOverlayClientHelper::ShowDictationDialog(currentQuestion.GetAnswerFile(), this, txtAnswer, &player, &filePathBuffer);
	if (returnValue == wxID_OK)
	{
		currentQuestion.SetAnswerText(filePathBuffer);
		rdoEvaluation->Enable();
		btnNext->Enable();
	}
}

void ExerciseRunDialogImp::AudioPlayOnButtonClick(wxCommandEvent& event)
{

}
void ExerciseRunDialogImp::OnInitDialog(wxInitDialogEvent & event)
{
	deleteIcon.CopyFromBitmap(*wxGetApp().GetImages().delete_icon);
	SetIcon(wxIcon(deleteIcon));

	btnRecord->SetBitmap(*wxGetApp().GetImages().record_icon);
	btnNext->SetBitmap(*wxGetApp().GetImages().next_icon);

	/* load the data */
	wxGetApp().GetProvider()->GetQuizProvider().Insert(viewModel.GetHeader());
	wxGetApp().GetProvider()->GetQuizProvider().GetQuestionsByQuizId(viewModel.GetHeader().GetQuizId(), &viewModel.GetQuestions());
	size_t siz = viewModel.GetQuestions().size();
	viewModel.CreateRunQuestions();
	RenderQuestions();
	//AudioPlayerPanelImp* playerPanel = new AudioPlayerPanelImp(this, &player);
	//this->bSizer10->Add(playerPanel);

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

void ExerciseRunDialogImp::SetQuestion(QuizRunQuestion& question)
{
	txtQuestion->SetValue(question.GetQuestion().GetQuestionText());
	if (!question.GetQuestion().GetQuestionFile().empty())
	{
		player.SetURL(question.GetQuestion().GetQuestionFile());
	}
}