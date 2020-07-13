#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
	: CurrentTry(0), MaxTries(0), MinWordLength(0), MaxWordLength(0),
	MinCombinationLength(3), MaxCombinationLength(9),
	MaxHint(0), GameMode(EGameMode::Invalid_Mode),
	IsogramDictionary(GetIsogramDictionaryFromFile("Isogram Word Bank.csv"))
{
}
FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::Initialize(EGameMode GameMode, int32 WordLength)
{
	bIsGoingToMenu = false;
	this->GameMode = GameMode;

	switch (GameMode)
	{
	case EGameMode::Invalid_Mode:
		break;
	case EGameMode::Mode_Word:
		InitWordGame(WordLength);
		break;
	case EGameMode::Mode_Combination:
		InitCombinationGame(WordLength);
		break;
	default:
		break;
	}

	return;
}
void FBullCowGame::InitWordGame(int32 WordLength)
{
	WordAndDefinition = GetWordAndDefinitionFromDictionary(WordLength, IsogramDictionary);
	CurrentTry = 1;
	this->MaxTries = CalculateMaxTries((int32)WordAndDefinition[0].length());
	CurrentHint = 1;
	MaxHint = CalculateMaxHint((int32)WordAndDefinition[0].length());
	InitializeHintSystem(WordLength);
}
void FBullCowGame::InitCombinationGame(int32 CombinationLength)
{
	LockCombination = GenerateRandomUniqueNumber(CombinationLength);
	CurrentTry = 1;
	this->MaxTries = CalculateMaxTries((int32)LockCombination.length());
	CurrentHint = 1;
	MaxHint = CalculateMaxHint((int32)LockCombination.length());
	InitializeHintSystem(CombinationLength);
}

FString FBullCowGame::WordGameIntro() const
{
	FString label =
	"                _____________________________________________                   \n"
	"               /                                             \\	             \n"
	"              /           Welcome to Bulls and Cows           \\                \n"
	"              \\               Word Game Mode!                 /                \n"
	"               \\_____________________________________________/	             \n"
	"                                                                                \n";
	return label;
}

FString FBullCowGame::CombinationGameIntro() const
{
	FString label =
	"                _____________________________________________                   \n"
	"               /                                             \\	             \n"
	"              /           Welcome to Bulls and Cows           \\                \n"
	"              \\          Lock Combination Game Mode!          /                \n"
	"               \\_____________________________________________/	             \n"
	"                                                                                \n";
	return label;
}

void FBullCowGame::BullCowGameIntro(EGameMode gameMode)
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
	
	switch (gameMode)
	{
	case EGameMode::Mode_Word:
		std::cout << WordGameIntro();
		break;
	case EGameMode::Mode_Combination:
		std::cout << CombinationGameIntro();
		break;
	default:
		break;
	}
	
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
	std::cout << "    *                    *** What is an ISOGRAM? ***                      *     \n";
	std::cout << "    *      *** An ISOGRAM is a word WITHOUT a repeating letter ***        *     \n";
	std::cout << "    *                                                                     *     \n";
	std::cout << "    *  INSTRUCTION: In this game, you'll guess an ISOGRAM with the length *     \n";
	std::cout << "    *  of your choice in a limited turns. After each guess, you'll see    *     \n";
	std::cout << "    *  the number of BULLS and COWS.                                      *     \n";
	std::cout << "    *                                                                     *     \n";
	std::cout << "    *  BULLS is the number of letter you guessed right in the right place *     \n";
	std::cout << "    *  COWS is the number of letter you guessed right in the wrong place  *     \n";
	std::cout << "    *                                                                     *     \n";
	std::cout << "    ***********************************************************************     \n";
	std::cout << std::endl;
	std::cout << "    ***********************************************************************     \n";
	std::cout << "    *                     -~~:+|    NEW GAME    |+:~~-                    *     \n";
	std::cout << "    ***********************************************************************     \n";
	std::cout << std::endl;
	return;
}

int32 FBullCowGame::GetMinWordLength() const { return MinWordLength; }
int32 FBullCowGame::GetMaxWordLength() const { return MaxWordLength; }
int32 FBullCowGame::GetMinCombinationLength() const { return MinCombinationLength; }
int32 FBullCowGame::GetMaxCombinationLength() const { return MaxCombinationLength; }
int32 FBullCowGame::GetMaxTries() const { return MaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
int32 FBullCowGame::GetTriesLeft() const { return MaxTries - CurrentTry + 1; }

FString FBullCowGame::GetDebugString(EGameMode gameMode)
{
	switch (gameMode)
	{
	case EGameMode::Mode_Word:
		return GetHiddenWord();
	case EGameMode::Mode_Combination:
		return GetLockCombination();
	}
	return "";
}

FString FBullCowGame::GetHiddenWord() const { return WordAndDefinition[0]; }
FString FBullCowGame::GetHiddenWordDefinition() const { return WordAndDefinition[1]; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32)WordAndDefinition[0].length(); }
FString FBullCowGame::GetLockCombination() const { return LockCombination; }
int32 FBullCowGame::GetLockCombinationLength() const { return (int32)LockCombination.length(); }
FString FBullCowGame::GetHint()
{
	FString HintWord = "";
	char Character = ' ';
	int32 Index = 0;


	// if had shown all letters return blank
	if (!HasShownAllLetters())
	{
		do
		{
			// randomized index
			Index = GetRandomInteger(0, (int32)Hint.size() - 1);
			// get letter from word at randomized index
			switch (GameMode)
			{
			case EGameMode::Invalid_Mode:
				break;
			case EGameMode::Mode_Word:
				Character = WordAndDefinition[0][Index];
				break;
			case EGameMode::Mode_Combination:
				Character = LockCombination[Index];
				break;
			default:
				break;
			}

		} while (IsHintLetterShown(Character));

		// populate hint letter shown
		HintShown.push_back(Character);

		// replace "_" with a random letter taken from hidden word
		Hint[Index] = Character;
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
FString FBullCowGame::GetAIName() const
{
	return AIName;
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

void FBullCowGame::PrintCommandListAndDescription() const
{
	std::cout << AIName;
	std::cout << ": Here is the command list for the game in case you need it\n";
	std::cout << "\n*******************************************\n";
	std::cout << "COMMAND LIST:\n";
	std::cout << "debug - for debugging purpose\n";
	std::cout << "hint - revealing a letter in the hidden word\n";
	std::cout << "giveup - give up the round\n";
	std::cout << "menu - go to menu\n";
	std::cout << "exit - quit the program\n";
	std::cout << "command list - print available command list\n";
	std::cout << "*******************************************\n";
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
bool FBullCowGame::IsGoingToMenu() const { return bIsGoingToMenu; }
bool FBullCowGame::HasShownAllLetters() const { return HintShown.size() == Hint.size(); }

EWordGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (IsCommand(Guess)) // if guess is command expression
	{
		return EWordGuessStatus::Is_Command;
	}
	else if (HasWhiteSpace(Guess)) // if guess has white space
	{
		return EWordGuessStatus::Has_White_Space;
	}
	else if (!IsIsogram(Guess)) // if guess isn't isogram
	{
		return EWordGuessStatus::Is_Not_Isogram;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if guess doesn't have right length
	{
		return EWordGuessStatus::Wrong_Length;
	}
	else // otherwise return Ok
	{
		return EWordGuessStatus::OK;
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
	else if (IWordLength > MaxWordLength || IWordLength < MinWordLength)
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
ECombinationGuessStatus FBullCowGame::CheckCombinationGuessValidity(FString Guess) const
{
	if (IsCommand(Guess)) // if guess is command expression
	{
		return ECombinationGuessStatus::Is_Command;
	}
	else if (HasWhiteSpace(Guess)) // if guess has white space
	{
		return ECombinationGuessStatus::Has_White_Space;
	}
	else if (!IsNumber(Guess)) // if guess has white space
	{
		return ECombinationGuessStatus::Is_Not_Number;
	}
	else if (Guess.length() != GetLockCombinationLength()) // if guess doesn't have right length
	{
		return ECombinationGuessStatus::Wrong_Length;
	}
	else // otherwise return Ok
	{
		return ECombinationGuessStatus::OK;
	}
}
ECombinationLengthStatus FBullCowGame::CheckCombinationLengthValidity(FString CombinationLength) const
{
	// will return -1 if cannot conver to integer
	int32 ICombinationLength = StringToInt32(CombinationLength);

	if (HasWhiteSpace(CombinationLength))
	{
		return ECombinationLengthStatus::Has_White_Space;
	}
	else if (ICombinationLength == -1)
	{
		return ECombinationLengthStatus::Not_Number;
	}
	else if (ICombinationLength > MaxCombinationLength || ICombinationLength < MinCombinationLength)
	{
		return ECombinationLengthStatus::Not_In_Range;
	}
	else
	{
		return ECombinationLengthStatus::OK;
	}
}

void FBullCowGame::ExecuteCommand(FString Command)
{
	ECommandAction CommandAction = GetCommandAction(Command);
	
	switch (CommandAction)
	{
	case ECommandAction::Invalid:
		std::cout << AIName;
		std::cout << ": Command Invalid.\n\n";
		break;
	case ECommandAction::Debug:
		std::cout << "[DEBUG] The combination is [" << GetDebugString(GameMode) << "]\n\n";
		break;
	case ECommandAction::Hint:
		std::cout << AIName;
		if (IsEligibleForHint())
		{
			std::cout << ": You used " << CurrentHint << " of " << MaxHint << " hints.\n";
			std::cout << AIName << ": Hint letter(s) - " << GetHint() << "\n\n";
			CurrentHint++;
		}
		else
		{
			std::cout << ": You have exhausted your " << MaxHint << " hints.\n\n";
		}
		break;
	case ECommandAction::Exit:
		exit(0);
		break;
	case ECommandAction::Menu:
		Reset();
		bIsGoingToMenu = true;
		break;
	case ECommandAction::Give_Up:
		bIsGivingUp = true;
		break;
	case ECommandAction::Command_List:
		PrintCommandList();
		break;
	default:
		break;
	}
}

FBullCowCount FBullCowGame::SubmitValidWordGuess(FString Guess)
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
			if (tolower(Guess[i]) == WordAndDefinition[0][j])
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
FBullCowCount FBullCowGame::SubmitValidCombinationGuess(FString Guess)
{// received a valid guess, increments turn and returns counts

	CurrentTry++;
	FBullCowCount BullCowCount;
	int32 CombinationLength = GetLockCombinationLength();

	// loop through all letters in the guess
	for (int32 i = 0; i < CombinationLength; i++)
	{
		// compare if same letter different place (cow)
		for (int32 j = 0; j < CombinationLength; j++)
		{
			// compare if same letter same place (bull)
			if (Guess[i] == LockCombination[j])
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
	if (BullCowCount.Bull == CombinationLength)
	{
		bIsGameWon = true; // win
	}
	else
	{
		bIsGameWon = false; // not win
	}

	return BullCowCount;
}

void FBullCowGame::Reset()
{
	bIsGameWon = false;
	bIsGivingUp = false;

	WordAndDefinition.clear();
	LockCombination.clear();
	CurrentTry = 0;
	MaxTries = 0;
	CurrentHint = 0;
	MaxHint = 0;
	Hint.clear();
	HintShown.clear();
}

void FBullCowGame::Reset(EGameMode GameMode, int32 WordLength)
{
	bIsGameWon = false;
	bIsGivingUp = false;
	bIsGoingToMenu = false;

	switch (GameMode)
	{
	case EGameMode::Invalid_Mode:
		break;
	case EGameMode::Mode_Word:
		ResetWordGame(WordLength);
		break;
	case EGameMode::Mode_Combination:
		ResetCombinationGame(WordLength);
		break;
	default:
		break;
	}

	return;
}

void FBullCowGame::ResetWordGame(int32 WordLength)
{
	WordAndDefinition = GetWordAndDefinitionFromDictionary(WordLength, IsogramDictionary);
	CurrentTry = 1;
	MaxTries = CalculateMaxTries(WordLength);
	CurrentHint = 1;
	MaxHint = CalculateMaxHint(WordLength);
	InitializeHintSystem(WordLength);
}

void FBullCowGame::ResetCombinationGame(int32 CombinationLength)
{
	LockCombination = GenerateRandomUniqueNumber(CombinationLength);
	CurrentTry = 1;
	MaxTries = CalculateMaxTries(CombinationLength);
	CurrentHint = 1;
	MaxHint = CalculateMaxHint(CombinationLength);
	InitializeHintSystem(CombinationLength);
}

// helper functions
ECommandAction FBullCowGame::GetCommandAction(FString Command) const
{
	if (Command == "debug") return ECommandAction::Debug;
	else if (Command == "hint") return ECommandAction::Hint;
	else if (Command == "giveup") return ECommandAction::Give_Up;
	else if (Command == "exit") return ECommandAction::Exit;
	else if (Command == "menu") return ECommandAction::Menu;
	else if (Command == "command list") return ECommandAction::Command_List;
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
bool FBullCowGame::IsEligibleForHint() const
{
	int32 TimesHinted = (int32)HintShown.size();
	if (IsGameWon()) return false;
	return (TimesHinted < MaxHint);
}

bool FBullCowGame::IsNumber(FString String) const
{
	for (auto Char : String)
	{
		if (!std::isdigit(Char)) return false;
	}

	return true;
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
	FString Definition = "";
	FString Word = "";
	FString Words[COLUMN] = {}; // used store the broken up words
	char Delimiter = (char)','; // delimiter that determine where to break up the words
	std::stringstream SStream; // used for breaking up words in a line and convert string to integer;

	for (auto Line : Data)
	{
		SStream.clear(); // clear stream in order to feed in new line

		TArray<FString> IsogramAndDefinition;

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
			Definition = Words[2]; // store third element of words array into variable definition

			if (ID == -1) throw Words[0];
		}
		catch (FString Word)
		{
			std::cout << "\n\n***EXCEPTION*** Cannot convert to integer at value " << Word << "\n\n";
			exit(-2);
		}

		IsogramAndDefinition.push_back(Isogram);
		IsogramAndDefinition.push_back(Definition);
		// store word length and word into dictionary at iterator position
		Dictionary.insert({ ID, IsogramAndDefinition });

		// initialize MinLength, MaxLength, and AvaiableID variables
		// this compare the values of min max length of words 
		// and populate integer array so has to be in loop
		InitializingSomePrivateVariables(ID, (int32)Isogram.length());
	}

	return Dictionary;
}
TArray<FString> FBullCowGame::GetWordAndDefinitionFromDictionary(int32 WordLength, TMap<int32, TArray<FString>> Dictionary)
{
	int32 ID = 0;
	FString Word = "";
	FString Definition = "";
	TArray<FString> WordAndDefinitioin = TArray<FString>();
	bool bHasSeenAllWords = false;

	// if word length is default which means equal to 0, get a random number within min and max length
	while (!IsLengthAvalable(WordLength))
	{
		// generate new random number while word length is not available
		WordLength = GetRandomInteger(MinWordLength, MaxWordLength);
	}

	while (Word.length() != WordLength || !IsIDAvailable(ID))
	{	
		ID = GetRandomInteger(1, (int32)Dictionary.size()); // get random ID number
		Word = Dictionary[ID][0]; // get the word of random ID
	}

	Definition = Dictionary[ID][1]; // set definition

	// populate array
	WordAndDefinitioin.push_back(Word);
	WordAndDefinitioin.push_back(Definition);

	// remove used ID and length
	RemoveUsedIDAndLength(ID);

	return WordAndDefinitioin;
}
FString FBullCowGame::GenerateRandomUniqueNumber(int32 CombinationLength)
{
	TArray<int32> Numbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	FString LockCombination = "";
	int32 RandomUniqueNumber = 0;
	int32 Index = 0;
	int32 Temp = 0;
	int32 Max = (int32)Numbers.size() - 1;

	// generating unique random number
	for (size_t i = 0; i < CombinationLength; i++)
	{
		Temp = Numbers[Max]; // save the value of the last number in numbers array
		Index = GetRandomInteger(0, Max); // get random index
		RandomUniqueNumber = Numbers[Index]; // pick a number at that index from numbers array
		Numbers[Max] = RandomUniqueNumber; // step 1 of swapping position of random number and last number in array
		Numbers[Index] = Temp; // step 2 of swapping position of random number and last number in array
		Max--; // decrease max - meaning last value is no longer unique

		LockCombination.append(std::to_string(RandomUniqueNumber)); // append to string
	}

	return LockCombination;
}
int32 FBullCowGame::CalculateMaxTries(int32 WordLength)
{
	return WordLength * 2;
}
int32 FBullCowGame::CalculateMaxHint(int32 WordLength)
{
	if (WordLength == 3) return 1;
	int32 MaxHint = (int32)std::ceil((float)WordLength / 2);
	return MaxHint;
}

void FBullCowGame::InitializingSomePrivateVariables(int32 ID, int32 WordLength)
{
	// 1. populate available ID and length table
	AvailableIDAndLengthTable.insert({ ID, WordLength });

	// 2. find min and max value
	if (ID == 1)
	{
		MinWordLength = WordLength;
		MaxWordLength = MinWordLength;
	}

	if (WordLength < MinWordLength) MinWordLength = WordLength;
	if (WordLength > MaxWordLength) MaxWordLength = WordLength;

	return;
}
void FBullCowGame::InitializeHintSystem(int32 WordLength)
{
	Hint.clear();
	HintShown.clear();

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
	for (auto HLetter : HintShown)
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
