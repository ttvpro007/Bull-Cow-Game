#include "GameManager.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

std::default_random_engine GameManager::RandomGenerator;

void GameManager::PowerON(bool IsDebugMode)
{
	Initialize();
	RunGameLoop(GameMode, IsDebugMode);
}

void GameManager::PrintWordsInDictionary()
{
	TMap<int32, TArray<FString>> Dictionary = BullCowGame.GetDictionary();

	std::cout << AIName;
	std::cout << ": Here is the Word Bank\n";

	for (auto Iterator = Dictionary.begin(); Iterator != Dictionary.end(); ++Iterator)
	{
		std::cout << "ID: " << Iterator->first;
		std::cout << "   Word: " << Iterator->second[0];
		std::cout << "   Definition: " << Iterator->second[1] << std::endl;
	}

	return;
}

void GameManager::PrintIntroduction(EGameMode GameMode)
{
	switch (GameMode)
	{
	case EGameMode::Invalid_Mode:
		std::cout << AIName;
		std::cout << ": GameMode INVALID!!!.\n";
		break;
	case EGameMode::Mode_Word:
		BullCowGame.Introduction();
		break;
	case EGameMode::Mode_Number:
		break;
	default:
		break;
	}
}

void GameManager::SetupGameMode()
{
	// variables
	FString Mode = "";

	std::cout << AIName;
	std::cout << ": I have 2 game mode for you.\n";
	std::cout << AIName;
	std::cout << ": 1 for Word game\n";
	std::cout << AIName;
	std::cout << ": 2 for Number game\n";

	do
	{
		std::cout << AIName;
		std::cout << ": Which mode would you like to play? ";

		std::getline(std::cin, Mode);

		GameMode = GetValidGameMode(StringToInt32(Mode));

		switch (GameMode)
		{
		case EGameMode::Mode_Word:
			std::cout << AIName;
			std::cout << ": You chose to play word game.\n\n";
			break;
		case EGameMode::Mode_Number:
			std::cout << AIName;
			std::cout << ": You chose to play number game.\n\n";
			break;
		default:
			std::cout << std::endl << AIName;
			std::cout << ": Please choose mode 1 or mode 2.\n";
			break;
		}

	} while (GameMode != EGameMode::Mode_Word && GameMode != EGameMode::Mode_Number);
}

void GameManager::Initialize()
{
	SetupGameMode();

	switch (GameMode)
	{
	case EGameMode::Invalid_Mode:
		break;
	case EGameMode::Mode_Word:
		PrintIntroduction(GameMode);
		StartWordGame();
		break;
	case EGameMode::Mode_Number:
		break;
	default:
		break;
	}

	return;
}

void GameManager::RunGameLoop(EGameMode GameMode, bool IsDebugMode)
{
	switch (GameMode)
	{
	case EGameMode::Invalid_Mode:
		break;
	case EGameMode::Mode_Word:
		PlayBullCowGame(IsDebugMode);
		break;
	case EGameMode::Mode_Number:
		break;
	default:
		break;
	}
}

void GameManager::StartWordGame()
{
	// variables
	int32 WordLength = 0;

	AIName = BullCowGame.GetAIName();
	WordLength = AskWordLength();
	BullCowGame.Initialize(WordLength);
	std::cout << std::endl;
	PrintCommandListAndDescription();
	std::cout << std::endl;
}

void GameManager::InitNumGame()
{
}

void GameManager::PlayBullCowGame(bool IsDebugMode)
{
	// variables
	int32 MaxTries = 0; FString Guess = "";

	bool bPlayAgain = false;

	std::cout << AIName;
	std::cout << ": You have " << BullCowGame.GetMaxTries() << " tries to guess the word!\n\n";

	do
	{
		MaxTries = BullCowGame.GetMaxTries();

		// debug mode for development process
		if (IsDebugMode) std::cout << "[DEBUG MODE] The hidden word is [" << BullCowGame.GetHiddenWord() << "]\n\n";

		// loop while is NOT won and there are still tries remaining
		while (!BullCowGame.IsGameWon() && BullCowGame.GetCurrentTry() <= MaxTries)
		{
			Guess = GetValidGuess();

			// break out of loop if giving up
			if (BullCowGame.IsGivingUp()) break;
			else if (BullCowGame.IsCommand(Guess)) continue;

			// submit valid guess to the game and receive counts
			FBullCowCount BullCowCount = BullCowGame.SubmitValidGuess(Guess);

			std::cout << "BULLS [" << BullCowCount.Bull << "]";
			std::cout << "   COWS [" << BullCowCount.Cow << "]\n";

			PrintGuess(Guess);
		}

		// print end game message
		PrintGameSummary(BullCowGame.IsGivingUp());
		std::cout << std::endl;
		bPlayAgain = AskToPlayAgain();

	} while (bPlayAgain);

	return;
}

int32 GameManager::AskWordLength()
{
	// variables
	FString WordLength = "";
	int32 IWordLength = 0;

	EWordLengthStatus WordLengthStatus = EWordLengthStatus::Invalid_Status;

	do
	{
		std::cout << AIName;
		std::cout << ": How many letter isogram do you want to try (from " << BullCowGame.GetMinLength() << " to " << BullCowGame.GetMaxLength() << ")? ";
		std::getline(std::cin, WordLength);

		WordLengthStatus = BullCowGame.CheckWordLengthValidity(WordLength);

		switch (WordLengthStatus)
		{
		case EWordLengthStatus::OK:
			break;
		case EWordLengthStatus::Not_In_Range:
			std::cout << AIName;
			std::cout << ": The number you just entered is not in range, please enter another number.\n\n";
			break;
		case EWordLengthStatus::Not_Number:
			std::cout << AIName;
			std::cout << ": The input you just entered is not a number, please enter a number.\n\n";
			break;
		case EWordLengthStatus::Has_White_Space:
			std::cout << AIName;
			std::cout << ": The input you just entered has white space, please enter a number without white space.\n\n";
			break;
		case EWordLengthStatus::No_Word_With_This_Length:
			std::cout << AIName;
			std::cout << ": There is NO or NO MORE word with this length, please enter a different number.\n\n";
			break;
		default:
			break;
		}

	} while (WordLengthStatus != EWordLengthStatus::OK);

	IWordLength = StringToInt32(WordLength);

	return IWordLength;
}

FString GameManager::GetValidGuess()
{
	// variables
	int32 CurrentTry = BullCowGame.GetCurrentTry();
	FString Guess = "";
	EGuessStatus GuessStatus = EGuessStatus::Invalid_Status;

	do
	{
		// prompt user input
		std::cout << "[Try " << CurrentTry << " of " << BullCowGame.GetMaxTries();
		std::cout << "] Please enter your guess: ";
		std::getline(std::cin, Guess);

		GuessStatus = BullCowGame.CheckGuessValidity(Guess);

		switch (GuessStatus)
		{
		case EGuessStatus::Is_Command:
			BullCowGame.ExecuteCommand(Guess);
			break;
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BullCowGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Has_White_Space:
			std::cout << "Please enter whole word without white space.\n\n";
			break;
		default:
			break;
		}

	} while (GuessStatus != EGuessStatus::OK && GuessStatus != EGuessStatus::Is_Command);

	return Guess;
}

void GameManager::PrintHint()
{
	constexpr int32 TAB_LENGTH = 4;
	FString AsteriskBorder = "***********************************************************************\n";
	FString Header = "!!! HINT !!!\n";
	FString Hint = "HIDDEN LETTER(S): " + BullCowGame.GetHint() + "\n";
	int32 AsteriskBorderLength = (int32)(TAB_LENGTH + AsteriskBorder.length());
	int32 HeaderFillLength = (int32)(TAB_LENGTH + (AsteriskBorder.length() - Header.length()) / 2 + Header.length());
	int32 DialogFillLength = (int32)(TAB_LENGTH + (AsteriskBorder.length() - Hint.length()) / 2 + Hint.length());

	std::cout << std::endl;
	std::cout << std::setfill(' ') << std::setw(AsteriskBorderLength) << AsteriskBorder;
	std::cout << std::setfill(' ') << std::setw(HeaderFillLength) << Header;
	std::cout << std::setfill(' ') << std::setw(AsteriskBorderLength) << AsteriskBorder;
	std::cout << std::setfill(' ') << std::setw(DialogFillLength) << Hint << "\n";
	std::cout << std::setfill(' ') << std::setw(AsteriskBorderLength) << AsteriskBorder;
	std::cout << std::endl;

	return;
}

void GameManager::PrintGuess(FString Guess)
{
	// print user input
	std::cout << AIName;
	std::cout << ": Your guess was \"" << Guess << "\"\n\n";

	return;
}

bool GameManager::AskIfWantHint()
{
	FString Response = "";
	EYesNoAnswerStatus AnswerStatus = EYesNoAnswerStatus::Invalid_Status;

	do
	{
		std::cout << AIName;
		std::cout << ": Too hard? Do you want to reveal a letter for this word (y/n)? ";
		std::getline(std::cin, Response);

		AnswerStatus = CheckYesNoAnswerStatus(Response);

	} while (AnswerStatus != EYesNoAnswerStatus::OK);

	return (tolower(Response[0]) == 'y');
}

void GameManager::PrintGameSummary(bool IsGivingUp)
{
	constexpr int32 TAB_LENGTH = 4;
	FString AsteriskBorder = "***********************************************************************\n";
	FString Header = "";
	FString Dialog = "";

	if (BullCowGame.IsGameWon())
	{
		Header = "!!!   WIN   !!!\n";
		Dialog = AIName + ": Well done - You WIN!\n";
	}
	else
	{
		Header = "!!!   LOSE   !!!\n";

		if (!IsGivingUp)
			Dialog = AIName + ": You've used all your tries! Better luck next time...\n";
		else
			Dialog = AIName + ": Given up already? You'll get it next time!\n";
	}

	int32 AsteriskBorderLength = (int32)(TAB_LENGTH + AsteriskBorder.length());
	int32 HeaderFillLength = (int32)(TAB_LENGTH + (AsteriskBorder.length() - Header.length()) / 2 + Header.length());

	std::cout << std::endl;
	std::cout << std::setfill(' ') << std::setw(AsteriskBorderLength) << AsteriskBorder;
	std::cout << std::setfill(' ') << std::setw(HeaderFillLength) << Header;
	std::cout << std::setfill(' ') << std::setw(AsteriskBorderLength) << AsteriskBorder;
	std::cout << "        HIDDEN WORD: " << BullCowGame.GetHiddenWord() << "\n";
	std::cout << "        DEFINITION: " << BullCowGame.GetHiddenWordDefinition() << "\n\n";
	std::cout << std::setfill(' ') << std::setw(AsteriskBorderLength) << AsteriskBorder;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << Dialog;
	std::cout << std::endl;

	return;
}

bool GameManager::AskToPlayAgain()
{
	FString Response = "";
	int32 WordLength = 0;

	EYesNoAnswerStatus AnswerStatus = EYesNoAnswerStatus::Invalid_Status;

	do
	{
		std::cout << "Do you want to play again (y/n)? ";
		std::getline(std::cin, Response);

		AnswerStatus = CheckYesNoAnswerStatus(Response);

	} while (AnswerStatus != EYesNoAnswerStatus::OK);

	if (tolower(Response[0]) == 'y')
	{
		WordLength = AskWordLength();
		BullCowGame.Reset(WordLength);
	}

	std::cout << std::endl;

	return (tolower(Response[0]) == 'y');
}

EGameMode GameManager::GetValidGameMode(int32 GameMode) const
{
	if (GameMode == 1)
	{
		return EGameMode::Mode_Word;
	}
	else if (GameMode == 2)
	{
		return EGameMode::Mode_Number;
	}
	else
	{
		return EGameMode::Invalid_Mode;
	}
}

EYesNoAnswerStatus GameManager::CheckYesNoAnswerStatus(FString Answer)
{
	if (IsFirstCharWhiteSpace(Answer))
	{
		std::cout << AIName;
		std::cout << ": Please enter Yes or No without white space infront.\n\n";
		return EYesNoAnswerStatus::First_Char_White_Space;
	}
	else if (!IsYesOrNo(Answer))
	{
		std::cout << AIName;
		std::cout << ": Please enter Yes or No.\n\n";
		return EYesNoAnswerStatus::Not_Yes_And_Not_No;
	}
	else
	{
		return EYesNoAnswerStatus::OK;
	}
}

bool GameManager::IsYesOrNo(FString Word)
{
	char FirstChar = Word[0];

	if (tolower(FirstChar) != 'y' && tolower(FirstChar) != 'n')
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool GameManager::IsFirstCharWhiteSpace(FString Word)
{
	char Letter = Word[0];

	if (Letter == ' ') // if is blank space
	{
		return true; // has white space
	}

	return false;
}

void GameManager::PrintCommandListAndDescription()
{
	std::cout << AIName;
	std::cout << ": Here is the command list for the game in case you need it\n";
	BullCowGame.PrintCommandListAndDescription();
}

int32 GameManager::GetRandomInteger(int32 Min, int32 Max)
{
	int32 RandomNumber = 0;
	RandomGenerator.seed((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int32> RandomIntegerDistribution(Min, Max);
	return RandomNumber = RandomIntegerDistribution(RandomGenerator);
}

int32 GameManager::StringToInt32(FString String)
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

void GameManager::TEST_CSVFileWrite()
{
	// open existing csv file
	CVSFileManager Test("Test File.csv");
	// get data from the file
	TArray<FString> Data = Test.GetData();
	// increment the ID of the word based on array size
	// and put in stream formating is "ID#,"  for example "32,"
	std::stringstream SStream;
	SStream << Data.size() + 1 << ',';
	FString Line; // for string storage
	SStream >> Line; // initiate to format "ID#," for example "32,"
	// get new value and append to line
	Line = Line.append("ging,A random word");
	Data.push_back(Line); // added to data
	Test.WriteFile("Test File.csv", Data); // create new or override existing file with data
}
