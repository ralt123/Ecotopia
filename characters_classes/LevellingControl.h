#ifndef LEVELLING_CONTROL_H
#define LEVELLING_CONTROL_H

#include "Character.cpp"
#include "Alien.cpp"
#include "Player.cpp"

#include <array>

// Class used to handle process requests related the levelling
class levelControl
{
private:
	int levellingOption;
	std::array<int, 3> alterStats;
	int usedPoints;
	int experiencePoints;
	
public:
	levelControl(Player &User);
	
	// Adjusts the amount a specified stat will be altered upon confirmation
	void adjust_stat(int statIndex, int adjustAmount);
	
	// Resets allocated points
	void reset();
	
	// Confirms the point allocation made by the player and returns to gameplay
	void confirm(Player &User);
	
	// Methods used to get specific attributes
	int get_usedPoints() const;
	
	// Get the experience points newly allocated to each stat
	int get_alter_maxHealth() const;
	
	int get_alter_attack() const;
	
	int get_alter_defence() const;
	
	int get_levellingOption() const;
	
	int get_experiencePoints() const;
	
	// Methods to adjust the attribute currently selected by the player
	void next_levellingOption();
	
	void previous_levellingOption();
};

#endif

