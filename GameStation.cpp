
/* This is the console executable that makes use of the FBullCowGame class
This acts as the view in a MVC pattern, and is responsible for all user
interaction. For game logic, see FBullCowGame class.
*/

#include "BullCowGameManager.h"
#include "FBullCowGame.h"

static BullCowGameManager GameCartridge;

int main()
{
	//PrintWordsInDictionary();

	GameCartridge.PowerON();

	/*for (int32 i = 0; i < 5; i++)
	{
		TEST_CSVFileWrite();
	}*/

	return 0; // exit application
}