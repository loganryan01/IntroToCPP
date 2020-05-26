/*-----------------------------------------------
	File Name: Valkyrie.cpp
	Purpose: Hold information about the valkyrie.
	Author: Logan Ryan
	Modified: 26 May 2020
-------------------------------------------------
	Copyright 2020 Logan Ryan
-----------------------------------------------*/

#include "Valkyrie.h"

//--------------------------------------------------------
// Set the variable for the valkyrie.
//   health (int): How much health does the valkyrie have?
//--------------------------------------------------------
Valkyrie::Valkyrie()
{
	health = 80;
	// Get a random number every time the game starts.
	srand((unsigned)time(0));
}

Valkyrie::~Valkyrie()
{

}

//-------------------------------------------------------
// Generate a random attack number between 1 and 10.
//	 attack (int): How much damage is the valkyrie doing?
//-------------------------------------------------------
int Valkyrie::attack()
{
	int attack = rand() % 10 + 1;
	return attack;
}