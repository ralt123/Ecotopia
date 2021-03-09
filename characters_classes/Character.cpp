#include "Character.h"


Character::Character(std::array<int,2> _position)
{
    position = _position;
    maxHealth = 10;
    health = maxHealth;
    attack = 5;
    defence = 2;
    level = 1;
}

void Character::override_stats(int _maxHealth, int _health, int _attack, int _defence, int _level)
{
	if (_health > _maxHealth)
	{
		throw std::invalid_argument( "Health cannot exceed max health" );
	}
	std::array<int,5> newStats = {_maxHealth, _health, _attack, _defence, _level};
	// Usage of pointers to iterate through assigning new values to attributes
	std::array<int*,5> statsPointers = {&maxHealth, &health, &attack, &defence, &level};
	for (int i=0; i<5; i++)
	{
		// Prevents a stat from being wrongly set as negative
		if (newStats[i] < 0)
		{
			throw std::invalid_argument( "Stats cannot be negative");
		}
		// Attribute is unchanged if the new stat value is 0
		else if (newStats[i] != 0)
		{
			*statsPointers[i] = newStats[i];
		}
	}
}
int Character::get_maxHealth() const
{
	return maxHealth;
}
int Character::get_health() const
{
    return health;
}
int Character::get_attack() const
{
    return attack;
}
int Character::get_defence() const
{
	return defence;
}
int Character::get_level() const
{
	return level;
}


std::array<int, 5> Character::get_stats_array() 
{
	std::array<int, 5> statsArray = {maxHealth, health, attack, defence, level};
	return statsArray;
}

std::map<std::string, int> Character::get_stats_map()
{
	std::map<std::string, int> statsMap;
	std::array<int, 5> mapData = get_stats_array();
	std::array<std::string, 5> mapKeys = {"maxHealth","health","attack","defence","level"};
	for (int i=0; i<mapKeys.size(); i++)
	{
		statsMap.insert(std::pair<std::string,int>(mapKeys[i],mapData[i]));
	}
	return statsMap;
}

void Character::heal(int healAmount)
{
    if (healAmount < 0)
    {
        throw std::invalid_argument( "cannot heal by negative number" );
    }
    else
    {
        health += healAmount;
        if (maxHealth < health)
        {
            health = maxHealth;
        }
    }
}

bool Character::directReduceHealth(int reduction)
{
    if (reduction < 0)
    {
        throw std::invalid_argument( "cannot reduce health by negative number" );
    }
    else
    {
        health -= reduction;
        
        if (health<0)
        {
            return true;
        }
        return false;
    }
}

bool Character::reduceHealth(int reduction)
{
	if (reduction < 0)
	{
		throw std::invalid_argument( "cannot reduce health by negative number");
	}
	reduction -= defence;
	if (reduction < 1)
	{
		reduction = 1;
	}
	return directReduceHealth(reduction);
}


