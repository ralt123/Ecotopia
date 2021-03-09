#include "Alien.h"


// Documentation for constructor method within initial class documentation
Alien::Alien(std::array<int,2> _position, char _characterSymbol, int level)
: Character(_position)
{
	expGiven = level + 5;
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
	switch (characterSymbol)
	{
		case 'A': // Alien - Basic enemy
			statProbability = {0.5, 0.2, 0.15};
			break;
		case 'B': // Berserk - Focus on attack
			statProbability = {0.4, 0.35, 0.1};
			break;
		case 'T': // Tank - Focus on defence
			statProbability = {0.45, 0.15, 0.25};
			break;
		// Unknown class
		default:
			statProbability = {0.35, 0.25, 0.25};
			break;
	}
	std::array<int*,3> availableStats = {&maxHealth, &attack, &defence};
	// ~85% of stats are set to specific stats, the remaining 15% is random with certain stat bias
	int availablePoints = 13 + level;
	for (int i=0; i<3; i++)
	{
		*availableStats[i] = statProbability[i]*availablePoints;
	}
	availablePoints -= maxHealth + attack + defence;
	availablePoints = std::rand()%(int)availablePoints*0.4 + (int)availablePoints*0.8;
	while (availablePoints > 0)
		{
			int randomSelection = std::rand()%85;
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
		}
	totalAliens += 1;
	std::cout << "-- " << maxHealth << "-" << attack << "-" << defence << std::endl;
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

