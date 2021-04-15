// MAIN HEADER FILE 
#include "item_animation/animation.h"
#include "sql_development\libs\sqlite3.h"
#include "map_development\console_settings.h"
#include "map_development\chunk_generation.h"
#include "characters_classes\Player.cpp"
Player User({0,0});
Alien Foe({0,1});

#include "characters_classes\CombatUI.cpp"
#include "characters_classes\LevellingUI.cpp"
#include "characters_classes\StatsUI.cpp"
#include "Inventory\drop_rates.h"
#include "Inventory\Inventory.cpp"

#include <fstream>
#include <iostream>
#include <vector>
#include<sstream>
