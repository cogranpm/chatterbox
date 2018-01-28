#pragma once

#include "stdafx.h"
#include <wx/window.h>
#include <wx/textctrl.h>
#include "AudioPlayer.h"

class DictationOverlayClientHelper
{
public:
	DictationOverlayClientHelper();
	~DictationOverlayClientHelper();
	static const int ShowDictationDialog(const std::wstring& audioFilePath,
		wxWindow* parent,
		wxTextCtrl* txtBox,
		AudioPlayer* player,
		std::wstring* filePathBuffer);
	static const void ClearAudio(const std::wstring& audioFilePath, wxWindow* parent, wxTextCtrl* txtBox, AudioPlayer* player);
};

