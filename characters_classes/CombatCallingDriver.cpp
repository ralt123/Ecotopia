// Used as a placeholder driver for integration testing
// The file features the bare minimal include statements for the code to operate as intended
#include "Player.cpp"

Player User({0,0});
Alien Foe({0,1});

#include "CombatUI.cpp"
int main()
{
	// Returns true if the player died, false otherwise
	if (CombatUIObject.run_loop(User, Foe))
	{
		std::cout << "You died, running death screen." << std::endl;
	}
	return 0;
}
