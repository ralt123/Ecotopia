#include <iostream>
#include <array>
#include <windows.h>

// Character base class that is inherited by the player and alien class
class Character
{
protected:
    int maxHealth;
    int health = maxHealth;
    int attack;
    int defense;
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
        defense = 2;
        level = 1;
    }

    int get_health() const
    {
        return health;
    }
    int get_attack() const
    {
        return attack;
    }
    
    // void operator
    
    /* Method used to heal the character by increasing their health
    Requires a postive integer argument to indicate the heal amount
    Character's health can not exceed their maximum health
    */
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
    Requires a postive integer argument to indicate the amount to reduce the health by
    Returns a boolean - True if the character died, false otherwise
    */
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
    		throw std::invalid_argument( "cannot reduce health by negative number" );
		}
    	reduction -= defense;
    	if (reduction < 0)
    	{
    		reduction = 1;
		}
    	return directReduceHealth(reduction);
	}
};

/* Alien class, inherits from the character class
*/
class Alien: public Character
{
private:
    static int totalAliens;
    int expGiven;
public:
    Alien(std::array<int,2> _position)
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
    static int alienCount()
    {
      return totalAliens;
    }
    /* Used to overried the amount of experience given to the player upon alien's death
    Requires a positive integer argument to represent the new experience given amount */
    void experienceGivenOverride(int _expGiven)
    {
    	if (_expGiven < 0)
    	{
    		throw std::invalid_argument( "cannot set experience given below 0" );
		}
		expGiven = _expGiven;
	}
};

/* Player class, inherits from the character class
*/
class Player: public Character
{
private:
	int experience;
    int totalExperience;
public:
	// Constructor method
    Player(std::array<int,2> _position)
    : Character(_position)
    {
        int combatOption = 0;
        experience = 0;
        totalExperience = 0;
    }
    
    int get_experience() const
    {
    	return experience;
	}
	int get_level() const
	{
		return level;
	}
    
    /* Method used to increase the player's experience
    Returns a boolean - true if the player levelled up, false otherwise
    Accepts a postive or negative integer
    Player levels up if they have sufficent experience
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
    
    /* Player is attacked the provided object of alien class
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
};

int Alien::totalAliens = 0;


