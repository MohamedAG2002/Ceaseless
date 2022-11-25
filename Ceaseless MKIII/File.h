#pragma once

#include <fstream>

// Const for the file name
const char FILE_NAME[9] = "data.dat";

// A singelton class for file managment
class File
{
private:
	File();
	~File();

private:
	std::fstream m_file;

public:
	static File& Instance();

	File(File const&) = delete;
	void operator=(File const&) = delete;

	bool IsFileEmpty(std::fstream& file);
	void SaveData(const unsigned int& data);
	const unsigned int LoadData();
};

