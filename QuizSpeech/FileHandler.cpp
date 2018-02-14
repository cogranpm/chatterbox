#include "stdafx.h"
#include "FileHandler.h"


using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::filesystem;


FileHandler::FileHandler(void) : audioPath()
{
}

FileHandler::FileHandler(const std::wstring& initialPath) : m_currentPath(initialPath), audioPath()
{
	
}


FileHandler::~FileHandler(void)
{
}

std::wstring FileHandler::GetCurrentPath(void)
{
	return m_currentPath.generic_wstring();
}

void FileHandler::SetCurrentPath(const std::wstring& newPath)
{
	m_currentPath = newPath + TEXT("/");
}

void FileHandler::MoveBack()
{
	path p(this->GetCurrentPath());
	std::wstring parentPath = p.branch_path().wstring();
	path pBack (parentPath);
	std::wstring secondParent = pBack.branch_path().wstring();
	this->SetCurrentPath(secondParent);
}

void FileHandler::IterateFolder(void)
{
	if (exists(m_currentPath))    // does p actually exist?
	{
		if (is_regular_file(m_currentPath))      
		{
			// is p a regular file?   
			//std::cout << m_currentPath << " size is " << file_size(m_currentPath) << '\n';
			//the current path will never be a file, always a folder
		}

		else if (is_directory(m_currentPath))      // is p a directory?
		{

			/*********************** start of files******************************/
			directory_iterator end_iter;
			typedef std::multimap<std::time_t, path> result_set_t;
			result_set_t result_set;

			for( directory_iterator dir_iter(m_currentPath) ; dir_iter != end_iter ; ++dir_iter)
			{
				if (is_regular_file(dir_iter->status()) )
				{
					result_set.insert(result_set_t::value_type(last_write_time(*dir_iter), *dir_iter));
				}
			}

			for (result_set_t::iterator it = result_set.begin(); it != result_set.end();++it)
			{
				path p((*it).second );
				std::wstring fileNamex = p.wstring();
				std::wstring extension = p.extension().wstring();
				if(extension == ".wav" || extension == ".txt" || extension == ".dat" || extension == ".qtn")
				{
					
				}
			}
			/*********************** end of files******************************/

			typedef std::vector<boost::filesystem::path> vec;             // store paths,
			vec v;     
			copy(directory_iterator(m_currentPath), directory_iterator(), back_inserter(v));
			for (vec::const_iterator it (v.begin()); it != v.end(); ++it)
			{
				boost::filesystem::path fn = it->filename();
				if(is_directory(*it))
				{
				}
			}
		}
		else
		{
		//	std::cout << m_currentPath << "exists, but is neither a regular file nor a directory\n";
		}
	}
	else
	{

	}

}

void FileHandler::PlaySound(const std::wstring& fullPath)
{
	::PlaySound(fullPath.c_str(), NULL, SND_SYNC); 
}

void FileHandler::PlayAll()
{
	if (exists(m_currentPath))    // does p actually exist?
	{
		if (is_directory(m_currentPath))      // is p a directory?
		{

			directory_iterator end_iter;
			typedef std::multimap<std::time_t, path> result_set_t;
			result_set_t result_set;

			for( directory_iterator dir_iter(m_currentPath) ; dir_iter != end_iter ; ++dir_iter)
			{
				if (is_regular_file(dir_iter->status()) )
				{
					result_set.insert(result_set_t::value_type(last_write_time(*dir_iter), *dir_iter));
				}
			}

			for (result_set_t::iterator it = result_set.begin(); it != result_set.end();++it)
			{
				path p((*it).second );
				std::wstring fileNamex = p.wstring();
				std::wstring extension = p.extension().wstring();
				if(extension == ".wav")
				{
					this->PlaySound(p.wstring());
				}
			}
		}
	}
}

void FileHandler::ReadAll(std::wstring& buffer)
{
	if (exists(m_currentPath))    // does p actually exist?
	{
		if (is_directory(m_currentPath))      // is p a directory?
		{
			directory_iterator end_iter;
			typedef std::multimap<std::time_t, path> result_set_t;
			result_set_t result_set;

			for( directory_iterator dir_iter(m_currentPath) ; dir_iter != end_iter ; ++dir_iter)
			{
				if (is_regular_file(dir_iter->status()) )
				{
					result_set.insert(result_set_t::value_type(last_write_time(*dir_iter), *dir_iter));
				}
			}

			for (result_set_t::iterator it = result_set.begin(); it != result_set.end();++it)
			{
				path p((*it).second );
				std::wstring fileNamex = p.wstring();
				std::wstring extension = p.extension().wstring();
				if(extension == ".txt")
				{
					this->ReadText(buffer, fileNamex);
				}
			}
		}
	}
}


std::wstring FileHandler::GetFileNameByTime(const std::wstring& extension)
{
	 date d( day_clock::local_day());
	 ptime t(second_clock::local_time());
	 time_duration tod = t.time_of_day();
	 std::wostringstream sstimeName;
	 sstimeName << tod.ticks();
	 std::wstring fileName = sstimeName.str();
	 fileName += L"." + extension;
	 return fileName;
}

void FileHandler::WriteText(const std::wstring& data, const std::basic_string<TCHAR>& fileName)
{
	std::ofstream myfile;
	myfile.open (fileName);
	myfile << data;
	myfile.close();
}

void FileHandler::AppendText(const std::wstring& data, const std::basic_string<TCHAR>& fileName)
{
	std::ofstream myfile;
	myfile.open (fileName, std::ios::out | std::ios::app);
	myfile << data << std::endl;
	myfile.close();

}


void FileHandler::ReadText(std::wstring& data, const std::wstring& fileName)
{
	//std::ifstream t(fileName);
	std::basic_ifstream<TCHAR> t(fileName);
	std::wstring line;
	while(std::getline(t, line))
	{
		data += line + TEXT("\n");
	}
	
	//C:\Users\paulm\Documents\Notes\Tests\2012Apr1511924.txt
	//std::stringstream buffer;
	//buffer << t.rdbuf();
	//std::string tmp(buffer.str());
	
	//data += buffer.str();
	
}


void FileHandler::MakeDirectory(const std::wstring& directoryName)
{
	//if(directoryName.length() == 0)
	//{
	//	return;
	//}
	path newPath = m_currentPath.wstring() + directoryName;
	bool result = create_directory(newPath);
	if(result)
	{
		SetCurrentPath(newPath.wstring());
	}
}

bool FileHandler::DeleteFile(const std::wstring& filePath)
{
	path deletePath = filePath;
	return remove(deletePath);
}

std::wstring FileHandler::getFileExtension(const std::wstring& filePath)
{
	path pathOfFile = filePath;
	return pathOfFile.extension().wstring();
}

void FileHandler::loadFileNamesByExtension(std::list<std::wstring>& lst, const std::wstring& extension, const std::wstring& directoryPath)
{
	if (exists(directoryPath))    // does p actually exist?
	{
		if (is_directory(directoryPath))      // is p a directory?
		{
			directory_iterator end_iter;
			typedef std::multimap<std::time_t, path> result_set_t;
			result_set_t result_set;

			for( directory_iterator dir_iter(directoryPath) ; dir_iter != end_iter ; ++dir_iter)
			{
				if (is_regular_file(dir_iter->status()) )
				{
					result_set.insert(result_set_t::value_type(last_write_time(*dir_iter), *dir_iter));
				}
			}

			for (result_set_t::iterator it = result_set.begin(); it != result_set.end();++it)
			{
				path p((*it).second );
				//std::string fileName = p.string();
				std::wstring fileName = p.filename().wstring();
				std::wstring fileExtension = p.extension().wstring();
				if(extension == fileExtension)
				{
					lst.push_back(fileName);
				}
			}
		}
	}
}

bool FileHandler::FileExists(const std::wstring& path)
{	
	boost::filesystem::path filePath(path);
	return exists(filePath);

}

bool FileHandler::FileExists(const std::string& path)
{	
	boost::filesystem::path filePath(path);
	return exists(filePath);

}

std::wstring FileHandler::GetFullAudioPathToFile(const std::wstring& fileName)
{
	std::wstring fullPath(GetAudioPath());
	fullPath = fullPath + fileName;
	return fullPath;
}

std::wstring FileHandler::GetNewAudioFileName()
{
	return GetFileNameByTime(L"wav");
}