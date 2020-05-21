#include "Zergling.h"



Zergling::Zergling()
{
	//health = 50;
}


Zergling::~Zergling()
{
}

int Zergling::attack() 
{
	int damage = (rand() % 15) + 1;
	return damage;
}

void Zergling::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}
