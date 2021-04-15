#ifndef STATSUI_H
#define STATSUI_H

#include "UITemplate.cpp"
#include <iostream>
#include <windows.h>

class StatsUI : public UITemplate
{
public:	
	// Used to display the mandatory details for each frame
	void display_frame();
	
	// Only the z key is used for the statsUI - used to return to gameplay
	void z_key();
	
	// Repeatedly ran method that is called within a loop to display the UI and control user input
	void run_loop();
};

StatsUI StatsUIObject;
#endif

