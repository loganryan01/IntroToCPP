/*-----------------------------------------------
	File Name: Zergling.cpp
	Purpose: Hold information about the Zergling.
	Author: Logan Ryan
	Modified: 26 May 2020
-------------------------------------------------
	Copyright 2020 Logan Ryan
-----------------------------------------------*/

#include "Zergling.h"

//--------------------------------------------------------
// Set the variable for the zergling.
//   health (int): How much health does the zergling have?
//--------------------------------------------------------
Zergling::Zergling()
{
	health = 40;
	srand((unsigned)time(0));
}

Zergling::~Zergling()
{
}

//-------------------------------------------------------
// Generate a random attack number between 1 and 5.
//	 attack (int): How much damage is the zergling doing?
//-------------------------------------------------------
int Zergling::attack()
{
	int attack = rand() % 5 + 1;
	return attack;
}