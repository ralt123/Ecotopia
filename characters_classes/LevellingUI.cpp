#include "LevellingUI.h"

Player User({0,0});
levelControl levelController(User);

// Used to display the mandatory details for each frame
void displayFrame(Player &User)
{
	std::array<std::string,5> outputSelections = {};
	//outputSelections[0] = "Level - " + User.get_level();
	//outputSelections[1] = "Experience - " + User.get_experience() + "/" + (level*5 + 5) + "\n\n";
	
	
	std::cout << "Level - " << User.get_level() << std::endl;
	std::cout << "Experience - " << User.get_experience() << "/" <<  User.get_level()*5 + 5 << std::endl;
	std::cout << "Used experience points - " << levelController.get_usedPoints() << "/" << User.get_experiencePoints() << "\n\n";
	
	outputSelections[0] = "Max health - " + std::to_string(User.get_maxHealth()) + " | +" + std::to_string(levelController.get_alter_maxHealth());
	outputSelections[1] = "Attack - " + std::to_string(User.get_attack()) + " | +" + std::to_string(levelController.get_alter_attack());
	outputSelections[2] = "Defence - " + std::to_string(User.get_defence()) + " | +" + std::to_string(levelController.get_alter_defence());
	
	outputSelections[3] = "Confirm";
	outputSelections[4] = "Reset";
	
	int selection = levelController.get_levellingOption();
	
	outputSelections[selection] = ">> " + outputSelections[selection] + " <<";
	for (int i=0; i<outputSelections.size(); i++)
	{
		std::cout << outputSelections[i] << std::endl;
		if (i == 2)
		{
			std::cout << std::endl;
		}
	}
}

// Clears the screen (Hopefully a better method of clearing the screen will be found in time)
void clearScreen()
{
	system("CLS");
}
int LevellingUILoop(Player &User)
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
		if (levelController.get_levellingOption() < 3)
		{
			levelController.adjust_stat(levelController.get_levellingOption(), -1);
		}
		// CombatController.previous_combatOption();
		displayFrame(User);
		break;
	case 100:
	case 68:
		// "d" key pressed, change selected action to next action
		clearScreen();
		if (levelController.get_levellingOption() < 3)
		{
			levelController.adjust_stat(levelController.get_levellingOption(), 1);
		}
		// CombatController.next_combatOption();
		displayFrame(User);
		break;
	// w
	case 119:
	case 87:
		clearScreen();
		levelController.previous_levellingOption();
		displayFrame(User);
		break;
	// s
	case 115:
	case 83:
		clearScreen();
		levelController.next_levellingOption();
		displayFrame(User);
		break;
	case 122:
	case 90:
		// "z" key pressed, confirm selected action
		clearScreen();
		switch (levelController.get_levellingOption())
		{
			case 3:
				levelController.confirm(User);
				return 1;
				break;
			case 4:
				levelController.reset();
		}
		displayFrame(User);
		/*
		if (CombatController.get_combatOption() == 0)
		{
			attack += 1;
		}
		else
		{
			displayStaticFrame(User, Foe);
		}
		*/
		break;
	default:
		break;
	}
	// std::cout << character;
	
	SetConsoleMode( hstdin, mode );
	return 0;
}
