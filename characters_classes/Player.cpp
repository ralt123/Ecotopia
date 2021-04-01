#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"


Player::Player(std::array<int,2> _position)
: Character(_position)
{
	char characterSymbol = '@';
    experience = 0;
    gold = 10;
    experiencePoints = 3;
}

void Player::override_stats(int _maxHealth, int _health, int _attack, int _defence, int _level, int _experience, int _experiencePoints)
{
	Character::override_stats(_maxHealth, _health, _attack, _defence, _level);
	// Experience/experiencePoints can be set to 0 therefore the integer -1 is used to indicate that experience/experiencePoints is to remain unchanged
	if (_experience < -1 or _experiencePoints < -1)
	{
		throw std::invalid_argument("cannot set experience given below 0");
	}
	else
	{
		// Checks if the attributes that are unique to the player class are to remain unchanged
		if (_experience != -1)
		{
			experience = 0;
			alter_experience(_experience);
		}
		if (_experiencePoints != -1)
		{
			experiencePoints = _experiencePoints;
		}
	}	
}

int Player::get_experience() const
{
	return experience;
}

int Player::get_experiencePoints() const
{
	return experiencePoints;
}

float Player::get_gold() const
{
	return gold;
}

void Player::reduce_experiencePoints(int reduceBy)
{
	// raises error if the operation results in experience points being negative
	if (experiencePoints - reduceBy < 0)
	{
		throw std::invalid_argument("experience points cannot go below 0");
	}
	experiencePoints -= reduceBy;
}

float Player::derive_gold_adjustment(float baseAdjustment)
{
	// Ensures the adjustment is to 2 decimal places at most
	int roundedAdjustment = ((int)(baseAdjustment*100))/100;
	if (baseAdjustment != roundedAdjustment)
	{
		throw std::invalid_argument("all prices must be 2 decimal places at most");
	}
	// Prevents the adjustment from resulting in a negative gold amount
	if (gold + baseAdjustment < 0)
	{
		baseAdjustment = -gold;
	}
	return baseAdjustment;
}

void Player::alter_gold(float increaseBy)
{
	// Used to ensure the price is to 2 decimal places at most and prevent gold from becoming negative
	increaseBy = derive_gold_adjustment(increaseBy);
	gold += increaseBy;
	if (increaseBy > 0)
	{
		playerStatistics.alter_statistic("totalGoldGained", increaseBy);
	}
}


bool Player::make_purchase(float cost)
{
	// False is return if the player cannot afford the purchase
	if (cost > gold)
	{
		return false;
	}
	// Used to ensure the price is to 2 decimal places at most
	gold += derive_gold_adjustment(-cost);
	playerStatistics.alter_statistic("totalGoldSpent", cost);
	return true;
}

bool Player::alter_experience(int expGained)
{
	experience += expGained;
	// Player levels up and experience is deducted
	if (experience >= level*5 + 5)
	{
		while (experience >= level*5 + 5)
		{
			experience -= level*5 + 5;
			level += 1;
			experiencePoints += 1;
		}
		return true;
	}
	// Experience cannot be negative
	else if (experience < 0)
	{
		experience = 0;
	}
	if (expGained > 0)
	{
		playerStatistics.alter_statistic("totalExperienceGained", expGained);
	}
	return false;
}

bool Player::directReduceHealth(int reduction)
{
	playerStatistics.alter_statistic("totalDamageReceived", reduction);
	return Character::directReduceHealth(reduction);
}

bool Player::attackFoe(Alien &other)
{
	playerStatistics.alter_statistic("totalDamageDealt", other.deriveDamage(attack));
    other.reduceHealth(attack);
    // Enemy was defeated
    if (other.get_health() < 1)
    {
    	playerStatistics.alter_statistic("totalEnemiesDefeated", 1);
        return true;
    }
    return false;
}

bool Player::defend(Alien &other)
{
	int derivedDamage = Character::deriveDamage(other.get_attack());
	playerStatistics.alter_statistic("totalDamageReceived", derivedDamage);
	playerStatistics.alter_statistic("totalDamageMitigated", other.get_attack() - derivedDamage);
	reduceHealth(other.get_attack());
	// Player was defeated
    if (health < 1)
    {
        return true;
    }
    return false;
}

bool Player::preparedDefend(Alien &other)
{
	// Variable used to temporarily store the player's actual defence
	int actualDefence = defence;
	// Defence is increased by 50% whilst defending
	defence = int(defence * 1.5);
	int derivedDamage = deriveDamage(other.get_attack());
	playerStatistics.alter_statistic("totalDamageReceived", derivedDamage);
	playerStatistics.alter_statistic("totalDamageMitigated", other.get_attack() - derivedDamage);
	bool result = defend(other);
	defence = actualDefence;
	return result;
}

std::array<int, 2> Player::death()
{
	playerStatistics.alter_statistic("totalDeaths", 1);
	position = {0,0};
	// 20% of the player's current experience is lost
	int experienceDeducted = (int)experience*0.2;
	experience -= experienceDeducted;
	// Player loses 10% of their gold or 5 multiplied by their level, whichever is larger
	int goldDeducted = gold*0.1;
	if (goldDeducted < 5*level)
	{
		goldDeducted = 5*level;
	}
	goldDeducted = derive_gold_adjustment(-goldDeducted);
	alter_gold(goldDeducted);
	return std::array<int, 2> {-goldDeducted, experienceDeducted};
}

float Player::get_statistic(std::string requestedVariable)
{
	return playerStatistics.get_statistic(requestedVariable);
}

bool Player::save_data(int saveFileId)
{
	// Try statement used to deal with runtime errors that may arise due to user incompetence
	try
	{
		// Opens text file to write data to said file
		std::ofstream saveFile;
		saveFile.open("playerData" + std::to_string(saveFileId) + ".txt");
		// Wrties data to text file and closes file
		std::array<int, 10> integerSaveData = {maxHealth, health, attack, defence, level, experience, experiencePoints, position[0], position[1], (int)gold*100};
		for (int saveData:integerSaveData)
		{
			saveFile << saveData << ",";
		}
		saveFile.close();
		return true;
	}
	// Error whilst saving file and storing attributes, return false
	// This catch statement is most likely ran due to insufficient access rights
	catch(...)
	{
		return false;
	}
}

bool Player::load_data(int loadFileId)
{
	// Try statement used to deal with runtime errors that may arise due to user incompetence
	try
	{
		// Opens file to input data from the file
		std::ifstream saveFile;
		saveFile.open("playerData" + std::to_string(loadFileId) + ".txt");
		std::array<std::string, 10> attributeData;
		std::string savedData;
		// File not found thus false is returned
		if (not saveFile.is_open())
		{
			return false;
		}
		// Retrieves data and closes file
		std::getline(saveFile, savedData);
		saveFile.close();
		int separatorPos;
		int dataPos = 0;
		for (int i=0; i<10; i++)
		{
			// Gets position of separatorseparaseparato
			separatorPos = savedData.substr(dataPos).find(",") + dataPos;
			// Save file was edited by a third party or corrupted, false is returned
			if (separatorPos == -1)
			{
				return false;
			}
			// Extracts attribute
			attributeData[i] = savedData.substr(dataPos, separatorPos);
			dataPos = separatorPos+1;
		}
		// Sets attributes
		std::array<int*, 9> integerSaveData = {&maxHealth, &health, &attack, &defence, &level, &experience, &experiencePoints, &position[0], &position[1]};
		for (int i=0; i<10; i++)
		{
			// Gold was multiplied by 100 to store gold as an int, must divide by 100 to receive the original value
			if (i == 9)
			{
				gold = std::stoi(attributeData[i]);
				gold /= 100;
			}
			else
			{
				// Converts the extracted string attribute to an integer
				*integerSaveData[i] = std::stoi(attributeData[i]);
			}
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

