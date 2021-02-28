#ifndef CharacterClasses
#define CharacterClasses

#include <iostream>
#include <array>
#include <windows.h>
#include <map>

/* Character base class that is inherited by the player and alien class
Contains various attributes to resemble the character's stats and position
Contains various methods to allow manipulation of such attributes

Constructor method requires an int array of 2 elements for the character's position*/
class Character
{
// Most attributes are protected to prevent invalid values
protected:
    int maxHealth;
    int health = maxHealth;
    int attack;
    int defence;
    int level;
    std::array<int,2> position;

public:
	// Constructor method
    Character(std::array<int,2> _position)
    {
        position = _position;
        maxHealth = 10;
        health = maxHealth;
        attack = 5;
        defence = 2;
        level = 1;
    }

	// Decided to use separate int variables opposed to a single array for understandability
	/* Method used to override the character's stats
    
    Up to 5 optional arguments can be passed to override the character's stats
    Possible stats passed much all be integers and follow the order maxHealth, health, attack, defence, level
    Stats set to 0 or with no argument for the corresponding parameter stat will remain unchanged
    No stats can be negative*/
	void override_stats(int _maxHealth = 0, int _health = 0, int _attack = 0, int _defence = 0, int _level = 0)
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

    int get_health() const
    {
        return health;
    }
    int get_attack() const
    {
        return attack;
    }
    int get_defence() const
    {
    	return defence;
	}
	int get_level() const
	{
		return level;
	}
	
	// Returns all the character's stats as a single array 
	// Return format - {maxHealth, health, attack, defence, level}
	std::array<int, 5> get_stats_array() 
	{
		std::array<int, 5> statsArray = {maxHealth, health, attack, defence, level};
		return statsArray;
	}
	// Returns a map for the character's stats so exact numeric indexes aren't required, keys are the camel case name of the attribute
	std::map<std::string, int> get_stats_map()
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
    
    /* Method used to heal the character by increasing their health
    Requires a positive  integer argument to indicate the heal amount
    Character's health can not exceed their maximum health*/
    void heal(int healAmount)
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
    
    /* Method used to directly reduce the character's health without consideration of defence
    Requires a positive integer argument to indicate the amount to reduce the health by
    Returns a boolean - True if the character died, false otherwise*/
    bool directReduceHealth(int reduction)
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
    
    // Identical to directReduceHealth but considers defence
    bool reduceHealth(int reduction)
    {
    	if (reduction < 0)
    	{
    		throw std::invalid_argument( "cannot reduce health by negative number");
		}
    	reduction -= defence;
    	if (reduction < 0)
    	{
    		reduction = 1;
		}
    	return directReduceHealth(reduction);
	}
};

/* Alien class, inherits from the character class

Constructor method requires an int array of 2 elements for the alien's position*
The constructor method can receive two optional arguments, characterSymbol and level

Level should generally be around the same level as the player as it dictates the alien's stats
characterSymbol sets the alien's class and technique for generating stats as well as the symbol for representing the character on the map
If a characterSymbol is set of which does not correspond to a class, the alien's stats should be set through the "override_stats" method*/
class Alien: public Character
{
private:
    static int totalAliens;
    int expGiven;
public:
	// Documentation for constructor method within initial class documentation
    Alien(std::array<int,2> _position, char characterSymbol = 'A', int level = 1)
    : Character(_position)
    {
        totalAliens += 1;
        expGiven = 5;
    }
    ~Alien()
    {
        totalAliens -= 1;
    }
    int get_expGiven() const
    {
    	return expGiven;
	}
    static int get_alienCount()
    {
      return totalAliens;
    }
    /* Used to override the amount of experience given to the player upon alien's death
    Requires a positive integer argument to represent the new experience given amount */
    void experienceGivenOverride(int _expGiven)
    {
    	if (_expGiven < 0)
    	{
    		throw std::invalid_argument( "cannot set experience given below 0");
		}
		expGiven = _expGiven;
	}
};

/* Player class, inherits from the character class

Used to represent the player's character
Provides methods to allow for combat*/
class Player: public Character
{
private:
	int experience;
    int totalExperience;
    int experiencePoints;
public:
	// Constructor method
    Player(std::array<int,2> _position)
    : Character(_position)
    {
        int combatOption = 0;
        experience = 0;
        totalExperience = 0;
    }
    
    /* Method used to override the player's stats
    Same as the "override_stats" in the Character class with the addition of the experience attribute, documentation is repeated for simplicity
    
    Up to 6 optional arguments can be passed to override the character's stats
    Possible stats passed much all be integers and follow the order maxHealth, health, attack, defence, level, experience
    Stats set to 0 or with no argument for the corresponding parameter stat will remain unchanged
    No stats can be negative
    */
    void override_stats(int _maxHealth = 0, int _health = 0, int _attack = 0, int _defence = 0, int _level = 0, int _experience = 0)
    {
    	Character::override_stats(_maxHealth, _health, _attack, _defence, _level);
    	if (_experience < -1)
    	{
    		throw std::invalid_argument( "cannot set experience given below 0");
		}
		else if (_experience != -1)
		{
			increase_experience(_experience);
		}
		
	}
    
    int get_experience() const
    {
    	return experience;
	}
    
    /* Method used to increase the player's experience
    Returns a boolean - true if the player levelled up, false otherwise
    Accepts a positive or negative integer
    Player levels up if they have sufficient experience
    Player cannot go below 0 experience and therefore cannot delevel*/
    bool increase_experience(int expGained)
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
    /* Player attacks the provided object of alien class
    Returns a boolean - true if the enemy is killed, false otherwise*/
    bool attackFoe(Alien &other)
    {
        other.reduceHealth(attack);
        if (other.get_health() < 1)
        {
            return true;
        }
        return false;
    }
    
    /* Player is attacked by the provided object of alien class
    Returns a boolean - true if the player is killed, false otherwise*/
    bool defend(Alien &other)
    {
    	reduceHealth(other.get_attack());
        if (health < 1)
        {
            return true;
        }
        return false;
    }
    /* Player is attacked by the provided object alien class
    Used whilst the player is defending after having selected the "defend" action and increases the player's defence by 50% when attacked
    Returns a boolean - true if the player is killed, false otherwise*/
    bool preparedDefend(Alien &other)
    {
    	int actualDefence = defence;
    	defence = int(defence * 1.5);
    	bool result = defend(other);
    	defence = actualDefence;
    	return result;
	}
};



int Alien::totalAliens = 0;
#endif
