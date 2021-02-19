#ifndef CombatUI_H
#define CombatUI_H

#include <iostream>
#include <windows.h>
#include "CombatControl.cpp"

CombatControl CombatController;

void displayFrame();

void displayCombatFrame(std::string combatIcons);

void displayStaticFrame();

void clearScreen();

void combatUILoop();

#endif

