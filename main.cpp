
/* This is the console executable that makes use of the FBullCowGame class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic, see FBullCowGame class.
*/

#include "GameManager.h"
#include "FBullCowGame.h"

#define FText std::string
#define int32 int

void PlayGame();
void PrintIntroduction();
void Initialize();
void PrintHint();
void RunGameLoop();
FText GetValidGuess();
void PrintGuess(FText);
void PrintGameSummary();
bool AskToPlayAgain();
int32 AskWordLength();
bool AskIfWantHint();
EYesNoAnswerStatus CheckYesNoAnswerStatus(FString);

bool IsYesOrNo(FString);
bool IsFirstCharWhiteSpace(FString);

void PrintWordsInDictionary();
static int32 StringToInt32(FString);

int32 GetRandomInteger(int32, int32);

void TEST_CSVFileWrite();

//static FBullCowGame BullCowGame(3);
FBullCowGame BullCowGame;

static std::default_random_engine RandomGenerator;



int main()
{
	//PrintWordsInDictionary();
	
	PlayGame();

	/*for (size_t i = 0; i < 5; i++)
	{
		TEST_CSVFileWrite();
	}*/

	return 0; // exit application
}

void PlayGame()
{
	PrintIntroduction();

	Initialize();

	RunGameLoop();
}
void PrintIntroduction()
{
	// introduction
	std::cout << "               .                                                                \n";
	std::cout << "                		                                                          \n";
	std::cout << "               |		                                                          \n";
	std::cout << "      .               /                                                         \n";
	std::cout << "       \\       I     	                                                      \n";
	std::cout << "                   /                                                            \n";
	std::cout << "         \\  ,g88R_                                                             \n";
	std::cout << "           d888(`  ).                             _                         __  \n";
	std::cout << "  -  --==  888(     ).=--              _      .+(`  )`.              .--._.'  ' \n";
	std::cout << " )         Y8P(       '`.          _+(   ) --:(   .    )          .=(         ) \n";
	std::cout << "         .+(`(      .   )     .-- '      _   `.  (    ) )         (   .  )   )  \n";
	std::cout << "        ((    (..__.:'-'   .=(   )     (   )   ` _`  ) )         (   (   ))     \n";
	std::cout << " `.     `(       ) )       (   .  )    ''    )    (   )    ._      `- __.'      \n";
	std::cout << "   )      ` __.:'   )     (   (   )) (  (     ) _: `-'  .:(`  )           (     \n";
	std::cout << " )  )  ( )       --'       `- __.'     -+_ _:'         :(      ))          '-__ \n";
	std::cout << " .-'  (_.'          .')                                `(    )  ))              \n";
	std::cout << "                   (_  )                                 ` __.:'                \n";
	std::cout << "                                      	                                      \n";
	std::cout << " -..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._.---.-'`,---..-_.--,-,,..._.--.. \n";
	std::cout << "                                                                                \n";
	std::cout << "                _____________________________________________                   \n";
	std::cout << "               /                                             \\	              \n";
	std::cout << "              /           Welcome to Bulls and Cows           \\                \n";
	std::cout << "              \\               A fun word game!                /                \n";
	std::cout << "               \\_____________________________________________/	              \n";
	std::cout << "                                                                                \n";
	std::cout << "                                                                                \n";
	std::cout << " -.-.,,._,-.--._.--,--'`,,'`,---..-_,,..._.--..-..-..-.--+-....__---._.-,--.--- \n";
	std::cout << "                                                                                \n";
	std::cout << "                                                                                \n";
	std::cout << "                         ,@@@@@@@,              _.-^-._         +&-             \n";
	std::cout << "                 ,,,.   ,@@@@@@/@@,         .-'---------'-.    .--.             \n";
	std::cout << "               ,&%%&%&&%,@@@@@/@@@@@     .-'-------_-------'-. |__|             \n";
	std::cout << "              ,%&\\%&&%&&%,@@@\\@@@/@@    /---------|_|---------\\|  |          \n";
	std::cout << "              %&&%&%&/%&&%@@\\@@/ /@@   / _____           _____ \\  |           \n";
	std::cout << "              %&&%/ %&%%&&@@\\ V /@@'  /| |_|_|  _______  |_|_| |\\ |           \n";
	std::cout << "              `&%\\|o|/%&'    |.|       | |_|_|  |==|==|  |_|_| |  |            \n";
	std::cout << " |---|---|---|---|---|---|---|---|---|-|        |--|--|        |  |--|---|---|- \n";
	std::cout << " |---|---|---|---|---|---|---|---|---|-|        |==|==|        |  |--|---|---|- \n";
	std::cout << " '-'''-'-''-''-''''-''-'''-''''-''-'''-'''''-''-'''-'-''-'''''-''-'''-''-''-''' \n";
	std::cout << " ' 'VV'   '  ''' ' '  '  ''       ' '   '''   'VV ''   '''' ' ''    '  ' ''V    \n";
	std::cout << "  ''' ' VV'   'vv '  vv'   }___{  '''VV'  ''''  '  ___ '''  '  VVV' ' V''  '' ' \n";
	std::cout << " ''' ' '  ' ''      ''     (o o)  ' '' vv'' '     (o o)      '   ''  v  '   VVV \n";
	std::cout << "  '''V    'V   '''  /-------\\ /  '''     ''  '     \\ /-------\\   '''  '   '' \n";
	std::cout << "  ''  ' '' '' '    / | BULL |O     ''  '    'vvv    O| COW  | \\   '''vv ' 'V   \n";
	std::cout << "    'vv  '''      *  |-,--- |   ''vvv'   '   ''   '  |------|  *    '  ''   ''  \n";
	std::cout << "  ''    'v'' ' ''    ^   '  ^ '  '''   '    ''''     ^ '''  ^ ' '' ''  '''  ' v \n";
	std::cout << "    ''    vV '''  VV  ''    V  ' '' 'VV '''   ' Vv''   '''' ' ''V   'V  v'    ' \n";
	std::cout << " '  ''    '     '''   '' '    ''  vv      '  '     ''   ''     '    ' '   '''   \n";
	std::cout << " ''-'-''-''-''-''''-''-'''-''''-''-'''-''''''-'-'''-''-'''-'-''-'''''-''-'-'''- \n";
	std::cout << std::endl;
	std::cout << "    ***********************************************************************     \n";
	std::cout << "    *  INSTRUCTION: In this game, you'll guess an ISOGRAM with the        *     \n";
	std::cout << "    *  length of your choice in 5 turns. After each guess, you'll see the *     \n";
	std::cout << "    *  the number of BULLS and COWS.                                      *     \n";
	std::cout << "    *                                                                     *     \n";
	std::cout << "    *  BULLS is the number of letter you guessed right in the right place *     \n";
	std::cout << "    *  COWS is the number of letter you guessed right in the wrong place  *     \n";
	std::cout << "    *                                                                     *     \n";
	std::cout << "    *                    *** What is an ISOGRAM? ***                      *     \n";
	std::cout << "    *      *** An ISOGRAM is a word WITHOUT a repeating letter ***        *     \n";
	std::cout << "    *                                                                     *     \n";
	std::cout << "    ***********************************************************************     \n";
	std::cout << std::endl;
	std::cout << "    ***********************************************************************     \n";
	std::cout << "    *                     -~~:+|    NEW GAME    |+:~~-                    *     \n";
	std::cout << "    ***********************************************************************     \n";
	return;
}
void Initialize()
{
	// variables
	int32 WordLength = 0;

	WordLength = AskWordLength();
	BullCowGame.Initialize(WordLength, 5);

	std::cout << std::endl;

	return;
}
void PrintHint()
{
	std::cout << "Can you guess the \"" << BullCowGame.GetHiddenWordLength() << "\" isogram that I'm thinking of?\n\n";
	std::cout << "    ***********************************************************************     \n";
	std::cout << "    *                             !!! HINT !!!                            *     \n";
	std::cout << "    ***********************************************************************     \n";
	std::cout << "         LENGTH: " << BullCowGame.GetHiddenWordLength() << " letters.			  \n";
	std::cout << "         DESCRIPTION: " << BullCowGame.GetHiddenWordDescription() << "		  \n";
	std::cout << "    ***********************************************************************     \n";
	std::cout << std::endl;
	return;
}
void RunGameLoop()
{
	// variables
	int32 MaxTries = BullCowGame.GetMaxTries();
	FText Guess = "";

	// will ask player when he/she has the number of turn(s) left that is within the MIN and MAX_TURN_FOR_HINT
	// if they need a hint
	constexpr int32 MIN_TURN_FOR_HINT = 1;
	constexpr int32 MAX_TURN_FOR_HINT = 3;
	int32 RandomTurnForHint = 0;
	int32 TriesLeft = 0;

	bool bPlayAgain = false;
	bool bWantHint = false;

	std::cout << "You have " << BullCowGame.GetMaxTries() << " tries to guess the word!\n\n";

	do
	{
		RandomTurnForHint = GetRandomInteger(MIN_TURN_FOR_HINT, MAX_TURN_FOR_HINT);

		// loop while is NOT won and there are still tries remaining
		while (!BullCowGame.IsGameWon() && BullCowGame.GetCurrentTry() <= MaxTries)
		{
			Guess = GetValidGuess();

			// submit valid guess to the game and receive counts
			FBullCowCount BullCowCount = BullCowGame.SubmitValidGuess(Guess);

			std::cout << "BULLS [" << BullCowCount.Bull << "]";
			std::cout << "   COWS [" << BullCowCount.Cow << "]\n";

			PrintGuess(Guess);

			TriesLeft = BullCowGame.GetTriesLeft();
			// ask if want hint when tries left equals one of the number within the MIN MAX range
			// see the constexpr above for clarification
			if (TriesLeft == RandomTurnForHint)
			{
				bWantHint = AskIfWantHint();

				if (bWantHint)
				{
					PrintHint();
				}
			}
		}

		// print end game message
		PrintGameSummary();
		std::cout << std::endl;

		bPlayAgain = AskToPlayAgain();

	}
	while (bPlayAgain);

	return;
}
FText GetValidGuess()
{
	// variables
	int32 CurrentTry = BullCowGame.GetCurrentTry();
	FText Guess = "";
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

	} while (GuessStatus != EGuessStatus::OK);

	return Guess;
}
void PrintGuess(FText Guess)
{
	// print user input
	std::cout << "Your guess was: " << Guess << std::endl;
	std::cout << std::endl;

	return;
}
void PrintGameSummary()
{
	std::cout << "The hidden word is: " << BullCowGame.GetHiddenWord() << "\n\n";

	if (BullCowGame.IsGameWon())
	{
		std::cout << "Well done - You WIN!\n";
	}
	else
	{
		std::cout << "You've used all your tries! Better luck next time...\n";
	}

	return;
}
bool AskToPlayAgain()
{
	FText Response = "";
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
int32 AskWordLength()
{
	// variables
	FText WordLength = "";
	int32 IWordLength = 0;

	EWordLengthStatus WordLengthStatus = EWordLengthStatus::Invalid_Status;

	do
	{
		std::cout << "How many letter isogram do you want to try (from 3 to 10)? ";
		std::getline(std::cin, WordLength);

		WordLengthStatus = BullCowGame.CheckWordLengthValidity(WordLength);

		switch (WordLengthStatus)
		{
		case EWordLengthStatus::OK:
			break;
		case EWordLengthStatus::Not_In_Range:
			std::cout << "The number you just entered is not in range, please enter another number.\n\n";
			break;
		case EWordLengthStatus::Not_Number:
			std::cout << "The input you just entered is not a number, please enter a number.\n\n";
			break;
		case EWordLengthStatus::Has_White_Space:
			std::cout << "The input you just entered has white space, please enter a number without white space.\n\n";
			break;
		case EWordLengthStatus::No_Word_With_This_Length:
			std::cout << "There is NO or NO MORE word with this length, please enter a different number.\n\n";
			break;
		default:
			break;
		}

	} while (WordLengthStatus != EWordLengthStatus::OK);

	IWordLength = StringToInt32(WordLength);

	return IWordLength;
}
bool AskIfWantHint()
{
	FText Response = "";

	std::cout << "You have " << BullCowGame.GetTriesLeft() << " tries left\n";
	std::cout << "You can ask for a hint this round.\n";

	EYesNoAnswerStatus AnswerStatus = EYesNoAnswerStatus::Invalid_Status;

	do
	{
		std::cout << "Do you want a hint for this isogram (y/n)?";
		std::getline(std::cin, Response);

		AnswerStatus = CheckYesNoAnswerStatus(Response);

	} while (AnswerStatus != EYesNoAnswerStatus::OK);

	return (tolower(Response[0]) == 'y');
}
EYesNoAnswerStatus CheckYesNoAnswerStatus(FString Answer)
{
	if (!IsYesOrNo(Answer))
	{
		std::cout << "Please enter Yes or No.\n\n";
		return EYesNoAnswerStatus::Not_Yes_And_Not_No;
	}
	else if (IsFirstCharWhiteSpace(Answer))
	{
		std::cout << "Please enter Yes or No without white space infront.\n\n";
		return EYesNoAnswerStatus::First_Char_White_Space;
	}
	else
	{
		return EYesNoAnswerStatus::OK;
	}

}

bool IsYesOrNo(FString Word)
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
bool IsFirstCharWhiteSpace(FString Word)
{
	char Letter = Word[0]; 

	if (Letter == ' ') // if is blank space
	{
		return true; // has white space
	}

	return false;
}

void PrintWordsInDictionary() 
{
	TMap<int32, TArray<FText>> Dictionary = BullCowGame.GetDictionary();

	for (auto Iterator = Dictionary.begin(); Iterator != Dictionary.end(); ++Iterator)
	{
		std::cout << "ID: " << Iterator->first;
		std::cout << "   Word: " << Iterator->second[0];
		std::cout << "   Definition: " << Iterator->second[1] << std::endl;
	}
	
	return;
}
int32 StringToInt32(FString String)
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

int32 GetRandomInteger(int32 Min, int32 Max)
{
	int32 RandomNumber = 0;
	RandomGenerator.seed((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int32> RandomIntegerDistribution(Min, Max);
	return RandomNumber = RandomIntegerDistribution(RandomGenerator);
}

void TEST_CSVFileWrite()
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