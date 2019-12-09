#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
	: CurrentTry(0), MaxTries(0), MinLength(0), MaxLength(0), UserIndicatedWordLength(0),
	IsogramDictionary(GetIsogramDictionaryFromFile("Isogram Word Bank.csv"))
{
}

FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::Initialize()
{
	CurrentTry = 1;
	MaxTries = 3;
	UserIndicatedWordLength = 0;
	WordAndDescription = GetWordAndDescriptionFromDictionary(UserIndicatedWordLength, IsogramDictionary);
}

void FBullCowGame::Initialize(int32 MaxTries)
{
	CurrentTry = 1;
	this->MaxTries = MaxTries;
	UserIndicatedWordLength = 0;
	WordAndDescription = GetWordAndDescriptionFromDictionary(UserIndicatedWordLength, IsogramDictionary);
}

void FBullCowGame::Initialize(int32 WordLength, int32 MaxTries)
{
	CurrentTry = 1;
	this->MaxTries = MaxTries;
	UserIndicatedWordLength = WordLength;
	WordAndDescription = GetWordAndDescriptionFromDictionary(UserIndicatedWordLength, IsogramDictionary);
}

int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
FString FBullCowGame::GetHiddenWord() const { return WordAndDescription[0]; }
FString FBullCowGame::GetHiddenWordDescription() const { return WordAndDescription[1]; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32)WordAndDescription[0].length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }
TMap<int32, TArray<FString>> FBullCowGame::GetDictionary() const { return IsogramDictionary; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (HasWhiteSpace(Guess)) // if guess has white space
	{
		return EGuessStatus::Has_White_Space;
	}
	else if (!IsIsogram(Guess)) // if guess isn't isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if guess doesn't have right length
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise return Ok
	{
		return EGuessStatus::OK;
	}
}
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{// received a valid guess, increments turn and returns counts

	CurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();

	// loop through all letters in the guess
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare if same letter different place (cow)
		for (int32 j = 0; j < WordLength; j++)
		{
			// compare if same letter same place (bull)
			if (tolower(Guess[i]) == WordAndDescription[0][j])
			{
				if (i == j) // if same spot
				{
					BullCowCount.Bull++; // increment bull
				}
				else // otherwise
				{
					BullCowCount.Cow++; // increment cow
				}
			}
		}
	}

	// if all bull
	if (BullCowCount.Bull == WordLength)
	{
		bIsGameWon = true; // win
	}
	else
	{
		bIsGameWon = false; // not win
	}

	return BullCowCount;
}

EWordLengthStatus FBullCowGame::CheckWordLengthValidity(FString WordLength) const
{
	// will return -1 if cannot conver to integer
	int32 IWordLength = StringToInt32(WordLength);

	if (HasWhiteSpace(WordLength))
	{
		return EWordLengthStatus::Has_White_Space;
	}
	else if (IWordLength == -1)
	{
		return EWordLengthStatus::Not_Number;
	}
	else if (IWordLength > MaxLength|| IWordLength < MinLength)
	{
		return EWordLengthStatus::Not_In_Range;
	}
	else if (!IsLengthAvalable(IWordLength))
	{
		return EWordLengthStatus::No_Word_With_This_Length;
	}
	else
	{
		return EWordLengthStatus::OK;
	}
}

void FBullCowGame::SetUserIndicatedWordLength(int32 WordLength)
{
	UserIndicatedWordLength = WordLength;
}

void FBullCowGame::Reset()
{
	CurrentTry = 1;
	bIsGameWon = false;
	WordAndDescription = GetWordAndDescriptionFromDictionary(UserIndicatedWordLength, IsogramDictionary); // TODO should take in word length

	return;
}

// helper functions
bool FBullCowGame::IsIsogram(FString Word) const
{
	// 0 or 1 word length can pass
	if (Word.length() <= 1) return true;

	TMap<char, bool> LetterSeen;

	// iterate through each character of the word
	for (auto Letter : Word)
	{
		// convert to lowercase
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) // if letter was seen
		{
			return false; // is not isogram
		}
		else // otherwise
		{
			LetterSeen[Letter] = true; // add letter to map as seen
		}
	}

	return true;
}
bool FBullCowGame::HasWhiteSpace(FString Word) const
{
	for (auto Letter : Word)
	{
		if (Letter == ' ') // if is blank space
		{
			return true; // has white space
		}
	}

	return false;
}

TMap<int32, TArray<FString>> FBullCowGame::GetIsogramDictionaryFromFile(FString File)
{
	CVSFileManager WordBankReader = CVSFileManager(File); // read file

	constexpr int32 COLUMN = 3;

	TMap<int32, TArray<FString>> Dictionary; // dictionary with word IDs
	TArray<FString> Data = WordBankReader.GetData(); // get data from cvs file reader

	int32 ID;
	FString Isogram, Description, Word;
	FString Words[COLUMN]; // used store the broken up words
	char Delimiter = (char)','; // delimiter that determine where to break up the words
	std::stringstream SStream; // used for breaking up words in a line and convert string to integer;

	for (auto Line : Data)
	{
		SStream.clear(); // clear stream in order to feed in new line

		TArray<FString> IsogramAndDescription;

		SStream << Line; // stream in

		int32 Count = 0;
		while (std::getline(SStream, Word, Delimiter))
		{
			Words[Count] = Word; // store the word into an array of words

			// array out of bound check
			if (Count < COLUMN - 1) Count++;
		}

		ID = StringToInt32(Words[0]); // convert number as string to integer *** MAKE SURE STRING IS NUMBER ***
		Isogram = Words[1]; // store second element of words array into variable IsogramWord
		Description = Words[2]; // store third element of words array into variable description

		IsogramAndDescription.push_back(Isogram);
		IsogramAndDescription.push_back(Description);

		// store word length and word into dictionary at iterator position
		Dictionary.insert({ ID, IsogramAndDescription });

		// initialize MinLength, MaxLength, and AvaiableID variables
		// this compare the values of min max length of words 
		// and populate integer array so has to be in loop
		InitializingSomePrivateVariables(ID, (int32)Isogram.length());
	}

	return Dictionary;
}
TArray<FString> FBullCowGame::GetWordAndDescriptionFromDictionary(int32 WordLength, TMap<int32, TArray<FString>> Dictionary)
{
	std::default_random_engine RandomGenerator;
	RandomGenerator.seed((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int32> IDRandomDistribution(1, (int32)Dictionary.size());

	// exception handler for initialize WordLengthRandomDistribution
	ExceptionHandlerInt32LessThanZero(MinLength, "MinLength");
	ExceptionHandlerInt32LessThanZero(MaxLength, "MaxLength");
	std::uniform_int_distribution<int32> WordLengthRandomDistribution(MinLength, MaxLength);

	int32 ID = 0;
	int32 Count = 0;
	FString Word, Description;
	TArray<FString> WordAndDescription;
	bool bHasSeenAllWords = false;

	// if word length is default which means equal to 0, get a random number within min and max length
	while (!IsLengthAvalable(WordLength))
	{
		// generate new random number while word length is not available
		WordLength = WordLengthRandomDistribution(RandomGenerator);
	}

	while (Word.length() != WordLength || !IsIDAvailable(ID))
	{	
		ID = IDRandomDistribution(RandomGenerator); // get random ID number
		Word = Dictionary[ID][0]; // get the word of random ID
	}

	Description = Dictionary[ID][1]; // set description

	// populate array
	WordAndDescription.push_back(Word);
	WordAndDescription.push_back(Description);

	// remove used ID and length
	RemoveUsedIDAndLength(ID);

	return WordAndDescription;
}

void FBullCowGame::InitializingSomePrivateVariables(int32 ID, int32 WordLength)
{
	AvailableIDAndLengthTable.insert({ ID, WordLength });

	// find min and max value
	if (ID == 1)
	{
		MinLength = WordLength;
		MaxLength = MinLength;
	}

	if (WordLength < MinLength) MinLength = WordLength;
	if (WordLength > MaxLength) MaxLength = WordLength;

	return;
}

bool FBullCowGame::IsIDAvailable(int32 ID) const
{
	// check every element in id and length table
	for (auto Iterator = AvailableIDAndLengthTable.begin(); Iterator != AvailableIDAndLengthTable.end(); ++Iterator)
	{
		// if ID is equal to one of the elements
		if (ID == Iterator->first)
		{
			// ID is available
			return true;
		}
	}

	// ID not available
	return false;
}
bool FBullCowGame::IsLengthAvalable(int32 WordLength) const
{
	// check every element in id and length table
	for (auto Iterator = AvailableIDAndLengthTable.begin(); Iterator != AvailableIDAndLengthTable.end(); ++Iterator)
	{
		// if length is equal to one of the elements
		if (WordLength == Iterator->second)
		{
			// length is available
			return true;
		}
	}

	// length not available
	return false;
}
void FBullCowGame::RemoveUsedIDAndLength(int32 ID)
{
	AvailableIDAndLengthTable.erase(ID);
}

void FBullCowGame::ExceptionHandlerInt32LessThanZero(int32 Variable, FString VariableName) const
{
	try
	{
		if (Variable <= 0)
		{
			throw Variable;
		}
	}
	catch (int32 ExceptionInt32)
	{
		std::cout << VariableName << " value of " << ExceptionInt32 << " is <= 0.\n";
	}

	return;
}
int32 FBullCowGame::StringToInt32(FString String)
{
	char* pEnd;
	int32 Integer = (int32)std::strtol(String.c_str(), &pEnd, 10);

	if (*pEnd)
	{
		// conversion fail
		return -1;
	}
	else
	{
		// conversion success
		return Integer;
	}
}