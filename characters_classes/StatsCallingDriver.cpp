// Used as a placeholder driver for integration testing
//#include "CombatUICaller.cpp"
#include "Player.cpp"

Player User({0,0});

#include "StatsUI.cpp"
int main()
{
	// No data returned
	StatsUIObject.run_loop(User);
	return 0;
}
