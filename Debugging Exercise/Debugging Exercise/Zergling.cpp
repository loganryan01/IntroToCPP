#include "Zergling.h"

// Set the health for the zergling
Zergling::Zergling()
{
	health = 40;
	srand(time(0));
}

Zergling::~Zergling()
{
}

// Generate a random number between 1 and 5
int Zergling::attack()
{
	int attack = rand() % 5 + 1;
	return attack;
}