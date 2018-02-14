#pragma once

#include "stdafx.h"
#include <wx/window.h>
#include <wx/textctrl.h>
#include "AudioPlayer.h"

class DictationOverlayClientHelper
{

	static const int ShowDictationDialog(
		const std::wstring& audioFilePath,
		wxWindow* parent,
		std::wstring* textBuffer,
		AudioPlayer* player,
		std::wstring* filePathBuffer,
		wxTextCtrl* txtBox);

public:
	DictationOverlayClientHelper();
	~DictationOverlayClientHelper();
	static const int ShowDictationDialog(const std::wstring& audioFileName,
		wxWindow* parent,
		wxTextCtrl* txtBox,
		AudioPlayer* player,
		std::wstring* filePathBuffer);

	static const int ShowDictationDialog(const std::wstring& audioFileName,
		wxWindow* parent,
		std::wstring* textBuffer,
		AudioPlayer* player,
		std::wstring* filePathBuffer);

	static const void ClearAudio(const std::wstring& audioFileName, wxWindow* parent, wxTextCtrl* txtBox, AudioPlayer* player);
};

