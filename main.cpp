
/* This is the console executable that makes use of the FBullCowGame class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic, see FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

#define FText std::string
#define int32 int


void PrintIntroduction();
void PrintHint();
void RunGameLoop();
FText GetValidGuess();
void PrintGuess(FText Guess);
void PrintGameSummary();
bool AskToPlayAgain();
FText AskWordLength();

void PrintWordsInDictionary();

//static FBullCowGame BullCowGame(3);
FBullCowGame BullCowGame(5);

int main()
{
	//PrintWordsInDictionary();
	
	PrintIntroduction();

	RunGameLoop();

	return 0; // exit application
}

void PrintIntroduction()
{
	// introduction
	std::cout << "              .                                                                 \n";
	std::cout << "               		                                                          \n";
	std::cout << "              |		                                                          \n";
	std::cout << "     .               /                                                          \n";
	std::cout << "      \\       I     	                                                          \n";
	std::cout << "                  /                                                             \n";
	std::cout << "        \\  ,g88R_                                                              \n";
	std::cout << "          d888(`  ).                               _                         __ \n";
	std::cout << " -  --==  888(     ).=--                _      .+(`  )`.              .--._.'  '\n";
	std::cout << ")         Y8P(       '`.            _+(   ) --:(   .    )          .=(         )\n";
	std::cout << "        .+(`(      .   )       .-- '      _   `.  (    ) )         (   .  )   ) \n";
	std::cout << "       ((    (..__.:'-'     .=(   )     (   )   ` _`  ) )         (   (   ))    \n";
	std::cout << "`.     `(       ) )         (   .  )    ''    )    (   )    ._      `- __.'     \n";
	std::cout << "  )      ` __.:'   )       (   (   )) (  (     ) _: `-'  .:(`  )           (    \n";
	std::cout << ")  )  ( )       --'         `- __.'     -+_ _:'         :(      ))          '-__\n";
	std::cout << ".-'  (_.'          .')                                  `(    )  ))             \n";
	std::cout << "                  (_  )                                   ` __.:'               \n";
	std::cout << "                                       	                                      \n";
	std::cout << "-..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._.---.-'`,---..-_.--,-,,..._.--..-.\n";
	std::cout << "                                                                                \n";
	std::cout << "               _____________________________________________                    \n";
	std::cout << "              /                                             \\	              \n";
	std::cout << "             /           Welcome to Bulls and Cows           \\                 \n";
	std::cout << "             \\               A fun word game!                /                 \n";
	std::cout << "              \\_____________________________________________/	              \n";
	std::cout << "                                                                                \n";
	std::cout << "                                                                                \n";
	std::cout << "-.-.,,._,-.--._.--,--'`,,'`,---..-_,,..._.--..-..-..-.--+-....__---._.-,--.---,-\n";
	std::cout << "                                                                                \n";
	std::cout << "                                                                                \n";
	std::cout << "                        ,@@@@@@@,              _.-^-._         +&-              \n";
	std::cout << "                ,,,.   ,@@@@@@/@@,         .-'         '-.    .--.              \n";
	std::cout << "              ,&%%&%&&%,@@@@@/@@@@@     .-'       _       '-. |__|              \n";
	std::cout << "             ,%&\\%&&%&&%,@@@\\@@@/@@    /         |_|         \\|  |           \n";
	std::cout << "             %&&%&%&/%&&%@@\\@@/ /@@   /   __             __   \\  |            \n";
	std::cout << "             %&&%/ %&%%&&@@\\ V /@@'  /|  |  |  _____    |  |  |\\ |            \n";
	std::cout << "             `&%\\|o|/%&'    |.|       |  |__|  |==|==|  |__|  |  |             \n";
	std::cout << "        |---|---|---|---|---|---|---|-|        |--|--|        |  |              \n";
	std::cout << "        |---|---|---|---|---|---|---|-|        |==|==|        |  |              \n";
	std::cout << "'-'''-'-''-''-''''-''-'''-''''-''-'''-'''''-''-'''-'-''-'''''-''-'''-''-''-''''-\n";
	std::cout << "' 'VV'   '  ''' ' '  '  ''       ' '   '''   'VV ''   '''' ' ''    '  ' ''V   ' \n";
	std::cout << " ''' ' VV'   'vv '  vv'   }___{  '''VV'  ''''  '  ___ '''  '  VVV' ' V''  '' '''\n";
	std::cout << "''' ' '  ' ''      ''     (o o)  ' '' vv'' '     (o o)      '   ''  v  '   VVV '\n";
	std::cout << " '''V    'V   '''  /-------\\ /  '''     ''  '     \\ /-------\\   '''  '   ''' \n";
	std::cout << " ''  ' '' '' '    / | BULL |O     ''  '    'vvv    O| COW  | \\   '''vv ' 'V    \n";
	std::cout << "   'vv  '''      *  |-,--- |   ''vvv'   '   ''   '  |------|  *    '  ''   ''   \n";
	std::cout << " ''    'v'' ' ''    ^   '  ^ '  '''   '    ''''     ^ '''  ^ ' '' ''  '''  ' v' \n";
	std::cout << "   ''    vV '''  VV  ''    V  ' '' 'VV '''   ' Vv''   '''' ' ''V   'V  v'    '' \n";
	std::cout << "'  ''    '     '''   '' '    ''  vv      '  '     ''   ''     '    ' '   '''  ''\n";
	std::cout << "''-'-''-''-''-''''-''-'''-''''-''-'''-''''''-'-'''-''-'''-'-''-'''''-''-'-'''-'-\n";
	std::cout << std::endl;
	return;
}

void PrintHint()
{
	std::cout << "Here is a hint!\n\n";
	std::cout << "Word length: " << BullCowGame.GetHiddenWordLength() << " letters.\n";
	std::cout << "Description: " << BullCowGame.GetHiddenWordDescription() << "\n\n";
	std::cout << "You have " << BullCowGame.GetMaxTries() << " tries to guess the word!\n\n";

	return;
}

void RunGameLoop()
{
	// variables
	int32 MaxTries = BullCowGame.GetMaxTries();
	FText Guess = "";

	bool bPlayAgain = false;

	do
	{
		// reset game
		if (bPlayAgain) BullCowGame.Reset();

		PrintHint();

		// loop while is NOT won and there are still tries remaining
		while (!BullCowGame.IsGameWon() && BullCowGame.GetCurrentTry() <= MaxTries)
		{
			Guess = GetValidGuess();

			// submit valid guess to the game and receive counts
			FBullCowCount BullCowCount = BullCowGame.SubmitValidGuess(Guess);

			std::cout << "Bulls = " << BullCowCount.Bull;
			std::cout << "   Cow = " << BullCowCount.Cow << "\n";

			PrintGuess(Guess);
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
		std::cout << "Try " << CurrentTry << " of " << BullCowGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
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
	FText WordLength = "";

	std::cout << "Do you want to play again(y/n)? ";
	std::getline(std::cin, Response);

	if (tolower(Response[0]) == 'y')
	{
		WordLength = AskWordLength();
		BullCowGame.SetUserIndicatedWordLength(WordLength);
	}

	std::cout << std::endl;

	return (tolower(Response[0]) == 'y');
}

FText AskWordLength()
{
	// variables
	FText WordLength;
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
			std::cout << "The number you just entered is not in range, please enter another number.\n";
			break;
		case EWordLengthStatus::Not_Number:
			std::cout << "The input you just entered is not a number, please enter a number.\n";
			break;
		case EWordLengthStatus::Has_White_Space:
			std::cout << "The input you just entered has white space, please enter a number without white space.\n";
			break;
		case EWordLengthStatus::No_Word_With_This_Length:
			std::cout << "There is NO or NO MORE word with this length, please enter a different number.\n";
			break;
		default:
			break;
		}

	} while (WordLengthStatus != EWordLengthStatus::OK);

	return WordLength;
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