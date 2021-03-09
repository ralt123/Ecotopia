// Includes necessary functions and classes to display the combat UI
#include "LevellingUI.cpp"
// Player User({0,0});

// Function used to loop the AI and break when necessary
// Returns true if the player died; false otherwise
bool LevellingUIRun(Player &User)
{
    clearScreen();
	displayFrame(User);
	// Loops until combat ends
    while(true) {
    	int result = LevellingUILoop(User);
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

int main()
{
	if (LevellingUIRun(User))
	{
		std::cout << "You died, running death screen." << std::endl;
	}
	return 0;
}
// x - 120 X - 88 c - 99 C - 67
// w - 119 W - 87 s - 115 S - 83
