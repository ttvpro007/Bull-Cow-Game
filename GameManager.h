#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
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
	// instructor
	GameManager();
	~GameManager();

	// Play the game!!! TRUE for Debug mode, FALSE for Normal mode
	void PlayGame(bool);

	// Print all the words in the word bank
	void PrintWordsInDictionary();

private:
	// variables
	FBullCowGame BullCowGame;
	FString AIName;
	static std::default_random_engine RandomGenerator;

	// helper functions

	// ************** PlayGame **************
	// Print introduction for the game
	void PrintIntroduction();

	// Game mode
	int AskGameMode();

	// Setting up the game
	void Initialize();

	// Run the game
	void RunGameLoop(bool);
	// ************** PlayGame **************

	// ************** Gameplay functions **************
	// Ask the desired word length from user
	int32 AskWordLength();
	
	// Get guess and loop until valid guess is received
	FString GetValidGuess();
	
	// Print hint from game black box
	void PrintHint();
	
	// Show last entered guess
	void PrintGuess(FString);
	
	// Ask if want hint
	bool AskIfWantHint();
	
	// Print game summary
	void PrintGameSummary(bool);
	
	// Ask if want to play again
	bool AskToPlayAgain();
	
	// State of yes no input
	EYesNoAnswerStatus CheckYesNoAnswerStatus(FString);
	
	// Is Yes or No checker
	bool IsYesOrNo(FString);
	
	// Is first character white space
	bool IsFirstCharWhiteSpace(FString);
	
	// Command helper
	void PrintCommandListAndDescription();
	// ************** Gameplay functions **************

	// ************** Utility functions **************
	// Get a random integer within min and max
	int32 GetRandomInteger(int32, int32);

	// Convert string to int, if unsuccessful, return -1
	int32 StringToInt32(FString);

	// Testing function to write csv file
	void TEST_CSVFileWrite();
	// ************** Utility functions **************
};