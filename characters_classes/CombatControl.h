#ifndef COMBAT_CONTROL_H
#define COMBAT_CONTROL_H

#include "Player.cpp"
#include "SoundHandle.cpp"

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
    int animationDelay;
    
public:
	// Used to allow for reusable functions with conditional statements to conduct necessary tasks
	bool attacking;
	bool defending;
	bool verbSet;
	bool animationOngoing;
	
	// Constructor method to set default attribute values
	CombatControl();
	
	/* Method used to set the animation speed during combat animations
	animation speed must be an integer inclusively between 1 and 10
	1 is the slowest possible speed, 10 is the fastest possible speed */
	void set_animation_speed(int animationSpeed);
	
	// Get methods for private attributes
	int get_animationTick() const;
	
	int get_animationDelay() const;
	
	int get_combatOption() const;
	
	// Resets the animation tick attribute to 0
	void reset_animationTick();
	
	// Increments the specified private integer attribute by 1
	void next_animationTick();
	
	void next_combatOption();
	
	// Decrements the combat option integer by 1
	void previous_combatOption();
	
	// Returns the name of the option currently selected by the user
	std::string get_combat_option_name();

	/* Returns the string to be outputted to screen
	Player receives gold depending on the alien's "goldGiven" attribute
	Player receives experience depending on the alien's "experienceGiven" attribute */
	std::string loot_enemy(Player &User, Alien &Foe);
	
	/* Returns the current frame of the animation for the alien attacking the player
	Health is deducted from the player during animation*/
	std::string player_defending(Player &User, Alien &Foe);

	/* Returns the current frame of the animation for the player attacking the alien
	Health is deducted from the alien during animation*/
	std::string player_attacking(Player &User, Alien &Foe);
	
	/* Method used to allow the player to combat an alien
	Takes in two objects as arguments - Player object, alien object and a boolean denoating if the player chose the "defend" action
	Returns a string containing the data to be outputted to the screen */
	std::string engage_combat(Player &User, Alien &Foe, bool _defending = false);
	
	/* Method called when the player flees from combat
	Returns the string to be outputted
	Experience is deducted as punishment for fleeing*/
	std::string run_away(Player &User, Alien &Foe);
};
#endif

