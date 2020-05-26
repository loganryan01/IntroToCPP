/*-----------------------------------------------
	File Name: Mutalisk.cpp
	Purpose: Hold information about the mutalisk.
	Author: Logan Ryan
	Modified: 26 May 2020
-------------------------------------------------
	Copyright 2020 Logan Ryan
-----------------------------------------------*/

#include "Mutalisk.h"

//--------------------------------------------------------
// Set the variable for the mutalisk.
//   health (int): How much health does the mutalisk have?
//--------------------------------------------------------
Mutalisk::Mutalisk()
{
	health = 80;
	// Get a random number every time the game starts.
	srand((unsigned)time(0));
}

Mutalisk::~Mutalisk()
{
}

//-------------------------------------------------------
// Generate a random attack number between 1 and 10.
//	 attack (int): How much damage is the mutalisk doing?
//-------------------------------------------------------
int Mutalisk::attack()
{
	int attack = rand() % 10 + 1;
	return attack;
}