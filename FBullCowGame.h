#pragma once

#include <iostream>
#include <string>
#include <map>
#include <random>
#include <chrono>
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

enum class EGameMode
{
	Invalid_Mode,
	Mode_Word,
	Mode_Combination
};

enum class EWordGuessStatus
{
	Invalid_Status,
	OK,
	Is_Not_Isogram,
	Wrong_Length,
	Has_White_Space,
	Is_Command
};

enum class ECombinationGuessStatus
{
	Invalid_Status,
	OK,
	Is_Not_Number,
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

enum class ECombinationLengthStatus
{
	Invalid_Status,
	OK,
	Not_Number,
	Not_In_Range,
	Has_White_Space,
};

// command action switch
enum class ECommandAction
{
	Invalid,
	Debug,
	Hint,
	Exit,
	Give_Up,
	Menu,
	Command_List
};

class FBullCowGame
{
public:

	FBullCowGame(); // constructor
	~FBullCowGame(); // destructor

	// initializer that takes word length 
	void Initialize(EGameMode, int32);
	void InitWordGame(int32);
	void InitCombinationGame(int32);

	FString WordGameIntro() const;
	FString CombinationGameIntro() const;
	void BullCowGameIntro(EGameMode);

	int32 GetMinWordLength() const;
	int32 GetMaxWordLength() const;
	int32 GetMinCombinationLength() const;
	int32 GetMaxCombinationLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetTriesLeft() const;
	FString GetDebugString(EGameMode);
	FString GetHiddenWord() const;
	FString GetHiddenWordDefinition() const;
	int32 GetHiddenWordLength() const;
	FString GetLockCombination() const;
	int32 GetLockCombinationLength() const;
	FString GetHint();
	TMap<int32, TArray<FString>> GetDictionary() const;
	TArray<FString> Command_Expr() const;
	FString GetAIName() const;
	void PrintCommandList() const;
	void PrintCommandListAndDescription() const;

	bool IsCommand(FString) const;
	bool IsGameWon() const;
	bool IsGivingUp() const;
	bool IsGoingToMenu() const;
	bool HasShownAllLetters() const;

	// status checkers
	EWordGuessStatus CheckGuessValidity(FString) const;
	EWordLengthStatus CheckWordLengthValidity(FString) const;
	ECombinationGuessStatus CheckCombinationGuessValidity(FString) const;
	ECombinationLengthStatus CheckCombinationLengthValidity(FString) const;

	void ExecuteCommand(FString);
	
	// counts bulls and cows and increases turn #
	FBullCowCount SubmitValidWordGuess(FString);
	FBullCowCount SubmitValidCombinationGuess(FString);

	void Reset();
	void Reset(EGameMode, int32); // TODO make a more rich return value.
	void ResetWordGame(int32);
	void ResetCombinationGame(int32);

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
		"debug",
		"hint",
		"giveup",
		"menu",
		"exit",
		"command list"
	};

	const FString AIName = FString("[GAME MASTER]");

	// initialized int32 type variables in contructor
	// initialize in helper function 
	// InitializingSomePrivateVariables(int32, int32)
	int32 MinWordLength;
	int32 MaxWordLength;
	TMap<int32, int32> AvailableIDAndLengthTable;
	TArray<char> Hint;
	TArray<char> HintShown; // Not initialized in helper function
	EGameMode GameMode;

	// method initialization
	int32 CurrentTry = 0;
	int32 MaxTries = 0;
	int32 CurrentHint = 0;
	int32 MaxHint = 0;
	int32 MinCombinationLength = 0;
	int32 MaxCombinationLength = 0;
	TMap<int32, TArray<FString>> IsogramDictionary;
	TArray<FString> WordAndDefinition;
	FString LockCombination = "";

	// default initialization
	bool bIsGameWon = false;
	bool bIsGivingUp = false;
	bool bIsGoingToMenu = false;

	// helper functions
	// command action checker
	ECommandAction GetCommandAction(FString) const;

	bool IsIsogram(FString) const;
	bool HasWhiteSpace(FString) const;
	bool IsEligibleForHint() const;
	bool IsNumber(FString) const;

	TMap<int32, TArray<FString>> GetIsogramDictionaryFromFile(FString);
	TArray<FString> GetWordAndDefinitionFromDictionary(int32, TMap<int32, TArray<FString>>);
	FString GenerateRandomUniqueNumber(int32);
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