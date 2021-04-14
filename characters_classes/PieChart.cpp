#include <iostream>
#include "discpp.h"
#include <array>

int pieGraphCreation(Statistics &statisticsObject)
{ 
	// Required datatype to be used - can't use std::array
	double graphData[4];
	// Retrieves required data
	int totalScore = statisticsObject.derive_score();
	std::array<std::string, 5> requiredKeys = statisticsObject.get_score_contribution_keys();
	std::map<std::string, float> contributionMap = statisticsObject.get_score_contribution_map();
	
	// 0th index contains unused key
	for(int i=1; i<requiredKeys.size(); i++)
	{
		// Sets data to be used for the piechart
		graphData[i-1] = contributionMap[requiredKeys[i]];
	}
	
	// Derives values
	int deathDeduction = contributionMap[requiredKeys[0]];
	int grossScore = totalScore - deathDeduction;
	// Gross score must be greater than 1 for a pie chart to be produced
	if(grossScore<=0)
	{
		return 1;
	}
	
	// Array containing the various title lines of text
	std::array<std::string, 3> chartTitles;
	chartTitles[0] = (std::string)"Gross Score Contributions";
	chartTitles[1] = (std::string)"Gross score: " + std::to_string(grossScore) + (std::string)"  Total score: " + std::to_string(totalScore);
	chartTitles[2] = (std::string)"Score deducted due to deaths: " + std::to_string(deathDeduction);
	
	// Sets buffer size, variable name is standard practice within used library
	char cbuf[100];

	Dislin graphObject;
	
	// Graph object initialisation
	graphObject.scrmod("revers");
	graphObject.metafl("cons");
	graphObject.disini();
	// Sets font
	graphObject.complx ();
	// Sets length of piechart
	graphObject.axslen (1600, 1000);
	// Adjust position of title
	graphObject.vkytit(100);
	// Sets titles
	for(int i=0; i<chartTitles.size(); i++)
	{
		graphObject.titlin(chartTitles[i].c_str(), i+1);
	}
	// Each section has differing colours
	graphObject.chnpie("COLOR");
	// Sets internal pattern for each section
	graphObject.shdpat(8);
	// Initialises legend
	graphObject.legini (cbuf, 4, 20);
	// Sets labels for each pie section
	std::array<const char*, 4> pieLabels = {"Gaining experience", "Defeating enemies", "Dealing damage", "Gaining gold"};
	for(int i=0; i<pieLabels.size(); i++)
	{
		graphObject.leglin (cbuf, pieLabels[i], i+1);
	}
	
	// Sets position of	graph
	graphObject.axspos(800, 1600);
	// Sets label type/position
	graphObject.labpos("external", "pie");
	// Plots piechart
	graphObject.piegrf (cbuf, 1, graphData, 4);
	// Plots title
	graphObject.height (50);
	graphObject.title  ();
	
	// Terminates dislin 
	graphObject.endgrf ();
	graphObject.disfin ();
	return 0;
}

