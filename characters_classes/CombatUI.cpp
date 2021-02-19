#include "CombatUI.h"

// Used to display the mandatory details for each frame
void displayFrame(Player &User, Alien &Foe)
{
    std::cout << "Player  HP: " << User.get_health() << std::endl;
    std::cout << "Alien  HP: " << Foe.get_health() << std::endl;
    std::string optionOutput = CombatController.getCombatOptionName();
    std::cout << "<-- " << optionOutput << " -->" << std::endl;
}

// Used to display the mandatory frames in addition to the string parameter
void displayCombatFrame(std::string combatIcons, Player &User, Alien &Foe)
{
	std::cout << combatIcons << std::endl;
	displayFrame(User, Foe);
}

// Displays the frame whilst no animation is taking place
void displayStaticFrame(Player &User, Alien &Foe)
{
	std::cout << "P          A" << std::endl;
	displayFrame(User, Foe);
}

// Clears the screen (Hopefully a better method of clearing the screen will be found in time)
void clearScreen()
{
	system("CLS");
}

/* The function that loops whilst the combat ui is shown to the user
Takes a player object and alien object as arguments
Returns an integer - 0 if the player is still in combat, 1 if the enemy died and 2 if the player died
*/
int combatUILoop(Player &User, Alien &Foe)
{
    // Used to allow immediate input
    HANDLE hstdin;
    DWORD  mode;

    hstdin = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hstdin, &mode );
    SetConsoleMode( hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT );  

	// Retrieves the ascii value of the character inputted
    int character = std::cin.get();

	// Runs the statement relevant to the character pressed (non-capital sensitive)
	switch (character)
	{
	case 97:
	case 65:
		// "a" key pressed, change selected action to previous action
		clearScreen();
		CombatController.previous_combatOption();
		displayStaticFrame(User, Foe);
		break;
	case 100:
	case 68:
		// "d" key pressed, change selected action to next action
		clearScreen();
		CombatController.next_combatOption();
		displayStaticFrame(User, Foe);
		break;
	case 122:
	case 90:
		// "z" key pressed, confirm selected action
		clearScreen();
		if (CombatController.get_combatOption() == 0)
		{
			while (true)
			{
				std::string outputString = CombatController.engageCombat(User, Foe);
				if (outputString == std::string(""))
				{
					CombatController.reset_animationTick();
					break;
				}
				else if (outputString == std::string("victory"))
				{
					Sleep(500);
					clearScreen();
					std::cout << "You killed your foe." << std::endl;
					Sleep(1200);
					// Changed to inform the player of exp gained and item drops later in development
					return 1;
				}
				else if (outputString == std::string("defeat"))
				{
					Sleep(500);
					clearScreen();
					std::cout << "Game over." << std::endl;
					Sleep(1200);
					return 2;
				}
				clearScreen();
				displayCombatFrame(outputString, User, Foe);
				
			}
		}
		else
		{
			// CombatController.confirmChoice();
			displayStaticFrame(User, Foe);
		}
		break;
	default:
		break;
	}
	//std::cout << character;
	
	SetConsoleMode( hstdin, mode );
	return 0;
}


