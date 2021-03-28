#ifndef ALIEN_H
#define ALIEN_H

#include <iostream>
#include <array>
#include <windows.h>
#include <map>
#include <stdlib.h>
#include <time.h>

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
    float goldGiven;
public:
	// Documentation for constructor method within initial class documentation
    Alien(std::array<int,2> _position, char _characterSymbol = 'R', int level = 1, int difficulty = 3);
    
    ~Alien();
    
    // Get methods for private attributes
    int get_expGiven() const;
    
	float get_goldGiven() const;
	
    static int get_alienCount();

    /* Used to override the amount of experience given to the player upon alien's death
    Requires a positive integer argument to represent the new experience given amount 
	Ideal for bosses or unique aliens */
    void experienceGivenOverride(int _expGiven);
};

#endif

