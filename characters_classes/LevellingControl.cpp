#include <array>
#include "Characters.h"

class levelControl
{
private:
	int levellingOption;
	std::array<int, 3> alterStats;
	int usedPoints;
	int experiencePoints;
	
public:
	levelControl(Player &User)
	{
		// previousStats = User.get_stats_array();
		experiencePoints = User.get_experiencePoints();
		alterStats = {0,0,0};
	}
	// Adjusts the amount the level will be impacted upon confirmation
	void adjust_stat(int statIndex, int adjustAmount)
	{
		//if (previousStats[statIndex] + adjustAmount > 0 and usedPoints + adjustAmount < experiencePoints+1)
		if (adjustAmount + usedPoints <= experiencePoints and alterStats[statIndex] + adjustAmount >= 0)
		{
			alterStats[statIndex] += adjustAmount;
			usedPoints += adjustAmount;
		}
	}
	
	// Resets the levelling screen
	void reset()
	{
		alterStats = {0,0,0};
		usedPoints = 0;
	}
	
	// Confirms the point allocation made by the player
	void confirm(Player &User)
	{
		User.override_stats(User.get_maxHealth() + alterStats[0], User.get_health() + alterStats[0], User.get_attack() + alterStats[1], User.get_defence() + alterStats[2]);
		User.reduce_experiencePoints(usedPoints);
		reset();
	}
	// Methods used to get specific attributes
	int get_usedPoints() const
	{
		return usedPoints;
	}
	int get_alter_maxHealth() const
	{
		return alterStats[0];
	}
	int get_alter_attack() const
	{
		return alterStats[1];
	}
	int get_alter_defence() const
	{
		return alterStats[2];
	}
	int adjust_maxHealth(int adjustAmount) // might be pointless just remove
	{
		alterStats[0] += adjustAmount;
	}
	int get_levellingOption() const
	{
		return levellingOption;
	}
	int get_experiencePoints() const
	{
		return experiencePoints;
	}
	
	// Adjust the attribute currently selected by the player
	void next_levellingOption()
	{
		levellingOption += 1;
		if (levellingOption > 4)
		{
			levellingOption = 0;
		}
	}
	void previous_levellingOption()
	{
		levellingOption -= 1;
		if (levellingOption < 0)
		{
			levellingOption = 4;
		}
	}
};