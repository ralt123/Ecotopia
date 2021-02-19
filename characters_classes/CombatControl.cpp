#include "Characters.h"
#include <windows.h>
#include <stdlib.h>
#include <time.h> 
#include <string>

// Used to control combat, provides methods to achieve this and contains necessary attributes
class CombatControl
{
private:
    int combatOption;
    int animationTick;
public:
	CombatControl()
    {
        int combatOption = 0;
        int animationTick = 0;
    }
	
	int get_animationTick() const
    {
    	return animationTick;
	}
	void next_animationTick()
	{
		animationTick += 1;
	}
	void reset_animationTick()
	{
		animationTick = 0;
	}
    int get_combatOption() const
    {
        return combatOption;
    }
    
    void next_combatOption()
    {
        combatOption += 1;
        if (combatOption == 3)
        {
            combatOption = 0;
        }
    }
    
    void previous_combatOption()
    {
        combatOption -= 1;
        if (combatOption == -1)
        {
            combatOption = 2;
        }
    }
	
	// Returns the name of the option currently selected by the user
	std::string getCombatOptionName()
	{
	    std::string optionOutput;
	    int option = get_combatOption();
	    switch(option)
	    {
	    	case 0:
	    		optionOutput = "Attack";
	    		break;
	    	case 1:
	    		optionOutput = "Inventory";
	    		break;
	    	case 2:
	    		optionOutput = "Placeholder";
	    		break;
	    	default:
	    		throw std::invalid_argument( "Invalid combatOption" );
	    		break;
		}
	    return optionOutput;
	}

	std::string lootEnemy(Player &User, Alien &Foe)
	{
		// Add item looting when items are implemented
		int givenExp = Foe.get_expGiven();
		std::string returnString = "You gained " + std::to_string(givenExp) + " experience.";
		if (User.increase_experience(givenExp))
		{
			returnString + "\nYou have levelled up to level " + std::to_string(User.get_level()) + "!";
		}
		throw std::invalid_argument( "This method will be finished once the necessary functions implemented" );
		return returnString;
	}

	/* Method used to allow the player to combat an alien
	Takes in two objects as arguments - Player object and alien object
	Returns a string containing the data to be outputted to the screen
	*/
	std::string engageCombat(Player &User, Alien &Foe)
	{
		std::string outputString = "";
		int currentTick = get_animationTick();
		switch(get_combatOption())
		{
			case 0:
				Sleep(50);
				if (currentTick < 4)
				{
					outputString = "P          A";
				}
				else if (currentTick < 14)
				{
					outputString = std::string((currentTick-4), ' ') + "P" + std::string(14-currentTick, ' ') + "A";
				}
				else if (currentTick < 20)
				{
					outputString = std::string(10, ' ') + "P" + "A";
					if (currentTick == 17)
					{
						if (User.attackFoe(Foe))
						{
							Sleep(1000);
							return "victory";
						}
					}
				}
				else if (currentTick < 30)
				{
					outputString = std::string((30-currentTick), ' ') + "P" + std::string(currentTick-20, ' ') + "A";
				}
				else if (currentTick < 34)
				{
					outputString = "P          A";
				}
				else if (currentTick < 44)
				{
					outputString = "P" + std::string(44-currentTick, ' ') + "A";
				}
				else if (currentTick < 50)
				{
					outputString =  "PA";
					if (currentTick == 47)
					{
						if (User.defend(Foe))
						{
							Sleep(1000);
							return "defeat";
						}
					}
				}
				else if (currentTick < 60)
				{
					outputString = "P" + std::string(currentTick-50, ' ') + "A";
				}
				else if (currentTick < 63)
				{
					outputString = "P          A";
				}
				next_animationTick();
				break;
			default:
				throw std::invalid_argument( "Invalid combatOption" );
				break;
		}
		return outputString;
	}
};
