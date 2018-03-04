#include "NoteListAudioPlayer.h"
#include <wx/app.h>
#include "MyApp.h"


NoteListAudioPlayer::NoteListAudioPlayer() : AudioPlayerWrapperClient(), audiofiles(), player(nullptr)
{
}


NoteListAudioPlayer::~NoteListAudioPlayer()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}

void NoteListAudioPlayer::Start(boost::ptr_vector<Note>* noteList)
{
	this->noteList = noteList;
	/* iterate all the notes, get the segments, add all audio files to list of audio paths */
	for (int i = 0; i < noteList->size(); i++)
	{
		Note note = (noteList->at(i));
		if (!note.GetTitleAudioFile().empty())
		{
			std::wstring file(note.GetTitleAudioFile());
			audiofiles.push(file);
		}
		if (!note.GetDescriptionAudioFile().empty())
		{
			std::wstring file(note.GetDescriptionAudioFile());
			audiofiles.push(file);
		}


		boost::ptr_vector<NoteSegment> list;
		wxGetApp().GetProvider()->GetNoteSegmentsByNote(&note, &list);
		NoteSegment* noteSegment = nullptr;
		for (int i = 0; i < list.size(); i++)
		{
			noteSegment = &(list.at(i));
			std::wstring file(noteSegment->GetBodyFile());
			if (!file.empty())
			{
				audiofiles.push(file);
			}
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

void NoteListAudioPlayer::Stop()
{
	player->GetAudioPlayer().Stop();
}


void NoteListAudioPlayer::SetPlayerInstance(std::wstring& file)
{
	if (player != nullptr)
	{
		player->GetAudioPlayer().Clear();
		delete player;
	}
	player = new AudioPlayerWrapper(this, wxGetApp().GetFileHandler().GetFullAudioPathToFile(file));
}

void NoteListAudioPlayer::PlayCompleted()
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

