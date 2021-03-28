#ifndef ALIEN_CPP
#define ALIEN_CPP

#include "Alien.h"

Alien::Alien(std::array<int,2> _position, char _characterSymbol, int level, int difficulty)
: Character(_position)
{
	expGiven = level*2 + 2;
	goldGiven = (std::rand()%level*5 + level*4) / 10;
	// Whilst proper balancing isn't a major concern, I can revisit the methods used to allocate stats for balancing if necessary
	characterSymbol = toupper(_characterSymbol);
	if (characterSymbol == 'R')
	{
		std::array<char,3> possibleSymbols = {'A','B','T'};
		characterSymbol = possibleSymbols[std::rand()%3];
	}
	// Adjusts stats depending on alien class
	// Extremely easy to add more alien classes
	std::array<float,3> statProbability;
	// Sets stat probabilities (for random stat allocation) and base stats for the alien depending on their character symbol which signifies class
	switch (characterSymbol)
	{
		case 'A': // Alien - Basic enemy
			statProbability = {0.4, 0.25, 0.2};
			break;
		case 'B': // Berserk - Focus on attack
			statProbability = {0.4, 0.35, 0.1};
			break;
		case 'T': // Tank - Focus on defence
			statProbability = {0.45, 0.15, 0.25};
			break;
		default: // Unknown class
			statProbability = {0.35, 0.25, 0.25};
			break;
	}
	std::array<int*,3> availableStats = {&maxHealth, &attack, &defence};
	// ~80% of stats are set to specific stats, the remaining 15% is random with certain stat bias
	int availablePoints = 11 + level;
	// Adjusts available points by the set difficulty
	switch (difficulty)
	{
		case 1:
			availablePoints = (int)availablePoints*0.6;
			break;
		case 2:
			availablePoints = (int)availablePoints*0.85;
			break;
		case 3:
			break;
		case 4:
			availablePoints = (int)availablePoints*1.1;
			break;
		case 5:
			availablePoints = (int)availablePoints*1.25;
			break;
		case 6:
			availablePoints = (int)availablePoints*1.45;
			break;
		case 7:
			availablePoints = (int)availablePoints*1.65;
			break;
		default:
			throw std::invalid_argument("invalid difficulty set");
	}
	// Causes random variation in the alien strength by increasing/decreasing available points
	availablePoints = std::rand()%(int)availablePoints*0.4 + (int)availablePoints*0.8;
	// Influences base stats for character
	for (int i=0; i<3; i++)
	{
		*availableStats[i] = statProbability[i]*availablePoints;
		std::cout << statProbability[i]*availablePoints;
		Sleep(3000);
	}
	availablePoints -= maxHealth + attack + defence;
	// Assigns remaining points randomly using the stat probabilities
	while (availablePoints > 0)
	{
		float randomSelection = std::rand()%100 / 100;
		availablePoints -= 1;
		if (randomSelection < statProbability[0])
		{
			maxHealth += 1;
		}
		else if (randomSelection < statProbability[0] + statProbability[1])
		{
			attack += 1;
		}
		else if (randomSelection < statProbability[0] + statProbability[1] + statProbability[2])
		{
			defence += 1;
		}
		else
		{
			throw std::logic_error( "error during alien stat allocation");
		}
	}
	// Each point provides 2 health points
	maxHealth *= 2;
	health = maxHealth;
	totalAliens += 1;
}

Alien::~Alien()
{
    totalAliens -= 1;
}

int Alien::get_expGiven() const
{
	return expGiven;
}

float Alien::get_goldGiven() const
{
	return goldGiven;
}

int Alien::get_alienCount()
{
  return totalAliens;
}

void Alien::experienceGivenOverride(int _expGiven)
{
	if (_expGiven < 0)
	{
		throw std::invalid_argument( "cannot set experience given below 0");
	}
	expGiven = _expGiven;
}

int Alien::totalAliens = 0;
#endif

