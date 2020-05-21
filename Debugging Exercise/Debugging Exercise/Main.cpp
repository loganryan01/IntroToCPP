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

#include <iostream>
#include <vector>
#include "Marine.h"
#include "Zergling.h"

using namespace std;

vector<Marine> squad;
vector<Zergling> swarm;

void startup();
bool marineAlive();
bool zerglingAlive();
void marineTurn();
void zerglingTurn();
void extendMarineSquad();
//void extendZerglingSquad();

int main()
{
	startup();
	extendMarineSquad();

	cout << "A squad of marines approaches a swarm of Zerglings and opens fire! The Zerglings charge!" << endl;
	// Attack each other until only one team is left alive
	while (marineAlive() && zerglingAlive()) // If anyone is left alive to fight . . .
	{
		marineTurn();
		zerglingTurn();
	}

	// Once one team is completely eliminated, the fight ends and one team wins
	cout << "The fight is over. ";
	if (marineAlive())
	{
		cout << "The Marines win." << endl;
	} else 
	{
		cout << "The Zerg win." << endl;
	}
}

// Set up the Squad and the Swarm at their initial sizes listed below
void startup()
{
	// Enter the starting size of the squads
	int squadSize = 10;
	int swarmSize = 10;

	Marine m;
	for (size_t i = 0; i < squadSize; i++)
	{
		squad.push_back(m);
	}

	Zergling z;
	for (size_t i = 0; i < swarmSize; i++)
	{
		swarm.push_back(z);
	}
}

// Is there a Marine Alive?
bool marineAlive()
{
	return squad.size() > 0;
}

// Is there a Zergling Alive?
bool zerglingAlive()
{
	return swarm.size() > 0;
}

// It's the Marines turn
void marineTurn()
{
	if (marineAlive()) // if there's at least one marine alive
	{
		for (vector<Marine>::iterator i = squad.begin(); i != squad.end(); ++i) // go through the squad
		{
			// each marine will attack the first zergling in the swarm
			cout << "A marine fires for " << i->attack() << " damage. " << endl;
			swarm.begin()->takeDamage(i->attack());
			if (!swarm.begin()->isAlive()) // if the zergling dies, it is removed from the swarm
			{
				cout << "The zergling target dies" << endl;
				swarm.erase(swarm.begin());
			}
			if (!zerglingAlive()) // if there is no more zerglings left end the turn
			{
				break;
			}
		}
	}
}

// It's the Zerglings turn
void zerglingTurn()
{
	if (zerglingAlive()) // if there's at least one zergling alive
	{
		for (vector<Zergling>::iterator i = swarm.begin(); i != swarm.end(); ++i) // loop through zerglings
		{
			// each zergling will attack the first marine in the squad
			cout << "A zergling attacks for " << i->attack() << " damage." << endl;
			squad.begin()->takeDamage(i->attack());
			if (!squad.begin()->isAlive()) // if the marine dies, it is removed from the squad
			{
				squad.erase(squad.begin());
				cout << "The marine succumbs to his wounds." << endl;
			}
			if (!marineAlive()) // if there is no more marines left end the turn
			{
				break;
			}
		}
	}
}

// If you want to extend the Marine squad
void extendMarineSquad()
{
	// Replace the 0 with how many more marines you want to add
	int newMarines = 0;

	Marine m;
	for (size_t i = 0; i < newMarines; i++)
	{
		squad.push_back(m);
	}
}