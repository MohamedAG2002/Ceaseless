#include "File.h"

#include <iostream>
#include <raylib.h>

File::File()
{
}

File::~File()
{
}

File& File::Instance()
{
	static File instance;
	return instance;
}

bool File::IsFileEmpty(std::fstream& file)
{
	// Returns true if there is nothing in the file
	return file.peek() == std::fstream::traits_type::eof();
}

void File::SaveData(const unsigned int& data)
{
	// Opening the file in write and binary mode
	m_file.open(FILE_NAME, std::ios::out | std::ios::binary);

	// Checking if the file has opened...
	if (m_file.is_open())
	{
		// ...if it has, write the data to the file
		m_file.write((char*)&data, sizeof(data));

		// ALWAYS REMEMBER TO CLOSE THE FILE
		m_file.close();
	}
	// ...if not, write an error
	else std::cerr << "The file did not open!" << std::endl;
}

const unsigned int File::LoadData()
{
	unsigned int data = 0;

	// Opening the file in read and binary mode
	m_file.open(FILE_NAME, std::ios::in | std::ios::binary);

	if (m_file.is_open())
	{
		// Read the data from the file
		m_file.read((char*)&data, sizeof(data));

		// Checking the file is empty...
		if (!IsFileEmpty(m_file))
		{
			//...if it not, read the contents of file until the end
			while (!m_file.eof())
			{
				m_file.read((char*)&data, sizeof(data));
			}
		}

		m_file.close();
	}
	else std::cerr << "The file did not open!" << std::endl;

	return data;
}
