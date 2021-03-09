#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Alien.h"

#include <iostream>
#include <array>
#include <windows.h>
#include <map>
#include <stdlib.h>
#include <time.h>


/* Player class, inherits from the character class

Used to represent the player's character
Provides methods to allow for combat*/
class Player: public Character
{
private:
	int experience;
    int totalExperience;
    int experiencePoints;
    float gold;
public:
	// Constructor method
    Player(std::array<int,2> _position);
    
    /* Method used to override the player's stats
    Same as the "override_stats" in the Character class with the addition of the experience attribute, documentation is repeated for simplicity
    
    Up to 6 optional arguments can be passed to override the character's stats
    Possible stats passed much all be integers and follow the order maxHealth, health, attack, defence, level, experience
    Stats set to 0 or with no argument for the corresponding parameter stat will remain unchanged
    No stats can be negative*/
    void override_stats(int _maxHealth = 0, int _health = 0, int _attack = 0, int _defence = 0, int _level = 0, int _experience = 0);
    
    int get_experience() const;
    
	int get_experiencePoints() const;
	
	float get_gold() const;
	
	
	void reduce_experiencePoints(int reduceBy);
    
    // Increases the gold by the received positive/negative float argument
    // Gold can not go below 0, if it does then gold is simply set to 0 without raising an expection 
    void alter_gold(float increaseBy);
    
    // If the player has more or equal gold to the cost, gold is reduced by the cost and true is returned.
    // If the player does not have sufficent funds, no gold is deducted and false is returned
    bool make_purchase(float cost);
    
    /* Method used to increase the player's experience
    Returns a boolean - true if the player levelled up, false otherwise
    Accepts a positive or negative integer
    Player levels up if they have sufficient experience
    Player cannot go below 0 experience and therefore cannot delevel*/
    bool increase_experience(int expGained);
    
    /* Player attacks the provided object of alien class
    Returns a boolean - true if the enemy is killed, false otherwise*/
    bool attackFoe(Alien &other);
    
    /* Player is attacked by the provided object of alien class
    Returns a boolean - true if the player is killed, false otherwise*/
    bool defend(Alien &other);
    
    /* Player is attacked by the provided object alien class
    Used whilst the player is defending after having selected the "defend" action and increases the player's defence by 50% when attacked
    Returns a boolean - true if the player is killed, false otherwise*/
    bool preparedDefend(Alien &other);
};

#endif

