/* Dislin library is used to produce necessary graphs - library used source (contains download/documentation within site): https://www.mps.mpg.de/dislin
I only used official documentation/examples whilst producing my code
I considered placing all statistics onto a single graph, but due to the variation of size between statistic I rejected the idea*/
#include "discpp.h"

#include <iostream>
#include <cmath>
#include <memory>

int singleGraphCreation(std::string trackedStat, Statistics &statisticsObject)
{ 
	// Retrieves required tracked statistic data
	std::array<float, 30> graphData = statisticsObject.get_tracked_statistic_map()[trackedStat];

	// Default to assuming that the array contains valid data only
	int entriesNum = graphData.size();
	
	for (int i=0; i<graphData.size(); i++)
	{
		// No data at given index, the amount of valid values in the array is determained
		if(graphData[i] == 0)
		{
			entriesNum = i;
			break;
		}
	}
	// Graph isn't produced if there are less than two tracked entries
	if(entriesNum < 2)
	{
		return 1;
	}
	// Dynamic array used as the amount of values used in the array isn't fixed
	double* yValues;
	yValues = new double [entriesNum];
	
	
	for (int i=0; i<entriesNum; i++)
	{
		yValues[i] = graphData[i];
	}
	
	int yLimit = graphData[entriesNum-1];
	int spacingNum = ceil(yLimit/20.0);
	// Ensures limit is a multiple of the spacing and greater than the larger value
	yLimit = yLimit/spacingNum * spacingNum + spacingNum;

	// Produces Dislin object
	Dislin graphObject;
	
	
	// Dynamic array used as the amount of values used in the array isn't fixed
	double* xValues;
	xValues = new double [entriesNum];
	for (int i=0; i<entriesNum; i++)
	{
		xValues[i] = i+1;
	}
	
	// Graph object initialisation
	graphObject.metafl ("cons");
	graphObject.scrmod ("revers");
	graphObject.disini ();
	
	// Positions graph within window
	graphObject.axspos (350, 1600);
	// Sets graph size within window
	graphObject.axslen (2400, 1300);
	
	// Axis labels
	graphObject.name   ("Entry number", "x");
	graphObject.name   ("Statistic value", "y");
	
	// Removes the decimal point from axis numbering
	graphObject.labdig (-1, "x");
	graphObject.labdig (-1, "y");
	// Sets the amount ticks between each axis value
	graphObject.ticks  (1, "x");
	graphObject.ticks  (1, "y");
	
	// Sets graph title
	graphObject.titlin ("Foes killed over time", 4);
	
	// Sets rgb of graph background
	graphObject.axsbgd(graphObject.intrgb (0.94,0.93,0.94));
	
	// Sets axis - defines limits, spacing etc
	graphObject.graf   (1, entriesNum, 1, 1, 0, yLimit, 0, spacingNum);
	// Sets rgb value of grid
	graphObject.setrgb (0.55, 0.55, 0.55);
	// Sets gridline frequency
	graphObject.grid   (1, 1);
	
	// Sets title
	graphObject.color  ("gray");
	graphObject.height (50);
	graphObject.title  ();
	
	// Produces curve
	graphObject.color  ("red");
	graphObject.curve  (xValues, yValues, entriesNum);
	
	delete[] yValues;
	delete[] xValues;
	
	// Terminates dislin 
	graphObject.disfin ();
	return 0;
}
