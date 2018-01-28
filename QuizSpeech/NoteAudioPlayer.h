#pragma once

#include "stdafx.h"
#include "NoteViewModel.h"
#include "Note.h"
#include "AudioPlayerWrapper.h"
#include "AudioPlayerWrapperClient.h"

class NoteAudioPlayer : public AudioPlayerWrapperClient
{
	NoteViewModel* viewModel;
	std::queue<std::wstring> audiofiles;
	AudioPlayerWrapper* player;
	boost::ptr_vector<Note>* noteList;
	void SetPlayerInstance(std::wstring& file);
public:
	NoteAudioPlayer();
	~NoteAudioPlayer();
	void Start(NoteViewModel* viewModel);
	void Start(Note* note);
	void Stop();
	NoteViewModel* GetViewModel() { return viewModel; }
	void PlayCompleted();
};

