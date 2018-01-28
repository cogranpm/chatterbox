#include "SoundRecorder.h"
#include "wx\msgdlg.h"


SoundRecorder::SoundRecorder()
{
}


SoundRecorder::~SoundRecorder()
{
}

void SoundRecorder::Record(const std::wstring filePath)
{
	// Uses the MCI_OPEN, MCI_RECORD, and MCI_SAVE commands to record and
	// save a waveform-audio file. Returns 0L if successful; otherwise,
	// it returns an MCI error code.

	UINT wDeviceID;
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;
	MCI_RECORD_PARMS mciRecordParms;
	MCI_SAVE_PARMS mciSaveParms;
	MCI_PLAY_PARMS mciPlayParms;



	// Open a waveform-audio device with a new file for recording.
	mciOpenParms.lpstrDeviceType = L"waveaudio";
	mciOpenParms.lpstrElementName = L"";
	if (dwReturn = mciSendCommand(0, MCI_OPEN,
		MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpenParms))
	{
		// Failed to open device; don't close it, just return error.
		return;
	}

	// The device opened successfully; get the device ID.
	wDeviceID = mciOpenParms.wDeviceID;

	// Begin recording and record for the specified number of 
	// milliseconds. Wait for recording to complete before continuing. 
	// Assume the default time format for the waveform-audio device 
	// (milliseconds).
	wxMessageBox(L"Recording");
	mciRecordParms.dwTo = 3000;
	if (dwReturn = mciSendCommand(wDeviceID, MCI_RECORD,
		MCI_TO | MCI_WAIT, (DWORD)(LPVOID)&mciRecordParms))
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
		return;
	}


	// Play the recording and query user to save the file.
	//lets not play just yet
	//mciPlayParms.dwFrom = 0L;
	//if (dwReturn = mciSendCommand(wDeviceID, MCI_PLAY,
	//	MCI_FROM | MCI_WAIT, (DWORD)(LPVOID)&mciPlayParms))
	//{
	//	mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
	//	return;
	//}

	// Save the recording to a file named TEMPFILE.WAV. Wait for
	// the operation to complete before continuing.
	mciSaveParms.lpfilename = filePath.c_str();
	if (dwReturn = mciSendCommand(wDeviceID, MCI_SAVE,
		MCI_SAVE_FILE | MCI_WAIT, (DWORD)(LPVOID)&mciSaveParms))
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
		return;
	}

}



