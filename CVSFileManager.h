#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define TArray std::vector
#define FString std::string
//using FString = std::string;

class CVSFileManager
{
public:
	CVSFileManager();
	CVSFileManager(FString);
	~CVSFileManager();

	TArray<FString> GetData() const;

	void ReadFile(FString);
	void WriteFile(FString, TArray<FString>);

private:
	TArray<FString> CSVData;
};

