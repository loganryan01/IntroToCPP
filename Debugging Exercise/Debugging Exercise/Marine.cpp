#include "Marine.h"



Marine::Marine()
{
	health = 50;
}


Marine::~Marine()
{
}

int Marine::attack()
{
	int damage = (rand() % 15) + 1;
	return damage;
}

void Marine::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}
