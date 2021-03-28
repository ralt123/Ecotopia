#ifndef LevellingUI_H
#define LevellingUI_H

#include "UITemplate.cpp"
#include "LevellingControl.cpp"
levelControl levelController(User);

#include <iostream>
#include <windows.h>

// Inherits from my UI template
// Class used to handle the interface for the levelling screen
class LevellingUI : public UITemplate
{
public:	
	// Used to display the mandatory details for each frame
	void display_frame();
	
	// Decrease allocation exp points for current stat
	void a_key();
	
	// Increase allocation exp points for current stat
	void d_key();
	
	// Change selection
	void w_key();
	
	void s_key();
	
	// Confrim option
	void z_key();
	
	// Method used to loop the levelling UI until the player confirms their point allocation
	void run_loop(Player &User);
};
LevellingUI LevellingUIObject;

#endif

