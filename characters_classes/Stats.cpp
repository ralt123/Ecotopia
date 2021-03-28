#include "Stats.h"

Statistics::Statistics()
{
	// Array of pointers to all statistics
	std::array<float*, 8> statisticData = {&totalExperienceGained, &totalEnemiesDefeated, &totalDeaths, &totalDamageDealt, &totalDamageReceived, &totalDamageMitigated, &totalGoldGained, &totalGoldSpent};
	// Produces a map of string to reference (reference is to a float)
	// The string is the name of the desired statistic attribute whilst the reference references the value of the desired attribute 
	std::array<std::string, 8> mapKeys = {"totalExperienceGained", "totalEnemiesDefeated", "totalDeaths", "totalDamageDealt", "totalDamageReceived", "totalDamageMitigated", "totalGoldGained", "totalGoldSpent"};
	for (int i=0; i<mapKeys.size(); i++)
	{
		statisticMap.insert(std::pair<std::string, float>(mapKeys[i], *statisticData[i]));
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
	// Uses various statistics to derive a score
	float totalScore = totalExperienceGained * 4;
	
	totalScore -= totalDeaths * 50;
	totalScore += totalEnemiesDefeated * 3;
	totalScore += totalDamageDealt / 50;
	totalScore += totalGoldGained;
	return totalScore;
}

float Statistics::get_statistic(std::string requiredVariable)
{
	if (requiredVariable == "totalScore")
	{
		return derive_score();
	}
	check_key(requiredVariable);
	return statisticMap[requiredVariable];
}

void Statistics::alter_statistic(std::string alteredVariable, int alterBy)
{
	check_key(alteredVariable);
	// ran when the modification is negative as statistics cannot be modified by a negative value
	if (alterBy < 0)
	{
		throw std::invalid_argument("statistic adjustments cannot be negative");
	}
	statisticMap[alteredVariable] += alterBy;
	validity_check();
}

std::map<std::string, float> Statistics::get_statistic_map()
{
	return statisticMap;
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
	for(const float* stat : statArray)
	{
		if (stat < 0)
		{
			throw std::logic_error("statistics cannot be negative");
		}
	}
}

