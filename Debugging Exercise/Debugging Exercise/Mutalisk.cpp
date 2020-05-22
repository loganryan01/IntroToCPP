#include "Mutalisk.h"

// Set the health for the mutalisk
Mutalisk::Mutalisk()
{
	health = 80;
	srand((unsigned)time(0));
}

Mutalisk::~Mutalisk()
{

}

// Generate a random number between 1 and 10
int Mutalisk::attack()
{
	int attack = rand() % 10 + 1;
	return attack;
}