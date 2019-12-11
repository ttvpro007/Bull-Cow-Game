#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
	: CurrentTry(0), MaxTries(0), MinLength(0), MaxLength(0),
	IsogramDictionary(GetIsogramDictionaryFromFile("Isogram Word Bank.csv"))
{
}
FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::Initialize()
{
	WordAndDescription = GetWordAndDescriptionFromDictionary(0, IsogramDictionary);
	CurrentTry = 1;
	MaxTries = CalculateMaxTries((int32)WordAndDescription[0].length());
	InitializeHintSystem((int32)WordAndDescription[0].size());

	return;
}
void FBullCowGame::Initialize(int32 WordLength)
{
	WordAndDescription = GetWordAndDescriptionFromDictionary(WordLength, IsogramDictionary);
	CurrentTry = 1;
	this->MaxTries = CalculateMaxTries((int32)WordAndDescription[0].length());
	InitializeHintSystem(WordLength);

	return;
}

int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetTriesLeft() const
{
	return MaxTries - CurrentTry + 1;
}
FString FBullCowGame::GetHiddenWord() const { return WordAndDescription[0]; }
FString FBullCowGame::GetHiddenWordDescription() const { return WordAndDescription[1]; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32)WordAndDescription[0].length(); }
FString FBullCowGame::GetHint()
{
	FString HintWord = "";
	char Letter = ' ';
	int32 Index = 0;


	// if had shown all letters return blank
	if (!HasShownAllLetters())
	{
		do
		{
			// randomized index
			Index = GetRandomInteger(0, Hint.size() - 1);
			// get letter from word at randomized index
			Letter = WordAndDescription[0][Index];

		} while (IsHintLetterShown(Letter));

		// populate hint letter shown
		HintLettersShown.push_back(Letter);

		// replace "_" with a random letter taken from hidden word
		Hint[Index] = Letter;
	}

	// populate the hint word
	HintWord = TArrayOfCharToString(Hint);
	
	return HintWord;
}
TMap<int32, TArray<FString>> FBullCowGame::GetDictionary() const { return IsogramDictionary; }
TArray<FString> FBullCowGame::Command_Expr() const
{
	return COMMAND_EXPR;
}
void FBullCowGame::PrintCommandList() const
{
	std::cout << "\n*************\n";
	std::cout << "COMMAND LIST:\n";
	for (auto Command : COMMAND_EXPR)
	{
		std::cout << Command << "\n";
	}
	std::cout << "*************\n";
	std::cout << std::endl;
}

bool FBullCowGame::IsCommand(FString Word) const
{
	TArray<FString> CommandList = Command_Expr();
	for (int32 i = 0; i < CommandList.size(); i++)
	{
		if (Word == CommandList[i]) return true;
	}

	return false;
}
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }
bool FBullCowGame::IsGivingUp() const { return bIsGivingUp; }
bool FBullCowGame::HasShownAllLetters() const { return HintLettersShown.size() == Hint.size(); }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (IsCommand(Guess)) // if guess is command expression
	{
		return EGuessStatus::Is_Command;
	}
	else if (HasWhiteSpace(Guess)) // if guess has white space
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
	else if (IWordLength > MaxLength || IWordLength < MinLength)
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

void FBullCowGame::ExecuteCommand(FString Command)
{
	ECommandAction CommandAction = GetCommandAction(Command);
	
	switch (CommandAction)
	{
	case ECommandAction::Invalid:
		std::cout << "Command Invalid\n\n";
		break;
	case ECommandAction::Help:
		PrintCommandList();
		break;
	case ECommandAction::Exit:
		exit(0);
		break;
	case ECommandAction::Give_Up:
		bIsGivingUp = true;
		break;
	default:
		break;
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

void FBullCowGame::Reset(int32 WordLength)
{
	bIsGameWon = false;
	bIsGivingUp = false;
	WordAndDescription = GetWordAndDescriptionFromDictionary(WordLength, IsogramDictionary);
	CurrentTry = 1;
	MaxTries = CalculateMaxTries(WordLength);
	InitializeHintSystem(WordLength);

	return;
}

// helper functions
ECommandAction FBullCowGame::GetCommandAction(FString Command) const
{
	if (Command == "help") return ECommandAction::Help;
	else if (Command == "giveup") return ECommandAction::Give_Up;
	else if (Command == "exit") return ECommandAction::Exit;
	else return ECommandAction::Invalid;
}

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
	// variables
	CVSFileManager WordBankReader = CVSFileManager(File); // read file

	constexpr int32 COLUMN = 3; // the total columns of data in work bank file

	TMap<int32, TArray<FString>> Dictionary; // dictionary with word IDs
	TArray<FString> Data = WordBankReader.GetData(); // get data from cvs file reader

	int32 ID = 0;
	FString Isogram = "";
	FString Description = "";
	FString Word = "";
	FString Words[COLUMN] = {}; // used store the broken up words
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

		try
		{
			ID = StringToInt32(Words[0]); // convert number as string to integer *** MAKE SURE STRING IS NUMBER ***
			Isogram = Words[1]; // store second element of words array into variable IsogramWord
			Description = Words[2]; // store third element of words array into variable description

			if (ID == -1) throw Words[0];
		}
		catch (FString Word)
		{
			std::cout << "\n\n***EXCEPTION*** Cannot convert to integer at value " << Word << "\n\n";
			exit(-2);
		}

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
	int32 ID = 0;
	FString Word = "";
	FString Description = "";
	TArray<FString> WordAndDescription = TArray<FString>();
	bool bHasSeenAllWords = false;

	// if word length is default which means equal to 0, get a random number within min and max length
	while (!IsLengthAvalable(WordLength))
	{
		// generate new random number while word length is not available
		WordLength = GetRandomInteger(MinLength, MaxLength);
	}

	while (Word.length() != WordLength || !IsIDAvailable(ID))
	{	
		ID = GetRandomInteger(1, (int32)Dictionary.size()); // get random ID number
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
int32 FBullCowGame::CalculateMaxTries(int32 WordLength)
{
	return WordLength * 2;
}

void FBullCowGame::InitializingSomePrivateVariables(int32 ID, int32 WordLength)
{
	// 1. populate available ID and length table
	AvailableIDAndLengthTable.insert({ ID, WordLength });

	// 2. find min and max value
	if (ID == 1)
	{
		MinLength = WordLength;
		MaxLength = MinLength;
	}

	if (WordLength < MinLength) MinLength = WordLength;
	if (WordLength > MaxLength) MaxLength = WordLength;

	return;
}
void FBullCowGame::InitializeHintSystem(int32 WordLength)
{
	Hint.clear();
	HintLettersShown.clear();

	// initialized all letters in hint to "_"
	for (int32 i = 0; i < WordLength; i++)
	{
		Hint.push_back('_');
	}

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
bool FBullCowGame::IsHintLetterShown(char Letter) const
{
	for (auto HLetter : HintLettersShown)
	{
		if (Letter == HLetter) return true;
	}

	return false;
}
void FBullCowGame::RemoveUsedIDAndLength(int32 ID)
{
	AvailableIDAndLengthTable.erase(ID);
}

int32 FBullCowGame::GetRandomInteger(int32 Min, int32 Max) const
{
	int32 RandomInteger = 0;
	if (Min == Max) return Min;
	std::default_random_engine RandomGenerator;
	RandomGenerator.seed((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int32> RandomDistribution(Min, Max);
	return RandomInteger = RandomDistribution(RandomGenerator);
}
int32 FBullCowGame::StringToInt32(FString String) const
{
	char* pEnd = nullptr;
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
FString FBullCowGame::TArrayOfCharToString(TArray<char> ArrayOfChar)
{
	if (ArrayOfChar.size() > 0)
	{
		return FString(ArrayOfChar.begin(), ArrayOfChar.end());
	}
	else
	{
		return FString("");
	}
}
