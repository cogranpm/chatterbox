#include "DictationOverlayClientHelper.h"
#include "SpeechMessageDialog.h"
#include <wx/app.h> 
#include "MyApp.h"
#include "DictationOverlayDialogImp.h"


DictationOverlayClientHelper::DictationOverlayClientHelper()
{
}


DictationOverlayClientHelper::~DictationOverlayClientHelper()
{
}


const int DictationOverlayClientHelper::ShowDictationDialog(
	const std::wstring& audioFilePath,
	wxWindow* parent,
	std::wstring* textBuffer,
	AudioPlayer* player,
	std::wstring* filePathBuffer,
	wxTextCtrl* txtBox)
{
	int returnVal = wxID_CANCEL;
	try
	{
		//show a warning before recording over what is currently saved????
		if (!audioFilePath.empty())
		{
			SpeechMessageDialog confirmDlg(parent, L"You will overwrite current audio, continue?", L"Confirm", wxOK | wxCANCEL | wxCENTRE, wxDefaultPosition);
			if (confirmDlg.ShowModal() != wxID_OK)
			{
				return returnVal;
			}
		}

		bool fileNameChanged = false;
		*filePathBuffer = wxGetApp().GetFileHandler().GetCurrentPath() + wxGetApp().GetFileHandler().GetFileNameByTime(L"wav");

		/* show an overlay when dictating so the user can totally focus on speaking */
		{
			//create an inner scope for the dialog so it's resources will be released inside it
			DictationOverlayDialogImp dialog(parent, *filePathBuffer);
			returnVal = dialog.ShowModal();
			if (returnVal == wxID_OK)
			{
				std::wstring recognizedText;
				dialog.GetRecognizedText(recognizedText);
				if (txtBox != nullptr)
				{
					txtBox->SetValue(recognizedText);
				}
				if (textBuffer != nullptr)
				{
					textBuffer->assign(recognizedText);
				}
				/* if player currently has a valid audio file, delete it before applying the new */
				if (wxGetApp().GetFileHandler().FileExists(audioFilePath))
				{
					wxGetApp().GetFileHandler().DeleteFile(audioFilePath);
				}
				//this->_viewModel->GetNote()->SetTitleAudioFile(fileName);
				fileNameChanged = true;
			}
		}
		if (fileNameChanged && (player != nullptr))
		{
			//set this outside of dialog scope
			player->SetURL(*filePathBuffer);
		}
	}
	catch (std::exception& e)
	{
		wxMessageBox(e.what(), L"Error", wxICON_ERROR);
	}
	return returnVal;

}

const int DictationOverlayClientHelper::ShowDictationDialog(const std::wstring& audioFilePath,
	wxWindow* parent,
	std::wstring* textBuffer,
	AudioPlayer* player,
	std::wstring* filePathBuffer)
{
	return DictationOverlayClientHelper::ShowDictationDialog(audioFilePath, parent, textBuffer, player, filePathBuffer, nullptr);
}

const int DictationOverlayClientHelper::ShowDictationDialog(const std::wstring& audioFilePath,
	wxWindow* parent,
	wxTextCtrl* txtBox,
	AudioPlayer* player,
	std::wstring* filePathBuffer
	)
{
	return DictationOverlayClientHelper::ShowDictationDialog(audioFilePath, parent, nullptr, player, filePathBuffer, txtBox);
}


const void DictationOverlayClientHelper::ClearAudio(const std::wstring& audioFilePath, wxWindow* parent, wxTextCtrl* txtBox, AudioPlayer* player)
{
	txtBox->Clear();
	if (wxGetApp().GetFileHandler().FileExists(audioFilePath))
	{
		wxGetApp().GetFileHandler().DeleteFile(audioFilePath);
	}
	player->Clear();
}