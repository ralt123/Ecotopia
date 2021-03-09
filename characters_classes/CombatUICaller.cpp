// Includes necessary functions and classes to display the combat UI
#include "CombatUI.cpp"

// Function used to loop the AI and break when necessary
// Returns true if the player died; false otherwise
bool CombatUIRun(Player &User, Alien &Foe)
{
    clearScreen();
	displayStaticFrame(User, Foe);
	// Loops until combat ends
    while(true) {
    	int result = combatUILoop(User, Foe);
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

