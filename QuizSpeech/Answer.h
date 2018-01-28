#pragma once

#include "stdafx.h"
#include "BaseEntity.h"

class Answer : public BaseEntity
{
	unsigned long answerId;
	unsigned long questionId;
	std::wstring answerText;
	std::wstring answerFile;

public:
	Answer(unsigned long questionId);
	Answer();
	~Answer();

	std::wstring GetAnswerText() { return answerText; }
	std::wstring GetShortAnswerText()
	{
		if (answerText.size() > 0)
		{
			if (answerText.size() < 50)
			{
				return answerText;
			}
			else
			{
				return answerText.substr(0, 50) + L" ...";
			}
		}
		else
		{
			return answerText;
		}

	}
	void SetAnswerText(const std::wstring& answerText);

	std::wstring GetAnswerFile() { return answerFile; }
	void SetAnswerFile(const std::wstring& audioFile);

	const unsigned long GetAnswerId() { return answerId; }
	void SetAnswerId(const unsigned long id) { answerId = id; }

	const unsigned long GetQuestionId() { return questionId; }
	void SetQuestionId(const unsigned long id) { questionId = id; }

	bool IsNew() { return !(answerId > 0); }
};

