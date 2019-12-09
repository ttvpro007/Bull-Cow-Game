#include "CVSReader.h"

CVSReader::CVSReader()
{
}

CVSReader::CVSReader(FString File)
{
	Import(File);
}

CVSReader::~CVSReader()
{
}

TArray<FString> CVSReader::GetData() const
{
	return Data;
}

void CVSReader::Import(FString File)
{
	std::fstream FIn;

	// open existing file
	FIn.open(File);

	FString Line;

	Data.clear(); // clear the vector

	// read data from the file as string and store in a data vector
	while (FIn.good())
	{
		std::getline(FIn, Line); // read an entire row and store in the variable Line
		Data.push_back(Line); // store the line that was read into data vector
	}

	return;
}
