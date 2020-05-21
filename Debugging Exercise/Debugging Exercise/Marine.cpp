#include "Marine.h"



Marine::Marine()
{
	health = 40;
}


Marine::~Marine()
{
}

// Decide the amount of damage the marine will do
int Marine::attack()
{
	return 6;
}

// Decrease marine health by the amount of damage taken from zergling
void Marine::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}
