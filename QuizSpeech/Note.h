#pragma once
#include <wx/datetime.h>

class Note
{
public:
	Note(void);
	Note(const unsigned long topicId);
	virtual ~Note(void);
	Note& operator=(const Note &note);
	bool operator==(const Note  &note)  {return _noteId == note.GetNoteId();}

	/*unsigned long GetType() const {return _type;}
	void SetType(unsigned long type) {_type = type;}
*/
	unsigned long GetNoteId() const {return _noteId;}
	void SetNoteId(unsigned long id) {_noteId = id;}
	bool IsNew() { return !(_noteId > 0); }
	unsigned long GetTopicId() const {return _topicId;}
	void SetTopicId(unsigned long id) {_topicId = id;}

	const std::wstring& GetTitle() const { return _title; }
	void SetTitle(const std::wstring &title) { _title = title; }

	const std::wstring GetLimitedDescription() const
	{
		if (_description.size() > 0)
		{
			if (_description.size() < 50)
			{
				return _description;
			}
			else
			{
				return _description.substr(0, 50) + L" ...";
			}
		}
		else
		{
			return _description;
		}

	}
	const std::wstring& GetDescription() const { return _description; }
	void SetDescription(const std::wstring &description) { _description = description; }

	const std::wstring& GetTitleAudioFile() const { return titleAudioFile; }
	void SetTitleAudioFile(const std::wstring &titleAudioFile) { this->titleAudioFile = titleAudioFile; }

	const std::wstring& GetDescriptionAudioFile() const { return descriptionAudioFile; }
	void SetDescriptionAudioFile(const std::wstring &descriptionAudioFile) { this->descriptionAudioFile = descriptionAudioFile; }

	const wxDateTime& GetCreatedDate() const { return _createdDate;}
	void SetCreatedDate(const wxDateTime &createdDate){ _createdDate = createdDate;}

private:
	unsigned long _noteId;
	unsigned long _topicId;
	std::wstring _title;
	std::wstring _description;
	std::wstring titleAudioFile;
	std::wstring descriptionAudioFile;

	// unsigned long _type;
	wxDateTime _createdDate;

};

