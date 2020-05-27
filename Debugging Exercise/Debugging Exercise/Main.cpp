/*---------------------------
	File Name: Main.cpp
	Purpose: Run game.
	Author: Logan Ryan
	Modified: 26 May 2020
-----------------------------
	Copyright 2020 Logan Ryan
---------------------------*/

#include <iostream>
#include <vector>
#include <windows.h>
#include "Marine.h"
#include "Zergling.h"
#include "Mutalisk.h"
#include "Valkyrie.h"

#define ESC "\x1b"
#define CSI "\x1b["

using namespace std;

vector<Marine> squad;
vector<Zergling> swarm;
vector<Mutalisk> airSwarm;
vector<Valkyrie> fleet;

bool EnableVTMode();
void startup();
void groundBattle();
void airBattle();
bool marineAlive();
bool zerglingAlive();
bool mutaliskAlive();
bool valkyrieAlive();
void marineTurn();
void zerglingTurn();
void mutaliskTurn();
void valkyrieTurn();

//------------------------
// The main game function.
//------------------------
int main()
{
	bool fSuccess = EnableVTMode();
	if (!fSuccess)
	{
		cout << "Unable to enter VT processing mode. Quitting." << endl;
		return 0;
	}

	startup();
	groundBattle();
	airBattle();
	return 0;
}

//--------------------------------------
// Enabling Virtual Terminal Processing.
//--------------------------------------
bool EnableVTMode()
{
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}
	return true;
}

//--------------------------------
// Set up the Squad and the Swarm.
//--------------------------------
void startup()
{
	// The size of the squads.
	int squadSize = 12;
	int swarmSize = 12;
	int fleetSize = 6;
	int airSwarmSize = 6;

	// Create the marine squad.
	Marine m;
	for (size_t i = 0; i < squadSize; i++)
	{
		squad.push_back(m);
	}

	// Create the zergling swarm
	Zergling z;
	for (size_t i = 0; i < swarmSize; i++)
	{
		swarm.push_back(z);
	}

	// Create the valkyrie fleet
	Valkyrie v;
	for (size_t i = 0; i < fleetSize; i++)
	{
		fleet.push_back(v);
	}

	// Create the mutalisk swarm
	Mutalisk u;
	for (size_t i = 0; i < airSwarmSize; i++)
	{
		airSwarm.push_back(u);
	}
}

//--------------------------------------------------
// The battle between the marines and the zerglings.
//--------------------------------------------------
void groundBattle()
{
	// Move opening message to correct position.
	cout << CSI << "1;0H";
	cout << "A squad of Marines approaches a swarm of Zerglings and opens fire! The Zerglings charge!" << endl;
	// Attack each other until only one team is left alive
	while (marineAlive() && zerglingAlive()) // If anyone is left alive to fight . . .
	{
		marineTurn();
		zerglingTurn();
	}

	// Once one team is completely eliminated, the fight ends and one team wins
	cout << "The fight on the ground is over. ";
	if (marineAlive())
	{
		cout << "The Marines win but the war continues in the air." << endl;
		cout << "Press 'Enter' to continue" << endl;
		cin.get();
		cout << CSI << "2;0H";
		cout << CSI << "0J";
	}
	else
	{
		cout << "The Zerg win but the war continues in the air." << endl;
		cout << "Press 'Enter' to continue" << endl;
		cin.get();

		// Clear the messages.
		cout << CSI << "2;0H";
		cout << CSI << "0J";
	}
}

//----------------------------------------------------
// The battle between the valkyries and the mutalisks.
//----------------------------------------------------
void airBattle()
{
	// Move opening message to correct position.
	cout << CSI << "1;0H";
	cout << "A fleet of Valkyries approaches a swarm of Mutalisks and opens fire! The Mutalisks charge!" << endl;
	// Attack each other until only one team is left alive
	while (valkyrieAlive() && mutaliskAlive()) // If anyone is left alive to fight . . .
	{
		valkyrieTurn();
		mutaliskTurn();
	}

	// Once one team is completely eliminated, the fight ends and one team wins.
	cout << "The fight in the air is over. ";
	if (valkyrieAlive())
	{
		cout << "The Valkyrie win." << endl;
	}
	else
	{
		cout << "The Mutalisk win." << endl;
	}
}

//-------------------------
// Is there a Marine Alive?
//-------------------------
bool marineAlive()
{
	// Check the marine squad.
	if (squad.size() > 0)
	{
		// If the squad contains at least one marine, then there is a marine alive.
		return true;
	}
	return false;
}

//---------------------------
// Is there a Zergling Alive?
//---------------------------
bool zerglingAlive()
{
	// Check the zergling swarm.
	if (swarm.size() > 0)
	{
		// If the swarm contains at least one zergling, then there is a zergling alive.
		return true;
	}
	return false;
}

//---------------------------
// Is there a Mutalisk Alive?
//---------------------------
bool mutaliskAlive()
{
	// Check the mutalisk swarm.
	if (airSwarm.size() > 0)
	{
		// If the swarm contains at least one mutalisk, then there is a mutalisk alive.
		return true;
	}
	return false;
}

//---------------------------
// Is there a Valkyrie Alive?
//---------------------------
bool valkyrieAlive()
{
	// Check the valkyrie fleet.
	if (fleet.size() > 0)
	{
		// If the fleet contains at least one valkyrie, then there is a valkyrie alive.
		return true;
	}
	return false;
}

//-----------------------
// It's the Marines turn.
//-----------------------
void marineTurn()
{
	if (marineAlive()) // if there's at least one marine alive
	{
		// Move the output messages to the correct position. 
		cout << CSI << "2;0H";
		for (vector<Marine>::iterator i = squad.begin(); i != squad.end(); ++i) // go through the squad
		{
			// each marine will attack the first zergling in the swarm
			cout << "A marine fires for " << i->attack() << " damage. " << endl;
			swarm.begin()->takeDamage(i->attack());
			if (!swarm.begin()->isAlive()) // if the zergling dies, it is removed from the swarm
			{
				swarm.erase(swarm.begin());
				cout << "The zergling target dies" << endl;
				cout << "There are " << swarm.size() << " Zergling left." << endl;
			}
			if (!zerglingAlive()) // if there is no more zerglings left end the turn
			{
				break;
			}
		}
		cout << "Press 'Enter' to continue" << endl;
		cin.get();

		// Clear the messages.
		cout << CSI << "2;0H";
		cout << CSI << "0J";
	}
}

//-------------------------
// It's the Zerglings turn.
//-------------------------
void zerglingTurn()
{
	if (zerglingAlive()) // if there's at least one zergling alive
	{
		// Move the output messages to the correct position. 
		cout << CSI << "2;0H";
		for (vector<Zergling>::iterator i = swarm.begin(); i != swarm.end(); ++i) // loop through zerglings
		{
			// each zergling will attack the first marine in the squad
			cout << "A zergling attacks for " << i->attack() << " damage." << endl;
			squad.begin()->takeDamage(i->attack());
			if (!squad.begin()->isAlive()) // if the marine dies, it is removed from the squad
			{
				squad.erase(squad.begin());
				cout << "The marine succumbs to his wounds." << endl;
				cout << "There are " << squad.size() << " Marines left." << endl;
			}
			if (!marineAlive()) // if there is no more marines left end the turn
			{
				break;
			}
		}
		cout << "Press 'Enter' to continue" << endl;
		cin.get();

		// Clear the messages.
		cout << CSI << "2;0H";
		cout << CSI << "0J";
	}
}

//------------------------
// It's the Mutalisk turn.
//------------------------
void mutaliskTurn()
{
	if (mutaliskAlive()) // if there's at least one mutalisk alive
	{
		// Move the output messages to the correct position. 
		cout << CSI << "2;0H";
		for (vector<Mutalisk>::iterator i = airSwarm.begin(); i != airSwarm.end(); ++i) // loop through mutalisk
		{
			// each mutalisk will attack the first valkyrie in the fleet
			cout << "A mutalisk attacks for " << i->attack() << " damage." << endl;
			fleet.begin()->takeDamage(i->attack());
			if (!fleet.begin()->isAlive()) // if the valkyrie dies, it is removed from the fleet
			{
				fleet.erase(fleet.begin());
				cout << "The valkyrie explodes killing the pilot." << endl;
				cout << "There are " << fleet.size() << " valkyrie left." << endl;
			}
			if (!valkyrieAlive()) // if there is no more valkyries left end the turn
			{
				break;
			}
		}
		cout << "Press 'Enter' to continue" << endl;
		cin.get();

		// Clear the messages.
		cout << CSI << "2;0H";
		cout << CSI << "0J";
	}
}

//------------------------
// It's the Valkyrie turn.
//------------------------
void valkyrieTurn()
{
	if (valkyrieAlive()) // if there's at least one valkyrie alive
	{
		// Move the output messages to the correct position. 
		cout << CSI << "2;0H";
		for (vector<Valkyrie>::iterator i = fleet.begin(); i != fleet.end(); ++i) // go through the fleet
		{
			// each valkyrie will attack the first mutalisk in the swarm
			cout << "A valkyrie fires for " << i->attack() << " damage. " << endl;
			airSwarm.begin()->takeDamage(i->attack());
			if (!airSwarm.begin()->isAlive()) // if the mutalisk dies, it is removed from the swarm
			{
				airSwarm.erase(airSwarm.begin());
				cout << "The mutalisk target dies" << endl;
				cout << "There are " << airSwarm.size() << " Mutalisk left." << endl;
			}
			if (!mutaliskAlive()) // if there is no more mutalisks left end the turn
			{
				break;
			}
		}
		cout << "Press 'Enter' to continue" << endl;
		cin.get();

		// Clear the messages.
		cout << CSI << "2;0H";
		cout << CSI << "0J";
	}
}

// A Debugging Exercise by Marc Chee (marcc@aie.edu.au)
// 18/12/2016

// Marines are trying to "de-bug" an area (haha . . . haha)
// However something's up with this code . . . figure out what's going wrong
// When you're finished, there should be no compiler errors or warnings
// The encounter should also run and finish correctly as per the rules in the comments

// In many cases there are differences between what's in otherwise identical sections
// for Marines and Zerglings. It's good to be able to tell what the differences are
// and why they might be important.

// What's efficient and inefficient? Why?
// What uses more memory and what doesn't? Why?