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
	
	// Clears the screen (Hopefully a better method of clearing the screen will be found in time)
	void clear_screen();

	// Methods called when their respective keys are pressed by the player
	virtual void a_key();
	
	virtual void d_key();
	
	virtual void w_key();
	
	virtual void s_key();
	
	virtual void z_key();
	
	virtual void invalid_key();
	
	/* The function that loops whilst the combat ui is shown to the user
	Takes a player object and alien object as arguments
	Returns an integer - 0 if the player is still in combat, 1 if the enemy died and 2 if the player died */
	int ui_loop();
};

