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
	Has_White_Space
};

static class BullCowGameManager
{
public:
	// instructor
	BullCowGameManager();
	~BullCowGameManager();

	// Play the game!!!
	void PowerON();

	// Print all the words in the word bank
	void PrintWordsInDictionary();

private:
	// variables
	EGameMode GameMode = EGameMode::Invalid_Mode;
	FBullCowGame BullCowGame;
	FString AIName = FString("[GAME STATION]");;
	static std::default_random_engine RandomGenerator;

	// helper functions

	// ************** PowerON **************
	// Game mode
	EGameMode InitGameMode();

	// Setting up the game
	void Initialize();

	// Run the game
	//void RunGameLoop(EGameMode, bool);
	void RunGameLoop(EGameMode);
	// ************** PowerON **************

	// ************** Initialize **************
	// Setup Word game
	void InitWordGame();

	// Setup Number game
	void InitCombinationGame();
	// ************** Initialize **************

	// ************** Gameplay functions **************
	// Play Word game
	void PlayWordGame();
	// Play Combination game
	void PlayCombinationGame();

	// Ask the desired word length from user
	int32 AskWordLength();
	
	// Ask the desired number length from user
	int32 AskCombinationLength();

	// Get guess and loop until valid guess is received
	FString GetValidWordGuess();

	// Get guess and loop until valid guess is received
	FString GetValidCombinationGuess();
	
	// Print hint from game black box
	void PrintHint();
	
	// Show last entered guess
	void PrintGuess(FString);
	
	// Ask if want hint
	bool AskIfWantHint();
	
	// Print game summary
	void PrintGameSummary(EGameMode, bool);
	void PrintHiddenWordAndDefinition() const;
	void PrintLockCombination() const;
	
	// Ask if want to play again
	bool AskToPlayAgain();
	
	// Game mode checker
	EGameMode CheckGameMode(int32) const;

	// State of yes no input
	EYesNoAnswerStatus CheckYesNoAnswerStatus(FString);

	// Is Yes or No checker
	bool IsYesOrNo(FString);
	
	// Is first character white space
	bool IsFirstCharWhiteSpace(FString);
	// ************** Gameplay functions **************

	// ************** Utility functions **************
	// Get current Game Mode
	EGameMode CurrentGameMode();

	// Get a random integer within min and max
	int32 GetRandomInteger(int32, int32);

	// Convert string to int, if unsuccessful, return -1
	int32 StringToInt32(FString);

	// Testing function to write csv file
	void TEST_CSVFileWrite();
	// ************** Utility functions **************
};