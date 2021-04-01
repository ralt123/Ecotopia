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
	
	void z_key();
	
	// Method called to display the statistics UI
	void run_loop(Player &User);
};

StatsUI StatsUIObject;
#endif

