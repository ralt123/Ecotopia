// Used as a driver for integration testing
// The file features the bare minimal include statements for the code to operate as intended

#include "Player.cpp"
Player User({0,0});
#include "LevellingUI.cpp"

int main()
{
	// No data returned
	LevellingUIObject.run_loop(User);
	return 0;
}

