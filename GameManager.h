#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"


#define FString std::string
#define int32 int

enum class EYesNoAnswerStatus
{
	Invalid_Status,
	OK,
	Not_Yes_And_Not_No,
	First_Char_White_Space,
};

static class GameManager
{
public:

	void PlayGame();
	void PrintWordsInDictionary();

private:
	// variables
	FBullCowGame BullCowGame = FBullCowGame();
	static std::default_random_engine RandomGenerator;

	// helper functions
	void PrintIntroduction();
	void Initialize();
	void PrintHint();
	void RunGameLoop();
	FString GetValidGuess();
	void PrintGuess(FString);
	void PrintGameSummary();
	bool AskToPlayAgain();
	int32 AskWordLength();
	bool AskIfWantHint();
	EYesNoAnswerStatus CheckYesNoAnswerStatus(FString);

	int32 GetRandomInteger(int32, int32);
	int32 StringToInt32(FString);

	void TEST_CSVFileWrite();
};