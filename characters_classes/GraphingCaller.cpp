/* The caller is independent from the main program file
this is because integrating the graph functions into the main program would require all team members to install and setup dislin to run the main program
as this is just an additional feature, I don't believe it is worth integration into the main program when considering the burden that would be put upon team members*/

#include <iostream>
#include "Stats.cpp"

// Object used to retrieve statistic data
Statistics statsObject;
#include "GraphingUI.cpp"
// graphControl is a singleton so a pointer returned from a static method is used to call upon the object
GraphingControl* graphControl = GraphingControl::createObject();

int main()
{
	// Object used to handle the graphing UI
	GraphingUI graphUI;
	// Input is initally stored as string
	std::string idInput;
	while(true)
	{
		std::cout << "Input save file ID: ";
		std::cin >> idInput;
		// Try statements to prevent saveid from being a non-integer
		try
		{
			// Attempts to convert the string to an integer
			int saveId = std::stoi(idInput);
			// Run the UI graphing loop
			if(statsObject.load_data(saveId))
			{
				graphUI.run_loop();
			}
			// Valid ID but the loading failed
			else
			{
				std::cout << "loading file error - enter a different save file ID\n";
			}
		}
		// Input was not an integer, output error message
		catch(std::invalid_argument)
		{
			std::cout << "invalid saveid - saveid must be an integer\n";
		}
	}
}


