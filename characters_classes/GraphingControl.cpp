#include "GraphingControl.h"


GraphingControl::GraphingControl() 
{
	// Default selected option is the first option
	graphOption = 0;
}

GraphingControl::~GraphingControl() {}

// Singleton object does not yet exist
GraphingControl* GraphingControl::graphingObject = nullptr;

// Tracks how many pointers are pointing at the singleton object
int GraphingControl::objectPointers = 0;

GraphingControl* GraphingControl::createObject()
{
	// Singleton object doesn't exist and thus is created
    if (graphingObject == nullptr)
    {
        graphingObject = new GraphingControl();
    }
    objectPointers += 1;
    return graphingObject;
}

GraphingControl* GraphingControl::nullifyPointer()
{
	objectPointers -= 1;
	// objectPointers cannot be negative, raise error
	if (objectPointers < 0)
	{
		throw std::logic_error("invalid value of objectPointers indicative of misuse of nullifyPointer method");
	}
	// No pointers for the singleton object thus the object is deleted
	else if (objectPointers == 0)
	{
		delete graphingObject;
		graphingObject = nullptr;
	}
	return nullptr;
}

int GraphingControl::confirm()
{
	std::array<std::string, 8> graphStats = statsObject.get_statistic_keys();
	int errorCode = 0;
	// User is requesting a single graph for a statistic
	if(graphOption < 8)
	{
		errorCode = singleGraphCreation(graphStats[graphOption], statsObject);
	}
	// User is requesting a pie chart displaying score contributions
	else if(graphOption == 8)
	{
		errorCode = pieGraphCreation(statsObject);
	}
	return errorCode;
}

int GraphingControl::get_graphOption() const
{
	return graphOption;
}

void GraphingControl::next_graphOption()
{
	graphOption += 1;
	if (graphOption > 8)
	{
		graphOption = 0;
	}
}

void GraphingControl::previous_graphOption()
{
	graphOption -= 1;
	if (graphOption < 0)
	{
		graphOption = 8;
	}
}

