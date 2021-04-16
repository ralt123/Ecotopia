#include "CombatControl.h"

CombatControl::CombatControl()
{
	// Default values
    combatOption = 0;
    animationTick = 0;
    animationDelay = 50;
    
	// Used to allow easier seperation of UI functions with the inclusion of animation
	verbSet = false;
	defending = false;
	attacking = false;
	animationOngoing = false;
}

void CombatControl::set_animation_speed(int animationSpeed)
{
	// Ensures animation speed is within the valid bounds (1 - 10)
	if (animationSpeed < 1 || animationSpeed > 10)
	{
		throw std::invalid_argument("Animation speed must be inclusively between 1 and 10");
	}
	// Uses animation speed to set the animation delay
	animationDelay = 10*(9-animationSpeed);
}

int CombatControl::get_animationTick() const
{
	return animationTick;
}
int CombatControl::get_animationDelay() const
{
	return animationDelay;
}
void CombatControl::next_animationTick()
{
	animationTick += 1;
}
void CombatControl::reset_animationTick()
{
	animationTick = 0;
}
int CombatControl::get_combatOption() const
{
    return combatOption;
}

void CombatControl::next_combatOption()
{
    combatOption += 1;
    if (combatOption == 4)
    {
        combatOption = 0;
    }
}

void CombatControl::previous_combatOption()
{
    combatOption -= 1;
    if (combatOption == -1)
    {
        combatOption = 3;
    }
}

std::string CombatControl::get_combat_option_name()
{
    // Returns the name of the current combat option
    switch(get_combatOption())
    {
    	case 0:
    		return "Attack";
    	case 1:
    		return "Inventory";
    	case 2:
    		return "Defend";
    	case 3:
    		return "Escape";
    	default:
    		throw std::invalid_argument("Invalid combatOption");
	}
}

std::string CombatControl::loot_enemy(Player &User, Alien &Foe)
{
	// Add item looting when items are fully implemented
	// Increases the player's gold and experience by the alien goldGiven and expGiven attributes
	int givenExp = Foe.get_expGiven();
	int givenGold = Foe.get_goldGiven();
	// Generates and returns the string to be outputted
	std::string returnString = "You killed your foe.\nYou gained " + std::to_string(givenExp) + " experience and " + std::to_string(givenGold) + " gold.";
	if (User.alter_experience(givenExp))
	{
		returnString += "\nYou have levelled up to level " + std::to_string(User.get_level()) + "\nYou've been fully healed!";
	}
	User.alter_gold(givenGold);
	return returnString;
}

std::string CombatControl::player_defending(Player &User, Alien &Foe)
{
	std::string outputString = "";
	char enemySymbol = Foe.characterSymbol;
	int currentTick = get_animationTick();
	Sleep(animationDelay);
	// Current tick dictates the current animation frame
	if (currentTick < 4)
	{
		outputString = "P          " + std::string(1, enemySymbol);
	}
	else if (currentTick < 14)
	{
		outputString = "P" + std::string(14-currentTick, ' ') + std::string(1, enemySymbol);
	}
	else if (currentTick < 20)
	{
		outputString =  "P" + std::string(1, enemySymbol);
		if (currentTick == 17)
		{
			bool playerDied;
			// Calls the necessary method to inflict damage upon the player
			if (combatOption == 2)
			{
				playSoundEffect("defend.wav");
				playerDied = User.preparedDefend(Foe);
			}
			else
			{
				playSoundEffect("attack.wav");
				playerDied = User.defend(Foe);
			}
			// Run if the player was defeated
			if (playerDied)
			{
				playSoundEffect("gameover.wav");
				Sleep(1000);
				return "defeat";
			}	
		}
	}
	else if (currentTick < 30)
	{
		outputString = "P" + std::string(currentTick-20, ' ') + std::string(1, enemySymbol);
	}
	else if (currentTick < 35)
	{
		outputString = "P          " + std::string(1, enemySymbol);
		// Run for the final tick, resets necessary attributes
		if (currentTick == 34)
		{
			defending = false;
			reset_animationTick();
			animationOngoing = false;
		}
	}
	next_animationTick();
	return outputString;
}

std::string CombatControl::player_attacking(Player &User, Alien &Foe)
{
	char enemySymbol = Foe.characterSymbol;
	std::string outputString = "";
	int currentTick = get_animationTick();
	Sleep(animationDelay);
	// Current tick dictates the current animation frame
	if (currentTick < 4)
	{
		outputString = "P          " + std::string(1, enemySymbol);
	}
	else if (currentTick < 14)
	{
		outputString = std::string((currentTick-4), ' ') + "P" + std::string(14-currentTick, ' ') + std::string(1, enemySymbol);
	}
	else if (currentTick < 20)
	{
		outputString = std::string(10, ' ') + "P" + std::string(1, enemySymbol);
		if (currentTick == 17)
		{
			playSoundEffect("attack.wav");
			// Run if the enemy was defeated
			if (User.attackFoe(Foe))
			{
				Sleep(1000);
				playSoundEffect("victory.wav");
				return "victory";
			}
		}
	}
	else if (currentTick < 30)
	{
		outputString = std::string((30-currentTick), ' ') + "P" + std::string(currentTick-20, ' ') + std::string(1, enemySymbol);
	}
	else if (currentTick < 35)
	{
		outputString = "P          " + std::string(1, enemySymbol);
		// Run for the final tick, resets necessary attributes
		if (currentTick == 34)
		{
			attacking = false;
			reset_animationTick();
		}
	}
	next_animationTick();
	return outputString;
}

std::string CombatControl::engage_combat(Player &User, Alien &Foe, bool _defending)
{
	// Sets necessary attributes
	if (not verbSet)
	{
		playSoundEffect("selectoption.wav");
		// Player does not attack whilst defending, whilst they do otherwise
		attacking = !_defending;
		defending = true;
		verbSet = true;
	}
	
	// Runs animation of the player attacking the enemy
	if (attacking)
	{
		return player_attacking(User, Foe);
	}
	// Runs animation of the enemy attacking the player
	else if (defending)
	{
		return player_defending(User, Foe);
	}
	// Return an empty string to signify that neither participant was defeated
	return "";
}

std::string CombatControl::run_away(Player &User, Alien &Foe)
{
	playSoundEffect("flee.wav");
	int deductedExp = (int)Foe.get_expGiven()/2;
	return "You cowardly fled from your foe.\nYou lost " + std::to_string(deductedExp) + " experience.\n";
}

