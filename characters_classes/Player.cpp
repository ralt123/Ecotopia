#include "Player.h"

// Constructor method
Player::Player(std::array<int,2> _position)
: Character(_position)
{
	char characterSymbol = '@';
    int combatOption = 0;
    experience = 0;
    totalExperience = 0;
    gold = 10;
    experiencePoints = 3;
}


void Player::override_stats(int _maxHealth, int _health, int _attack, int _defence, int _level, int _experience)
{
	Character::override_stats(_maxHealth, _health, _attack, _defence, _level);
	if (_experience < -1)
	{
		throw std::invalid_argument("cannot set experience given below 0");
	}
	else if (_experience != -1)
	{
		increase_experience(_experience);
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
	if (experiencePoints - reduceBy < 0)
	{
		throw std::invalid_argument("experience points cannot go below 0");
	}
	experiencePoints -= reduceBy;
}


void Player::alter_gold(float increaseBy)
{
	gold += increaseBy;
	if (gold < 0)
	{
		gold = 0;
	}
	gold = ((int)(gold*100))/100;
}


bool Player::make_purchase(float cost)
{
	// cost = ((int)(cost*100))/100;
	if (cost > gold)
	{
		return false;
	}
	gold -= cost;
	return true;
}

bool Player::increase_experience(int expGained)
{
	experience += expGained;
	totalExperience += expGained;
	if (experience > level*5 + 5)
	{
		while (experience > level*5 + 5)
		{
			experience -= level*5 + 5;
			level += 1;
			experiencePoints += 1;
		}
		return true;
	}
	else if (experience < 0)
	{
		experience = 0;
	}
	return false;
}


bool Player::attackFoe(Alien &other)
{
    other.reduceHealth(attack);
    if (other.get_health() < 1)
    {
        return true;
    }
    return false;
}


bool Player::defend(Alien &other)
{
	reduceHealth(other.get_attack());
    if (health < 1)
    {
        return true;
    }
    return false;
}

bool Player::preparedDefend(Alien &other)
{
	int actualDefence = defence;
	defence = int(defence * 1.5);
	bool result = defend(other);
	defence = actualDefence;
	return result;
}


