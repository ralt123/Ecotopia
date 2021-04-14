// Prevents accidental redefinition
#ifndef STATS_CPP
#define STATS_CPP
#include "Stats.h"

Statistics::Statistics()
{
	// Array of pointers to all statistics
	std::array<float*, 8> statisticData = {&totalExperienceGained, &totalEnemiesDefeated, &totalDeaths, &totalDamageDealt, &totalDamageReceived, &totalDamageMitigated, &totalGoldGained, &totalGoldSpent};
	// Produces a map of string to reference (reference is to a float)
	// The string is the name of the desired statistic attribute whilst the reference references the value of the desired attribute 
	statisticKeys = {"totalExperienceGained", "totalEnemiesDefeated", "totalDeaths", "totalDamageDealt", "totalDamageReceived", "totalDamageMitigated", "totalGoldGained", "totalGoldSpent"};
	statisticContributionKeys = {"totalDeaths", "totalExperienceGained", "totalEnemiesDefeated", "totalDamageDealt", "totalGoldGained"};
	for (int i=0; i<statisticKeys.size(); i++)
	{
		statisticMap.insert(std::pair<std::string, float>(statisticKeys[i], *statisticData[i]));
	}
}

void Statistics::check_key(std::string key)
{
	// Key was not found in map
	if (statisticMap.find(key) == statisticMap.end())
	{
		throw std::invalid_argument("invalid variable specified");
	}
}

float Statistics::derive_score()
{
	int totalScore = 0;
	// Uses various statistics to derive a score
	// The statistic contributions are stored within a map
	scoreContributionMap["totalExperienceGained"] = statisticMap["totalExperienceGained"];
	scoreContributionMap["totalDeaths"] = statisticMap["totalDeaths"] * -10;
	scoreContributionMap["totalEnemiesDefeated"] = statisticMap["totalEnemiesDefeated"] * 3;
	scoreContributionMap["totalDamageDealt"] = statisticMap["totalDamageDealt"] / 5;
	scoreContributionMap["totalGoldGained"] = statisticMap["totalGoldGained"] * 2;
	std::cout << std::endl;
	// Totalscore is derived and returned
	for(int i=0; i<statisticContributionKeys.size(); i++)
	{
		totalScore += scoreContributionMap[statisticContributionKeys[i]];
	}
	return totalScore;
}

float Statistics::get_statistic(std::string requiredVariable)
{
	// totalScore must be immediately calculated to ensure it is not outdated
	if (requiredVariable == "totalScore")
	{
		return derive_score();
	}
	// Ensures the key is valid
	check_key(requiredVariable);
	// Returns requested statistic
	return statisticMap[requiredVariable];
}

void Statistics::alter_statistic(std::string alteredVariable, int alterBy)
{
	check_key(alteredVariable);
	// Ran when the modification is negative as statistics cannot be modified by a negative value
	if (alterBy < 0)
	{
		throw std::invalid_argument("statistic adjustments cannot be negative");
	}
	// Performs the arithmetic and ensures validity
	statisticMap[alteredVariable] += alterBy;
	validity_check();
}

void Statistics::update_tracked_statistics()
{
	// Iterate through all statistic keys with variable int i containing the current index
	for(int i=0; i<statisticKeys.size(); i++)
	{
		// Contains the most recently tracked value and index for said value within the current tracked statistic array
		float latestEntry = 0;
		int latestEntryIndex;
		// Locates the most recent value/index for value
		for(latestEntryIndex=trackedStatisticMap[statisticKeys[i]].size()-1; latestEntryIndex>=0; latestEntryIndex--)
		{
			// Value is not 0 therefore the current value/index is the most recent
			if(trackedStatisticMap[statisticKeys[i]][latestEntryIndex] != 0)
			{
				latestEntry = trackedStatisticMap[statisticKeys[i]][latestEntryIndex];
				break;
			}
		}
		// Newest tracked value is not equal to the current statistic value thus the tracked values must be updated
		if(latestEntry != statisticMap[statisticKeys[i]])
		{
			// The tracked statistic array is full
			if(latestEntryIndex+1 == trackedStatisticMap[statisticKeys[i]].size())
			{
				// All elements in the tracked statistic array are shifted to the left, disgarding the left most value
				for(int z=0; z<trackedStatisticMap[statisticKeys[i]].size()-1; z++)
				{
					trackedStatisticMap[statisticKeys[i]][z] = trackedStatisticMap[statisticKeys[i]][z+1];
				}
				// Current statistic is added to the end of the current tracked statistic array
				trackedStatisticMap[statisticKeys[i]][latestEntryIndex] = statisticMap[statisticKeys[i]];
			}
			else
			{
				// Statistic is placed to the right of the newest value within the tracked statistic array
				trackedStatisticMap[statisticKeys[i]][latestEntryIndex+1] = statisticMap[statisticKeys[i]];
			}
		}
	}
}

std::map<std::string, float> Statistics::get_statistic_map()
{
	return statisticMap;
}

std::map<std::string, float> Statistics::get_score_contribution_map()
{
	return scoreContributionMap;
}

std::map<std::string, std::array<float, 30>> Statistics::get_tracked_statistic_map()
{
	return trackedStatisticMap;
}

std::array<std::string, 5> Statistics::get_score_contribution_keys()
{
	return statisticContributionKeys;
}

std::array<std::string, 8> Statistics::get_statistic_keys()
{
	return statisticKeys;
}


void Statistics::validity_check()
{
	// totalGoldSpent cannot logically be greater than totalGoldGained + 10
	// Player starts with 10 gold which is included in the "totalGoldGained" statistic
	if (totalGoldSpent > totalGoldGained + 10)
	{
		throw std::logic_error("gold related stats are invalid");
	}
	// All statistic attributes must be positive
	std::array<float*, 8> statArray = {&totalExperienceGained, &totalEnemiesDefeated, &totalDeaths, &totalDamageDealt, &totalDamageReceived, &totalDamageMitigated, &totalGoldGained, &totalGoldSpent};
	for(const float* stat:statArray)
	{
		// Stats cannot be negative
		if (stat < 0)
		{
			throw std::logic_error("statistics cannot be negative");
		}
	}
}

// Saving/loading current and tracked statistics is done using a single text file for storing data to prevent redundant use of data storage files
bool Statistics::save_data(int saveFileId)
{
	std::string fileName = "statsData";
	// Ensures the tracked statistics are update to date
	update_tracked_statistics();
	std::array<int, 240> integerSaveData;
	int dataIndex = 0;
	
	// Iterates through all tracked statistic arrays and saves the contents to a text file
	for(int keyIndex=0; keyIndex<statisticKeys.size(); keyIndex++)
	{
		for(dataIndex; dataIndex<(keyIndex+1)*30; dataIndex++)
		{
			integerSaveData[dataIndex] = trackedStatisticMap[statisticKeys[keyIndex]][dataIndex-keyIndex*30] * 100;
		}
	}
	// Calls upon my function to handle saving with necessary arguments
	return general_save_data(saveFileId, fileName, integerSaveData);
}

bool Statistics::load_data(int loadFileId)
{
	// Try statement used to deal with runtime errors that may arise due to user incompetence (modification of save files)
	try
	{
		std::string fileName = "statsData";
		std::array<float*, 8> floatSaveData = {&totalExperienceGained, &totalEnemiesDefeated, &totalDeaths, &totalDamageDealt, &totalDamageReceived, &totalDamageMitigated, &totalGoldGained, &totalGoldSpent};
		// Array used to contain the loaded data
		std::array<int, 240> loadedData;
		// Attempts to load the required data using my loading function with necessary arguments
		// If the load failed, false is returned
		if (!general_load_data(loadFileId, fileName, &loadedData))
		{
			return false;
		}
		// Maintains the current index in the size 240 array
		int dataIndex = 0;
		// Contains the most recent data entry (this is stored in the statistic map)
		int latestEntry = 0;
		// Iterates for each statistic
		for(int keyIndex=0; keyIndex<statisticKeys.size(); keyIndex++)
		{
			// Iterates to retrieve each statistic's tracked data
			for(dataIndex; dataIndex<(keyIndex+1)*30; dataIndex++)
			{
				// Stores in the tracked statistic map
				trackedStatisticMap[statisticKeys[keyIndex]][dataIndex-keyIndex*30] = loadedData[dataIndex] / 100.0;
				// Determains the latest entry
				if (loadedData[dataIndex] != 0)
				{
					latestEntry = loadedData[dataIndex] / 100.0;
				}
			}
			// Sets the current stats
			*floatSaveData[keyIndex] = loadedData[dataIndex]/100.0;
			statisticMap[statisticKeys[keyIndex]] = latestEntry;
		}
		return true;
	}
	// Error whilst loading file and setting attributes, return false
	// This catch statement is most likely ran due to the save file being altered after the last save
	catch(...)
	{
		return false;
	}
}
#endif

