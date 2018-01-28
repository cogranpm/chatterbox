#pragma once

#include "stdafx.h"
#include "NoteViewModel.h"
#include "Note.h"
#include "AudioPlayerWrapper.h"
#include "AudioPlayerWrapperClient.h"

class NoteListAudioPlayer : public AudioPlayerWrapperClient
{

	std::queue<std::wstring> audiofiles;
	AudioPlayerWrapper* player;
	boost::ptr_vector<Note>* noteList;
	void SetPlayerInstance(std::wstring& file);

public:
	~NoteListAudioPlayer();
	NoteListAudioPlayer();
	void Start(boost::ptr_vector<Note>* noteList);
	void Stop();
	void PlayCompleted();
};

