#include "Marine.h"



// Set the health for the marines
Marine::Marine()
{
	health = 40;
	srand((unsigned)time(0));
}

Marine::~Marine()
{
}

// Generate a random number between 1 and 5
int Marine::attack()
{
	int attack = rand() % 5 + 1;
	return attack;
}
