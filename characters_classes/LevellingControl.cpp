#include "LevellingControl.h"


levelControl::levelControl(Player &User)
{
	experiencePoints = User.get_experiencePoints();
	alterStats = {0,0,0};
}

void levelControl::adjust_stat(int statIndex, int adjustAmount)
{
	// Stat allocation is only changed if the intended change results in a valid state
	if (adjustAmount + usedPoints <= experiencePoints and alterStats[statIndex] + adjustAmount >= 0)
	{
		usedPoints += adjustAmount;
		// Health increased by 2 per allocated experience point
		if (statIndex == 0)
		{
			adjustAmount *= 2;
		}
		alterStats[statIndex] += adjustAmount;
	}
}

void levelControl::reset()
{
	alterStats = {0,0,0};
	usedPoints = 0;
}

void levelControl::confirm(Player &User)
{
	User.override_stats(User.get_maxHealth() + alterStats[0], User.get_health() + alterStats[0], User.get_attack() + alterStats[1], User.get_defence() + alterStats[2]);
	User.reduce_experiencePoints(usedPoints);
	reset();
}

int levelControl::get_usedPoints() const
{
	return usedPoints;
}

int levelControl::get_alter_maxHealth() const
{
	return alterStats[0];
}

int levelControl::get_alter_attack() const
{
	return alterStats[1];
}

int levelControl::get_alter_defence() const
{
	return alterStats[2];
}

int levelControl::get_levellingOption() const
{
	return levellingOption;
}

int levelControl::get_experiencePoints() const
{
	return experiencePoints;
}
void levelControl::next_levellingOption()
{
	levellingOption += 1;
	if (levellingOption > 4)
	{
		levellingOption = 0;
	}
}

void levelControl::previous_levellingOption()
{
	levellingOption -= 1;
	if (levellingOption < 0)
	{
		levellingOption = 4;
	}
}

