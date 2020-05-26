/*---------------------------------------------
	File Name: Marine.cpp
	Purpose: Hold information about the marine.
	Author: Logan Ryan
	Modified: 26 May 2020
-----------------------------------------------
	Copyright 2020 Logan Ryan
---------------------------------------------*/

#include "Marine.h"

//------------------------------------------------------
// Set the variable for the marine.
//   health (int): How much health does the marine have?
//------------------------------------------------------
Marine::Marine()
{
	health = 40;
	// Get a random number every time the game starts.
	srand((unsigned)time(0));
}

Marine::~Marine()
{
}

//-----------------------------------------------------
// Generate a random attack number between 1 and 5.
//	 attack (int): How much damage is the marine doing?
//-----------------------------------------------------
int Marine::attack()
{
	int attack = rand() % 5 + 1;
	return attack;
}