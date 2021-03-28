// Character class tests should be performed before player class tests

#define CATCH_CONFIG_MAIN

#include "Player.cpp"

#include <array>
#include <catch.hpp>

// Various tests regarding the player and alien class, assumes the character class passed all tests previously 
TEST_CASE( "Player/Alien Class" )
{
    Player testPlayerClass({2,4});
    Alien testAlienClass({3,4});
    
    WHEN("Experience methods")
    {
    	std::array<int,10> levelArray = {1, 1, 2, 3, 3, 3, 1, 10, 4, 5};
    	std::array<int,10> expArray = {0, 4, 5, 2, 5, 4, 9, 40, 16, 12};
    	std::array<int,10> expIncreaseArray = {10, 11, 15, 47, -100, 6, 1, 70, -14, 0};
    	std::array<int,10> resultExpArray = {0, 5, 5, 4, 0, 10, 0, 55, 2, 12};
    	std::array<int,10> resultLevelArray = {2, 2, 3, 5, 3, 3, 2, 11, 4, 5};
		
    	for (int i=0; i<10; i++)
    	{
    		testPlayerClass.override_stats(0, 0, 0, 0, levelArray[i], expArray[i], 3);
    		if (resultLevelArray[i] > levelArray[i])
    		{
    			REQUIRE(testPlayerClass.alter_experience(expIncreaseArray[i]));
			}
			else
			{
				REQUIRE(not testPlayerClass.alter_experience(expIncreaseArray[i]));
			}
    		REQUIRE(testPlayerClass.get_experience() == resultExpArray[i]);
    		REQUIRE(testPlayerClass.get_level() == resultLevelArray[i]);
    		REQUIRE(testPlayerClass.get_experiencePoints() == 3 + resultLevelArray[i] - levelArray[i]);
		}
		CHECK_THROWS(testPlayerClass.override_stats(0, 0, 0, 0, 0, -2));
		CHECK_THROWS(testPlayerClass.override_stats(0, 0, 0, 0, 0, -34));
		CHECK_THROWS(testPlayerClass.override_stats(0, 0, 0, 0, 0, -1, -2));
		CHECK_THROWS(testPlayerClass.override_stats(0, 0, 0, 0, 0, -1, -53));
		CHECK_THROWS(testPlayerClass.override_stats(0, 0, 0, 0, 0, -2, -2));
		CHECK_THROWS(testPlayerClass.override_stats(0, 0, 0, 0, 0, -42, -23));
	}
    
    WHEN("Gold methods")
    {
    	std::array<int,10> goldArray = {0, 100, 100, 100, 100, 200, 2, 50, 0, 50};
    	std::array<int,10> goldIncreaseArray = {-10, 50, 640, 100, 100, -50, -1, 0, 100, 50};
    	std::array<int,10> purchaseArray = {20, 140, 740, 201, 199, 100, 1, 45, 95, 0};
    	std::array<int,10> resultGoldArray = {0, 10, 0, 200, 1, 50, 0, 5, 5, 100};
		
    	for (int i=0; i<10; i++)
    	{
    		testPlayerClass.alter_gold(-testPlayerClass.get_gold());
    		REQUIRE(testPlayerClass.get_gold() == 0);
    		testPlayerClass.alter_gold(goldArray[i]);
    		REQUIRE(testPlayerClass.get_gold() == goldArray[i]);
    		testPlayerClass.alter_gold(goldIncreaseArray[i]);
    		REQUIRE(testPlayerClass.get_gold() == goldArray[i] + testPlayerClass.derive_gold_adjustment(goldIncreaseArray[i]));
    		if (goldArray[i] + goldIncreaseArray[i] >= purchaseArray[i])
    		{
    			REQUIRE(testPlayerClass.make_purchase(purchaseArray[i]));
			}
			else
			{
				REQUIRE(not testPlayerClass.make_purchase(purchaseArray[i]));
			}
    		REQUIRE(testPlayerClass.get_gold() == resultGoldArray[i]);
		}
	}
    
    WHEN("Combat methods")
    {
    	std::array<int,10> playerHealthArray = {10, 5, 5, 3, 5, 1, 15, 15, 4, 15};
    	std::array<int,10> playerMaxHealthArray = {10, 10, 10, 10, 10, 1, 15, 15, 10, 15};
    	std::array<int,10> playerAttackArray = {5, 5, 5, 8, 5, 5, 10, 7, 5, 20};
    	std::array<int,10> playerDefenceArray = {2, 2, 99, 2, 4, 99, 3, 5, 3, 5};
    	
    	std::array<int,10> alienHealthArray = {10, 5, 5, 3, 5, 10, 8, 10, 10, 6};
    	std::array<int,10> alienMaxHealthArray = {10, 10, 10, 10, 10, 10, 12, 10, 10, 10};
    	std::array<int,10> alienAttackArray = {5, 5, 5, 8, 9, 5, 7, 20, 20, 6};
    	std::array<int,10> alienDefenceArray = {2, 2, 2, 2, 0, 5, 5, 3, 5, 2};
    	
    	// Whilst this may seem unnecessary, it simplifies adding tests for future combat methods
    	struct setStats
		{
			std::array<int,10> pArray;
			std::array<int,10> aArray;
			Player* playerRef;
			Alien* alienRef;
			
			setStats(std::array<int,10> _pArray, std::array<int,10> _aArray, Player* _playerRef, Alien* _alienRef)
			{
				pArray = _pArray;
				aArray = _aArray;
				playerRef = _playerRef;
				alienRef = _alienRef;
			}
			
			void set(int i)
			{
				playerRef -> override_stats(pArray[i], pArray[i], pArray[i], pArray[i]);
    			alienRef -> override_stats(aArray[i], aArray[i], aArray[i], aArray[i]);
			}
		};
		
		setStats setter(playerMaxHealthArray, alienMaxHealthArray, &testPlayerClass, &testAlienClass);
    	/*
    	auto setStats = [](Player testPlayerClass, Alien testAlienClass) 
		{ 
			testPlayerClass.override_stats(0, 0, 0, 0, levelArray[i], expArray[i]);
    		testAlienClass.override_stats(0, 0, 0, 0, levelArray[i], expArray[i]);
		}; */
    	AND_WHEN("attackFoe method ")
    	{
    		std::array<int,10> resultHealthArray = {7, 2, 2, -3, 0, 9, 3, 6, 9, -12};
    		for (int i=0; i<10; i++)
    		{
    			setter.set(i);
    			
    			testPlayerClass.attackFoe(testAlienClass);
			}
		}
		
		AND_WHEN("defend method")
		{
			std::array<int,10> resultHealthArray = {7, 2, 4, -3, 0, 0, 11, 0, -13, 14};
    		for (int i=0; i<10; i++)
    		{
    			setter.set(i);
    			
    			testPlayerClass.defend(testAlienClass);
			}
		}
		
		AND_WHEN("preparedDefend method")
		{
			std::array<int,10> resultHealthArray = {8, 3, 4, -2, 2, 0, 12, 2, -11, 14};
    		for (int i=0; i<10; i++)
    		{
    			setter.set(i);
    			
    			testPlayerClass.preparedDefend(testAlienClass);
			}
		}
		
	}
}








