#ifndef STATS_H
#define STATS_H

#include "Stats.h"
#include <stdlib.h>
#include "SaveManagement.cpp"
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
	
	// Map containing arrays for each statistic key of which contain the last 30 tracked values
	std::map<std::string, std::array<float, 30>> trackedStatisticMap;
	
	// Map containing the float value of which each contribution key impacts the total score
	std::map<std::string, float> scoreContributionMap;
	
	// Array containing all statistic keys
	std::array<std::string, 8> statisticKeys;
	
	// Array containing statistic keys that are considered when deriving the value of the player's total score
	std::array<std::string, 5> statisticContributionKeys;
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

	// Various get methods for private attributes
	std::map<std::string, float> get_statistic_map();
	
	std::map<std::string, float> get_score_contribution_map();
	
	std::map<std::string, std::array<float, 30>> get_tracked_statistic_map();
	
	std::array<std::string, 8> get_statistic_keys();
	
	std::array<std::string, 5> get_score_contribution_keys();

	// Ensures the validity of all the statistic attributes, an error is risen if any attributes are known to be invalid
	void validity_check();
	
	// Updates the map attribute containing tracked statistics
	void update_tracked_statistics();

	/* Saves necessary player attributes to a text file
	integer argument denoates the id of the text file 
	returns true if the save was successful, false otherwise */
    bool save_data(int saveFileId = 1);

	/* Loads necessary player attributes from a text file
	integer argument denoates the id of the text file
	returns true if the load was successful, false otherwise */
	bool load_data(int loadFileId = 1);
};

#endif

