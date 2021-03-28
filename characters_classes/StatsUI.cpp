#include "StatsUI.h"


// Used to display the mandatory details for each frame
void StatsUI::display_frame()
{
	// Statements to output necessary data
	// Sequential rather than iterative for readability
	std::cout << "Total score: " <<User.get_statistic("totalScore") << "\n\n";
	std::cout << "Total experience gained: " << User.get_statistic("totalExperienceGained") << "\n";
	std::cout << "Total enemies defeated: " << User.get_statistic("totalEnemiesDefeated") << "\n";
	std::cout << "Total deaths: " << User.get_statistic("totalDeaths") << "\n";
	std::cout << "Total damage dealt: " << User.get_statistic("totalDamageDealt") << "\n";
	std::cout << "Total damage received: " << User.get_statistic("totalDamageReceived") << "\n";
	std::cout << "Total damage mitigated: " << User.get_statistic("totalDamageMitigated") << "\n\n";
	
	std::cout << "Total gold gained: " << User.get_statistic("totalGoldGained") << "\n";
	std::cout << "Total gold spent: " << User.get_statistic("totalGoldSpent") << "\n\n";
	
	std::cout << ">> Return <<";
}

void StatsUI::z_key()
{
	// Sets the returnInt attribute to 1 which ends the UI loop
	returnInt = 1;
}

void StatsUI::run_loop(Player &User)
{
    clear_screen();
	display_frame();
	// Loops until combat ends
    while(true) {
    	int result = ui_loop();
        if (result == 1)
        {
        	break;
		}
    }
}

