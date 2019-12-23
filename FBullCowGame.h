#pragma once

#include <iostream>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <unordered_set>
#include "CVSFileManager.h"

#define TMap std::map
#define int32 int
#define TArray std::vector
#define TPair std::pair
#define FString std::string

// all value initialized to zero
struct FBullCowCount
{
	int32 Bull = 0;
	int32 Cow = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Has_White_Space,
	Is_Command
};

enum class EWordLengthStatus
{
	Invalid_Status,
	OK,
	Not_Number,
	Not_In_Range,
	Has_White_Space,
	No_Word_With_This_Length
};

// command action switch
enum class ECommandAction
{
	Invalid,
	Hint,
	Exit,
	Give_Up,
	Command_List
};

class FBullCowGame
{
public:

	FBullCowGame(); // constructor
	~FBullCowGame(); // destructor

	// initializer
	void Initialize();
	// initializer that takes word length
	void Initialize(int32);

	void Introduction() const;
	int32 GetMinLength() const;
	int32 GetMaxLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetTriesLeft() const;
	FString GetHiddenWord() const;
	FString GetHiddenWordDefinition() const;
	int32 GetHiddenWordLength() const;
	FString GetHint();
	TMap<int32, TArray<FString>> GetDictionary() const;
	TArray<FString> Command_Expr() const;
	FString GetAIName() const;
	void PrintCommandList() const;
	void PrintCommandListAndDescription() const;

	bool IsCommand(FString) const;
	bool IsGameWon() const;
	bool IsGivingUp() const;
	bool HasShownAllLetters() const;

	// status checkers
	EGuessStatus CheckGuessValidity(FString) const;
	EWordLengthStatus CheckWordLengthValidity(FString) const;

	void ExecuteCommand(FString);
	
	// counts bulls and cows and increases turn #
	FBullCowCount SubmitValidGuess(FString); // TODO move current try and its incement to game manager

	void Reset(int32); // TODO make a more rich return value.

private:

	// Command System
	// step for adding command expression
	// 1. add expression in COMMAND_EXPR string array
	// 2. add enum of the command expression in ECommandAction
	// 3. add condition for returning command action switch in GetCommandAction function
	// 4. add command feature/ for the expression in ExecuteCommand
	// 5. enjoy your newly created command expression!
	const TArray<FString> COMMAND_EXPR = 
	{
		"hint",
		"giveup",
		"exit",
		"command list"
	};

	const FString AIName = FString("[WORD GAME MASTER]");

	// initialized int32 type variables in contructor
	// initialize in helper function 
	// InitializingSomePrivateVariables(int32, int32)
	int32 MinLength;
	int32 MaxLength;
	TMap<int32, int32> AvailableIDAndLengthTable;
	TArray<char> Hint;
	TArray<char> HintLettersShown; // Not initialized in helper function

	// method initialization
	int32 CurrentTry = 0;
	int32 MaxTries = 0;
	int32 CurrentHint = 0;
	int32 MaxHint = 0;
	TMap<int32, TArray<FString>> IsogramDictionary;
	TArray<FString> WordAndDefinition;

	// default initialization
	bool bIsGameWon = false;
	bool bIsGivingUp = false;

	// helper functions
	// command action checker
	ECommandAction GetCommandAction(FString) const;

	bool IsIsogram(FString) const;
	bool HasWhiteSpace(FString) const;
	bool IsEligibleForHint() const;

	TMap<int32, TArray<FString>> GetIsogramDictionaryFromFile(FString);
	TArray<FString> GetWordAndDefinitionFromDictionary(int32, TMap<int32, TArray<FString>>);
	int32 CalculateMaxTries(int32);
	int32 CalculateMaxHint(int32);

	void InitializingSomePrivateVariables(int32, int32);
	void InitializeHintSystem(int32);

	bool IsIDAvailable(int32) const;
	bool IsLengthAvalable(int32) const;
	bool IsHintLetterShown(char) const;
	// remove element from AvailableIDAndLengthTable
	void RemoveUsedIDAndLength(int32);

	int32 GetRandomInteger(int32, int32) const; // return Min if Min == Max
	int32 StringToInt32(FString) const; // output = -1 if cannot convert to integer
	FString TArrayOfCharToString(TArray<char>); // output = "" if array was not populated
};