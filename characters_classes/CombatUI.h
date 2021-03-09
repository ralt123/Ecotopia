#ifndef CombatUI_H
#define CombatUI_H

#include <iostream>
#include <cwchar>
#include <windows.h>
#include "CombatControl.h"

CombatControl CombatController;

void displayFrame();

void displayCombatFrame(std::string combatIcons);

void displayStaticFrame();

void clearScreen();

void combatUILoop();

#endif

