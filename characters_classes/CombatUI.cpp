#include "CombatUI.h"

void CombatUI::display_frame(Player &User, Alien &Foe)
{
	// Outputs health of combating characters
    std::cout << "Player  HP: " << User.get_health() << std::endl;
    std::cout << "Alien  HP: " << Foe.get_health() << std::endl;
    
    // Outputs player's current option during combat
    std::string optionOutput = CombatController.getCombatOptionName();
    std::cout << "<-- " << optionOutput << " -->" << std::endl;
    
    // Retrieves and outputs the stats of the characters participating in combat
    std::array<int, 5> playerStats = User.get_stats_array();
    std::array<int, 5> alienStats = Foe.get_stats_array();
    std::cout << "Player: max hp - " << playerStats[0] << "  hp - " << playerStats[1] << "  attack - " << playerStats[2] << "  defence - " << playerStats[3] << "  level - " << playerStats[4] << "\n";
    std::cout << "Alien: max hp - " << alienStats[0] << "  hp - " << alienStats[1] << "  attack - " << alienStats[2] << "  defence - " << alienStats[3] << "  level - " << alienStats[4] << "\n";
}

void CombatUI::display_combat_frame(std::string combatIcons, Player &User, Alien &Foe)
{
	std::cout << combatIcons << std::endl;
	display_frame(User, Foe);
}

void CombatUI::display_static_frame(Player &User, Alien &Foe)
{
	std::cout << "P          " << Foe.characterSymbol << std::endl;
	display_frame(User, Foe);
}

void CombatUI::a_key()
{
	clear_screen();
	CombatController.previous_combatOption();
	display_static_frame(User, Foe);
}

void CombatUI::d_key()
{
	clear_screen();
	CombatController.next_combatOption();
	display_static_frame(User, Foe);
}

void CombatUI::combat_action(Player &User, Alien &Foe, bool defending)
{
	std::string outputString;
	CombatController.animationOngoing = true;
	while (true)
	{
		// Run if the player selected the defense action
		if (defending)
		{
			outputString = CombatController.engageCombat(User, Foe, true);
		}
		// Run if the player selected the attack action
		else
		{
			outputString = CombatController.engageCombat(User, Foe);
		}
		// Combat conducted 
		if (outputString == std::string(""))
		{
			CombatController.reset_animationTick();
			if (not (CombatController.attacking || CombatController.defending))
			{
				CombatController.verbSet = false;
				break;
			}
		}
		// Enemy character is defeated
		else if (outputString == std::string("victory"))
		{
			Sleep(500);
			clear_screen();
			std::string outputText = CombatController.lootEnemy(User, Foe);
			std::cout << outputText << std::endl;
			Sleep(1200);
			returnInt = 1;
			break;
		}
		// Player is defeated
		else if (outputString == std::string("defeat"))
		{
			Sleep(500);
			clear_screen();
			std::array<int, 2> deductions = User.death();
			std::cout << "You have died.\n\nYou lost " << deductions[0] << " and " << deductions[1] << " experience" << std::endl;
			Sleep(1200);
			returnInt = 2;
			break;
		}
		clear_screen();
		display_combat_frame(outputString, User, Foe);
	}
}

void CombatUI::z_key()
{
	switch (CombatController.get_combatOption())
	{
		// Attack option
		case 0:
		{
			combat_action(User, Foe, false);
			break;
		}
		// Inventory option
		case 1:
		{
			User.override_stats(30,30,0,30,0,0);
			break;
		}
		// Defend option
		case 2:
		{
			combat_action(User, Foe, true);
			break;
		}
		// Escape option
		case 3:
		{
			// Add item looting when items are implemented
			int deductedExp = (int)Foe.get_expGiven()/2;
			std::cout << "You cowardly fled from your foe.\nYou lost " << std::to_string(deductedExp) << " experience.\n";
			Sleep(3200);
			returnInt = 1;	
		}
		default:
		{
			display_static_frame(User, Foe);
			break;
		}
	}
}

bool CombatUI::run_loop(Player &, Alien &Foe)
{
	// CombatController.animationOngoing = false;
    clear_screen();
	display_static_frame(User, Foe);
	// Loops until combat ends
    while(true){
    	int result = ui_loop();
        if (result == 1)
        {
        	return false;
		}
		else if (result == 2)
		{
			return true;
		}
    }
}


