#include "GraphingUI.h"

void GraphingUI::display_frame()
{
	// Array containing the text to be outputted that can be selected/highlighted by the user
	std::array<std::string,9> outputSelections = {};
	
	// Lines of text of which the player cannot interact with are outputted
	std::cout << "Graph selections\nSingle tracked data curve graphs\n\n";
	
	// Interable lines of text are stored in an array
	outputSelections[0] = "Total experience gained graph";
	outputSelections[1] = "Total enemies defeated graph";
	outputSelections[2] = "Total deaths graph";
	outputSelections[3] = "Total damage dealt graph";
	outputSelections[4] = "Total damage received graph";
	outputSelections[5] = "Total damage mitigated graph";
	outputSelections[6] = "Total gold gained graph";
	outputSelections[7] = "Total gold spent graph";
	
	outputSelections[8] = "Score contribution piechart";
	
	// Deduces which line/option is selected by the user
	int selection = graphController -> get_graphOption();
	// Outputs all lines in the "outputSelections" array with the selected line surrounded by arrows to indicate that the option is currently selected
	outputSelections[selection] = ">> " + outputSelections[selection] + " <<";
	// Iterate through array to output required text
	for (int i=0; i<outputSelections.size(); i++)
	{
		std::cout << outputSelections[i] << std::endl;
		// Output non-interable line of text
		if (i == 7)
		{
			std::cout << "\nPiechart comparing values\n";
		}
	}
}

void GraphingUI::w_key()
{
	clear_screen();
	graphController -> previous_graphOption();
	display_frame();
}

void GraphingUI::s_key()
{
	clear_screen();
	graphController -> next_graphOption();
	display_frame();
}

void GraphingUI::z_key()
{
	clear_screen();
	// Calls upon method to confirm user selection
	int errorCode = graphController -> confirm();
	// There was not enough data within the specified save to allow graph creation
	if(errorCode == 1)
	{
		std::cout << "Insufficent statistical data\nSelect another save or progress further within current save to use graphing functions\n";
	}
	std::cout << "Press w/s to return\n";
}

