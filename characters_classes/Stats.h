#ifndef STATS_H
#define STATS_H

#include "Stats.h"
#include <stdlib.h>
#include <array>
#include <string>
#include <map>

// Class used to contain and manipulate various statistics
class Statistics
{
private:
	// Float attributes are the available statistics
	float totalExperienceGained;
	float totalEnemiesDefeated;
	float totalDeaths;
	float totalDamageDealt;
	float totalDamageReceived;
	float totalDamageMitigated;
	
	float totalGoldGained;
	float totalGoldSpent;
	// Map of string to reference (reference is to a float)
	// The string is the name of the desired statistic attribute whilst the reference references the value of the desired attribute 
	std::map<std::string, float> statisticMap;
public:
	// Constructor method
	Statistics();
	
	// Raises an error if the string key is not within the statisticMap map
	void check_key(std::string key);
	
	// Uses various statistics to derive a score and returns the score
	float derive_score();
	
	// Returns the float corresponding to the string argument (string argument should be the name of the required statistic attribute)
	float get_statistic(std::string requiredVariable);
	
	// Alters the attribute specified by the string (string argument should be the name of the required statistic attribute)
	// Statistic is modified by the integer argument, the integer cannot be negative
	void alter_statistic(std::string alteredVariable, int alterBy);

	// Returns a map of string to reference (reference is to a float)
	// The string is the name of the desired statistic attribute whilst the reference references the value of the desired attribute 
	std::map<std::string, float> get_statistic_map();

	// Ensures the validity of all the statistic attributes, an error is risen if any attributes are known to be invalid
	void validity_check();
};

#endif

