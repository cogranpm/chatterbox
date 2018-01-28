#include "NoteAudioPlayer.h"
#include "Note.h"
#include "NoteSegment.h"
#include <wx/app.h>
#include "MyApp.h"

NoteAudioPlayer::NoteAudioPlayer() : AudioPlayerWrapperClient(), audiofiles(), player(nullptr)
{

}



NoteAudioPlayer::~NoteAudioPlayer()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}

void NoteAudioPlayer::Start(Note* note)
{
	NoteViewModel noteViewModel(note);
	wxGetApp().GetProvider()->GetNoteSegmentsByNote(note, noteViewModel.GetNoteSegmentList());
	Start(&noteViewModel);
}

void NoteAudioPlayer::Start(NoteViewModel* viewModel)
{
	this->viewModel = viewModel;
	Note* note = viewModel->GetNote();
	if (!note->GetTitleAudioFile().empty())
	{
		std::wstring file(note->GetTitleAudioFile());
		audiofiles.push(file);
	}
	if (!note->GetDescriptionAudioFile().empty())
	{
		std::wstring file(note->GetDescriptionAudioFile());
		audiofiles.push(file);
	}


	boost::ptr_vector<NoteSegment>* list = viewModel->GetNoteSegmentList();
	NoteSegment* noteSegment = nullptr;
	for (int i = 0; i < list->size(); i++)
	{
		noteSegment = &(list->at(i));
		std::wstring file(noteSegment->GetBodyFile());
		if (!file.empty())
		{
			audiofiles.push(file);
		}
	}
	if (!audiofiles.empty())
	{
		SetPlayerInstance(audiofiles.front());
		player->Play();
	}
	else
	{
		//should set an icon to play available status
	}
}

void NoteAudioPlayer::Stop()
{
	player->GetAudioPlayer().Stop();
}


void NoteAudioPlayer::SetPlayerInstance(std::wstring& file)
{
	if (player != nullptr)
	{
		player->GetAudioPlayer().Clear();
		delete player;
	}
	player = new AudioPlayerWrapper(this, file);
}

void NoteAudioPlayer::PlayCompleted()
{
	audiofiles.pop();
	if (!audiofiles.empty())
	{
		SetPlayerInstance(audiofiles.front());
		player->Play();
	}
	else
	{
		//should set an icon to play available status
	}
}

