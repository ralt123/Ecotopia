#define CATCH_CONFIG_MAIN

#include "Character.cpp"

#include <array>
#include <catch.hpp>

// Performs various tests on the character class
TEST_CASE( "Character Class" )
{
    Character testCharacterClass({2,4});
    WHEN("Get stats array method + constructor")
    {
    	REQUIRE(testCharacterClass.get_stats_array() == std::array<int,5> {10,10,5,2,1});
	}
	
    WHEN("Get methods - Assume default value")
    {
    	REQUIRE(testCharacterClass.get_position() == std::array<int,2> {2,4});
    	REQUIRE(testCharacterClass.get_maxHealth() == 10);
    	REQUIRE(testCharacterClass.get_health() == 10);
    	REQUIRE(testCharacterClass.get_attack() == 5);
    	REQUIRE(testCharacterClass.get_defence() == 2);
    	REQUIRE(testCharacterClass.get_level() == 1);
	}
	
	WHEN("Overwrite stats method")
	{
		// Considered using a for loop to reduce written code to perform the testing but opted against for readability
		testCharacterClass.override_stats(0, 0, 0, 0, 0);
		REQUIRE(testCharacterClass.get_stats_array() == std::array<int,5> {10,10,5,2,1});
		testCharacterClass.override_stats(0, 0, 35, 0, 4);
		REQUIRE(testCharacterClass.get_stats_array() == std::array<int,5> {10,10,35,2,4});
		CHECK_THROWS(testCharacterClass.override_stats(0, 5, 35, 0, -4));
	}
	
	WHEN("Heal method")
	{
		std::array<int,10> healthArray = {10, 5, 5, 5, 1, 2, 2, 2, 2, 2};
		std::array<int,10> maxHealthArray = {10, 10, 10, 10, 10, 5, 5, 5, 5, 5};
		std::array<int,10> healArray = {5, 4, 5, 6, 8, 3, 4, 2, 0, 1};
		std::array<int,10> healthResultArray = {10, 9, 10, 10, 9, 5, 5, 4, 2, 3};
		for (int i=0; i<10; i++)
		{
			testCharacterClass.override_stats(maxHealthArray[i], healthArray[i], 0, 0, 0);
			testCharacterClass.heal(healArray[i]);
			REQUIRE(testCharacterClass.get_health() == healthResultArray[i]);
		}
		CHECK_THROWS(testCharacterClass.heal(-1));
		CHECK_THROWS(testCharacterClass.heal(-100));
	}
	
	WHEN("directReduceHealth method")
	{
		std::array<int,10> healthArray = {10, 10, 10, 5, 5, 5, 1, 1, 1, 3};
		std::array<int,10> maxHealthArray = {10, 10, 10, 10, 10, 10, 5, 5, 5, 3};
		std::array<int,10> reduceArray = {5, 10, 0, 3, 6, 1, 1000, 1, 0, 1};
		std::array<int,10> healthResultArray = {5, 0, 10, 2, 0, 4, 0, 0, 1, 2};
		for (int i=0; i<10; i++)
		{
			testCharacterClass.override_stats(maxHealthArray[i], healthArray[i], 0, 0, 0);
			if (healthResultArray[i] == 0)
			{
				REQUIRE(true == testCharacterClass.directReduceHealth(reduceArray[i]));
			}
			else
			{
				REQUIRE(false == testCharacterClass.directReduceHealth(reduceArray[i]));
			}
			REQUIRE(testCharacterClass.get_health() == healthResultArray[i]);
		}
	}
	
	WHEN("reduceHealth method")
	{
		std::array<int,10> healthArray = {10, 10, 10, 10, 5, 10, 5, 1, 1, 10};
		std::array<int,10> maxHealthArray = {10, 10, 10, 10, 10, 10, 8, 10, 1, 103};
		std::array<int,10> defenceArray = {3, 5, 5, 5, 1, 6, 2, 1, 1, 1000000};
		std::array<int,10> reduceArray = {5, 3, 10, 11, 5, 16, 10, 1, 0, 1};
		std::array<int,10> healthResultArray = {8, 9, 5, 4, 1, 0, 0, 0, 0, 9};
		for (int i=0; i<10; i++)
		{
			testCharacterClass.override_stats(maxHealthArray[i], healthArray[i], 0, defenceArray[i], 0);
			if (healthResultArray[i] == 0)
			{
				REQUIRE(true == testCharacterClass.reduceHealth(reduceArray[i]));
			}
			else
			{
				REQUIRE(false == testCharacterClass.reduceHealth(reduceArray[i]));
			}
			REQUIRE(testCharacterClass.get_health() == healthResultArray[i]);
		}
	}
}
























