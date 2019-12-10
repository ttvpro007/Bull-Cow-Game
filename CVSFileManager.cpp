#include "CVSFileManager.h"

CVSFileManager::CVSFileManager()
{
}

CVSFileManager::CVSFileManager(FString File)
{
	ReadFile(File);
}

CVSFileManager::~CVSFileManager()
{
}

TArray<FString> CVSFileManager::GetData() const
{
	return CSVData;
}

void CVSFileManager::ReadFile(FString File)
{
	std::fstream FIn;

	// open existing file
	FIn.open(File, std::ios::in);

	// check if file exist
	if (FIn.fail())
	{
		std::cout << "File " << File << " not exist.\n";
		return;
	}

	FString Line;

	CSVData.clear(); // clear the vector

	// read data from the file as string and store in a data vector
	while (FIn.good())
	{
		std::getline(FIn, Line); // read an entire row and store in the variable Line
		CSVData.push_back(Line); // store the line that was read into data vector
	}

	return;
}

void CVSFileManager::WriteFile(FString FileName, TArray<FString> CSVData)
{
	std::fstream FOut;

	// create new file
	FOut.open(FileName, std::ios::out);

	for (auto Iterator = CSVData.begin(); Iterator != CSVData.end(); ++Iterator)
	{
		if (*Iterator != CSVData.back())
		{
			FOut << *Iterator << "\n";
		}
		else
		{
			FOut << *Iterator;
		}
	}
}