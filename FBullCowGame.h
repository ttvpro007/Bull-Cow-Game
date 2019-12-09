#pragma once

#include <iostream>
#include <string>
#include <map>
#include <random>
#include <chrono>
#include <unordered_set>
#include "CVSReader.h"

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
	// constructor
	FBullCowGame();
	// constructor that takes max tries
	FBullCowGame(int32);
	// constructor that takes word length and max tries
	FBullCowGame(int32, int32);
	~FBullCowGame(); // destructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	FString GetHiddenWordDescription() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	TMap<int32, TArray<FString>> GetDictionary() const;

	EGuessStatus CheckGuessValidity(FString);
	// counts bulls and cows and increases turn # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

	EWordLengthStatus CheckWordLengthValidity(FString);
	void SetUserIndicatedWordLength(FString);

	void Reset(); // TODO make a more rich return value.

private:
	// initialize in helper function 
	// InitializingSomePrivateVariables(int32, int32)
	int32 MinLength;
	int32 MaxLength;
	TMap<int32, int32> AvailableIDAndLengthTable;

	// constructor initialization
	int32 CurrentTry;
	int32 MaxTries;
	TMap<int32, TArray<FString>> IsogramDictionary;
	int32 UserIndicatedWordLength;
	TArray<FString> WordAndDescription;

	// default initialization
	bool bIsGameWon = false;

	// helper functions
	bool IsIsogram(FString) const;
	bool HasWhiteSpace(FString) const;

	TMap<int32, TArray<FString>> GetIsogramDictionaryFromFile(FString);
	TArray<FString> GetWordAndDescriptionFromDictionary(int32, TMap<int32, TArray<FString>>);

	void InitializingSomePrivateVariables(int32, int32);

	bool IsIDAvailable(int32);
	bool IsLengthAvalable(int32);
	// remove element from AvailableIDAndLengthTable
	void RemoveUsedIDAndLength(int32);

	void ExceptionHandlerInt32LessThanZero(int32, FString);
	// output = -1 if cannot convert to integer
	static int32 StringToInt32(FString);
};