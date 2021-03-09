// Used as a placeholder driver for integration testing
#include "CombatUICaller.cpp"

Player User({0,0});
Alien Foe({0,1});

int main()
{
	if (CombatUIRun(User, Foe))
	{
		std::cout << "You died, running death screen." << std::endl;
	}
	return 0;
}
// x - 120 X - 88 c - 99 C - 67
