#ifndef CombatUI_H
#define CombatUI_H

#include <iostream>
#include <cwchar>
#include <windows.h>
#include "UITemplate.cpp"
#include "CombatControl.cpp"

CombatControl CombatController;

class CombatUI : public UITemplate
{
public:
	// Used to display the mandatory details for each frame
	void display_frame(Player &User, Alien &Foe);
	
	// Used to display the mandatory frames in addition to the string parameter
	void display_combat_frame(std::string combatIcons, Player &User, Alien &Foe);
	
	// Displays the frame whilst no animation is taking place
	void display_static_frame(Player &User, Alien &Foe);

	// Methods called when their respective keys are pressed by the player
	void a_key();
	
	void d_key();
	
	void z_key();
	
	// Function called when the player performs a combat action (attacking/defending)
	void combat_action(Player &User, Alien &Foe, bool defending);
	
	// Function used to loop the AI and break when necessary
	// Returns true if the player died; false otherwise
	bool run_loop(Player &, Alien &Foe);
};

CombatUI CombatUIObject;
#endif

