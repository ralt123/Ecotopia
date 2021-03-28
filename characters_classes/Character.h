#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <array>
#include <windows.h>
#include <map>
#include <stdlib.h>
#include <time.h>

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
	char characterSymbol;
	// Constructor method
    Character(std::array<int,2> _position);

	// Decided to use separate int variables opposed to a single array for understandability
	/* Method used to override the character's stats
    
    Up to 5 optional arguments can be passed to override the character's stats
    Possible stats passed much all be integers and follow the order maxHealth, health, attack, defence, level
    Stats set to 0 or with no argument for the corresponding parameter stat will remain unchanged
    No stats can be negative*/
	void override_stats(int _maxHealth = 0, int _health = 0, int _attack = 0, int _defence = 0, int _level = 0);
	
	int deriveDamage(int damageReceived);
	
	int get_maxHealth() const;
	
    int get_health() const;
    
    int get_attack() const;
    
    int get_defence() const;
    
	int get_level() const;
	
	std::array<int,2> get_position() const;
	
	// Returns all the character's stats as a single array 
	// Return format - {maxHealth, health, attack, defence, level}
	std::array<int, 5> get_stats_array();

	// Returns a map for the character's stats so exact numeric indexes aren't required, keys are the camel case name of the attribute
	std::map<std::string, int> get_stats_map();
    
	/* Method used to heal the character by increasing their health
    Requires a positive  integer argument to indicate the heal amount
    Character's health can not exceed their maximum health*/
    void heal(int healAmount);
    
	/* Method used to directly reduce the character's health without consideration of defence
    Requires a positive integer argument to indicate the amount to reduce the health by
    Returns a boolean - True if the character died, false otherwise*/
    bool directReduceHealth(int reduction);
    
    // Identical to directReduceHealth but considers defence
    bool reduceHealth(int reduction);
};

#endif

