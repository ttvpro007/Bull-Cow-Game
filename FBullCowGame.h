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
	Has_White_Space
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

class FBullCowGame
{
public:

	FBullCowGame(); // constructor
	~FBullCowGame(); // destructor

	// initializer
	void Initialize();
	// initializer that takes word length
	void Initialize(int32);

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetTriesLeft() const;
	FString GetHiddenWord() const;
	FString GetHiddenWordDescription() const;
	int32 GetHiddenWordLength() const;
	FString GetHint();
	TMap<int32, TArray<FString>> GetDictionary() const;

	bool IsGameWon() const;
	bool HasShownAllLetters() const;

	// status checkers
	EGuessStatus CheckGuessValidity(FString) const;
	EWordLengthStatus CheckWordLengthValidity(FString) const;
	
	// counts bulls and cows and increases turn #
	FBullCowCount SubmitValidGuess(FString); // TODO move current try and its incement to game manager

	void Reset(int32); // TODO make a more rich return value.

private:
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
	TMap<int32, TArray<FString>> IsogramDictionary;
	TArray<FString> WordAndDescription;

	// default initialization
	bool bIsGameWon = false;

	// helper functions
	bool IsIsogram(FString) const;
	bool HasWhiteSpace(FString) const;

	TMap<int32, TArray<FString>> GetIsogramDictionaryFromFile(FString);
	TArray<FString> GetWordAndDescriptionFromDictionary(int32, TMap<int32, TArray<FString>>);
	int32 CalculateMaxTries(int32);

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