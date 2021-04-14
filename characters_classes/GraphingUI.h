#ifndef GrapingUI_H
#define GrapingUI_H

#include "UITemplate.cpp"
#include "GraphingControl.cpp"
GraphingControl graphingController();

#include <iostream>
#include <windows.h>

// Inherits from my UI template
// Class used to handle the interface for the selecting the desired graph
class GraphingUI : public UITemplate
{
public:	
	// Used to display the mandatory details for each frame
	void display_frame();
	
	// Change selection
	void w_key();
	
	void s_key();
	
	// Confrim option
	void z_key();
};
// graphControl is a singleton so a pointer returned from a static method is used to call upon the object
GraphingControl* graphController = GraphingControl::createObject();

#endif

