// Redeclaration errors may arise during integration thus guards are put in place to prevent this
#ifndef UITEMPLATE_CPP
#define UITEMPLATE_CPP

#include "UITemplate.h"


void UITemplate::display_frame() {}

void UITemplate::clear_screen()
{
	// Clears screen
	system("CLS");
}

// Methods called when their respective keys are pressed by the player
void UITemplate::a_key() {}

void UITemplate::d_key() {}

void UITemplate::w_key() {}

void UITemplate::s_key() {}

void UITemplate::z_key() {}

void UITemplate::invalid_key() {}

int UITemplate::ui_loop()
{
    // Used to allow immediate input
    // Code responsible for allowing immediate input was produced using official documentation
    // https://docs.microsoft.com/en-us/windows/console/using-the-high-level-input-and-output-functions
    // https://docs.microsoft.com/en-us/windows/console/setconsolemode
	HANDLE consoleHandle;
    DWORD  dMode;

    consoleHandle = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(consoleHandle, ENABLE_ECHO_INPUT);  

	// Retrieves the ascii value of the character inputted
    int character = std::cin.get();

	// Runs the statement relevant to the character pressed (non-capital sensitive)
	switch (character)
	{
	case 97:
	case 65:
		// "a" key pressed, change selected action to previous action
		a_key();
		break;
	case 100:
	case 68:
		// "d" key pressed, change selected action to next action
		d_key();
		break;
	// "w" key pressed, increase selected attribute, if possible
	case 119:
	case 87:
		w_key();
		break;
	// "s" key pressed, increase selected attribute, if possible
	case 115:
	case 83:
		s_key();
		break;
	case 122:
	case 90:
		// "z" key pressed, confirm selected action
		z_key();
		break;
	default:
		invalid_key();
		break;
	}
	
	SetConsoleMode(consoleHandle, dMode);
	return returnInt;
}

void UITemplate::run_loop()
{
	// Clears whatever was on the screen before the method was called
    clear_screen();
    // Displays the initial frame 
	display_frame();
	// Loops until the ui_loop returns a non 0 integer 
    while(ui_loop() == 0) {}
    // Clears screen before returning control to the caller
	clear_screen();
}
#endif

