#include "LevellingUI.h"

void LevellingUI::display_frame()
{
	std::array<std::string,5> outputSelections = {};
	
	// Lines of text of which the player cannot interact with are outputted
	std::cout << "Level - " << User.get_level() << std::endl;
	std::cout << "Experience - " << User.get_experience() << "/" <<  User.get_level()*5 + 5 << std::endl;
	std::cout << "Used experience points - " << levelController.get_usedPoints() << "/" << User.get_experiencePoints() << "\n\n";
	
	// Interable lines of text are stored in an array
	outputSelections[0] = "Max health - " + std::to_string(User.get_maxHealth()) + " | +" + std::to_string(levelController.get_alter_maxHealth());
	outputSelections[1] = "Attack - " + std::to_string(User.get_attack()) + " | +" + std::to_string(levelController.get_alter_attack());
	outputSelections[2] = "Defence - " + std::to_string(User.get_defence()) + " | +" + std::to_string(levelController.get_alter_defence());
	
	outputSelections[3] = "Confirm";
	outputSelections[4] = "Reset";
	
	// Deduces which line/option is selected by the user
	int selection = levelController.get_levellingOption();
	
	// Outputs all lines in the "outputSelections" array with the selected line surrounded by arrows to indicate that is it currently selected
	outputSelections[selection] = ">> " + outputSelections[selection] + " <<";
	for (int i=0; i<outputSelections.size(); i++)
	{
		std::cout << outputSelections[i] << std::endl;
		// Empty line for formatting
		if (i == 2)
		{
			std::cout << std::endl;
		}
	}
}

void LevellingUI::a_key()
{
	clear_screen();
	if (levelController.get_levellingOption() < 3)
	{
		levelController.adjust_stat(levelController.get_levellingOption(), -1);
	}
	display_frame();
}

void LevellingUI::d_key()
{
	clear_screen();
	if (levelController.get_levellingOption() < 3)
	{
		levelController.adjust_stat(levelController.get_levellingOption(), 1);
	}
	display_frame();
}

void LevellingUI::w_key()
{
	clear_screen();
	levelController.previous_levellingOption();
	display_frame();
}

void LevellingUI::s_key()
{
	clear_screen();
	levelController.next_levellingOption();
	display_frame();
}

void LevellingUI::z_key()
{
	clear_screen();
	switch (levelController.get_levellingOption())
	{
		case 3:
			levelController.confirm(User);
			returnInt = 1;
			break;
		case 4:
			levelController.reset();
	}
	display_frame();
}

void LevellingUI::run_loop(Player &User)
{
    clear_screen();
	display_frame();
	// Loops until the player confirms their stat changes
    while(true) {
    	int result = ui_loop();
        if (result == 1)
        {
        	break;
		}
    }
}


