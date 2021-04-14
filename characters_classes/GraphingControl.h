#ifndef GRAPHING_CONTROL_H
#define GRAPHING_CONTROL_H

#include "Player.cpp"
#include "SingletonTemplate.h"
#include "StatsGraphing.cpp"
#include "PieChart.cpp"

#include <array>

// Class used to handle process requests related the levelling
class GraphingControl
{
private:
	int graphOption;
	
	// static pointer which points at the singleton object
    static GraphingControl* graphingObject;
    
    // Tracks how many pointers are pointing at the singleton object
    static int objectPointers;
    
    // Constructor method is private as to prevent an object from being created without using the createObject method
    GraphingControl();
    
	// Destrustor method is private to prevent the singleton object from being deleted whilst a pointer for the object still exists
    ~GraphingControl();
public:
	/* Returns a pointer to the graphingControl object
	if the graphingControl object exists, a pointer to the existing object is returned
	otherwise, the graphingControl object is created and a pointer to the object is returned */
    static GraphingControl* createObject();
    
	/* Returns a nullptr
	Decrements the objectPointers attribute by 1
	If the objectPointers is set to 0 after the decrement, the singleton object is deleted */
    static GraphingControl* nullifyPointer();
	
	// Confirms the graph selection made by the player and calls necessary functions to produce/display the graph
	int confirm();
	
	// Standard get method - returns graphOption
	int get_graphOption() const;
	
	// Methods to adjust the attribute currently selected by the player
	void next_graphOption();
	
	void previous_graphOption();
};
#endif

