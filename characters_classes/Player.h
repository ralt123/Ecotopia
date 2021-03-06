#ifndef PLAYER_H
#define PLAYER_H

#include "Character.cpp"
#include "Alien.cpp"
#include "Stats.cpp"
#include "SaveManagement.cpp"

#include <iostream>
#include <array>
#include <windows.h>
#include <map>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>


/* Player class, inherits from the character class

Used to represent the player's character
Provides methods to allow for combat*/
class Player: public Character
{
private:
	int experience;
    int experiencePoints;
    // Gold should have at most 2 decimal places
    float gold;
    Statistics playerStatistics;

public:
	// Constructor method - requires the player's position on the map (integer array of size 2)
    Player(std::array<int,2> _position);
    
    /* Method used to override the player's stats
    Same as the "override_stats" in the Character class with the addition of the experience attribute, documentation is repeated for simplicity.
    Experience remains unchanged when set to the integer -1
    
    Up to 6 optional arguments can be passed to override the character's stats
    Possible stats passed much all be integers and follow the order maxHealth, health, attack, defence, level, experience
    Stats set to 0 or with no argument for the corresponding parameter stat will remain unchanged
    No stats can be negative*/
    void override_stats(int _maxHealth = 0, int _health = 0, int _attack = 0, int _defence = 0, int _level = 0, int _experience = -1, int _experiencePoints = -1);
    
    // Gets methods for private attributes
    int get_experience() const;
    
	int get_experiencePoints() const;
	
	float get_gold() const;
	
	// Set as public to allow for ease of testing
	float derive_gold_adjustment(float baseAdjustment);
	
	// Reduces experience points by the provided argument - argument must be positive
	void reduce_experiencePoints(int reduceBy);
    
    // Increases the gold by the received positive/negative float argument
    // Gold can not go below 0, if it does then gold is simply set to 0 without raising an expection 
    void alter_gold(float increaseBy);
    
    /* If the player has more or equal gold to the cost, gold is reduced by the cost and true is returned.
    If the player does not have sufficent funds, no gold is deducted and false is returned
    Passed float can be negative which would result in the player gaining gold  */
    bool make_purchase(float cost);
    
    /* Method used to increase the player's experience
    Returns a boolean - true if the player levelled up, false otherwise
    Accepts a positive or negative integer
    Player levels up if they have sufficient experience
    Player cannot go below 0 experience and therefore cannot delevel*/
    bool alter_experience(int expGained);
    
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
    
    /* Reduces the player's health without consideration for defense
    returns 0 if the player died, false otherwise */
    bool direct_reduce_health(int reduction);
    
    /* Invoked when the player dies
    punishes the player by deducting health and experience */
    std::array<int, 2> death();
    
    /* Returns the statistic specified by the string argument
    the string passed refers to the attribute name in the statistics class of the desired statsitic */
    float get_statistic(std::string requestedVariable);
    
    Statistics* get_statistic_object_pointer();
    
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

