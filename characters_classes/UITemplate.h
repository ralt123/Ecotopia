#ifndef UITEMPLATE_H
#define UITEMPLATE_H

// Template used for my user interfaces

#include <windows.h>
#include <iostream>

class UITemplate
{
protected:
	int returnInt = 0;
	static UITemplate* getInstance();
public:
	// Used to display the mandatory details for each frame
	virtual void display_frame();
	
	// Clears the screen
	void clear_screen();

	// Methods called when their respective keys are pressed by the player
	virtual void a_key();
	
	virtual void d_key();
	
	virtual void w_key();
	
	virtual void s_key();
	
	virtual void z_key();
	
	virtual void invalid_key();
	
	/* Method that is repeatedly called within a loop to display the UI and control user input
	returnInt is returned and by default is 0 - the value of returnInt is expected to be modified within the child class */
	virtual int ui_loop();
	
	// Method used to iterate the ui_loop method until a ui_loop returns a non 0 integer
	void run_loop();
};
#endif

