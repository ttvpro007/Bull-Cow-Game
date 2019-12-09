#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#define TArray std::vector
#define FString std::string
//using FString = std::string;

class CVSReader
{
public:
	CVSReader();
	CVSReader(FString);
	~CVSReader();

	TArray<FString> GetData() const;

	void Import(FString);

private:
	TArray<FString> Data;
};

