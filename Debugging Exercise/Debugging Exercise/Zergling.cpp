#include "Zergling.h"



Zergling::Zergling()
{
	health = 35;
}


Zergling::~Zergling()
{
}

// Decide the amount of damage the zergling will do
int Zergling::attack() 
{
	return 5;
}

// Decrease zergling health by the amount of damage taken from marine
void Zergling::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}