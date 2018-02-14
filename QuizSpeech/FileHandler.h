#ifndef GTKMM_TEST001_FILEHANDLER_H__
#define GTKMM_TEST001_FILEHANDLER_H__

class FileHandler
{
public:
	FileHandler(void);
	FileHandler(const std::wstring& initialPath);
	~FileHandler(void);

	std::wstring GetFileNameByTime(const std::wstring& extension);
	void WriteText(const std::wstring& data, const std::basic_string<TCHAR>& fileName);
	void AppendText(const std::wstring& data, const std::basic_string<TCHAR>& fileName);
	void ReadText(std::wstring& data, const std::wstring& fileName);
	void IterateFolder();
	void PlaySound(const std::wstring& fullPath);
	void PlayAll();
	void ReadAll(std::wstring& buffer);

	std::wstring GetCurrentPath();
	void SetCurrentPath(const std::wstring&);

	void MakeDirectory(const std::wstring&);
	void MoveBack();
	bool DeleteFile(const std::wstring&);
	std::wstring getFileExtension(const std::wstring&);
	void loadFileNamesByExtension(std::list<std::wstring>& lst, const std::wstring& extension, const std::wstring& directoryPath);

	bool FileExists(const std::wstring& path);
	bool FileExists(const std::string& path);
	std::wstring& GetAudioPath() { return audioPath; }
	void SetAudioPath(const std::wstring& path) { audioPath = path; }
protected:


private:
	boost::filesystem::path m_currentPath;
	std::wstring audioPath;
};

#endif GTKMM_TEST001_FILEHANDLER_H__