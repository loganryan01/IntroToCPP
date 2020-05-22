#include "Mutalisk.h"



Mutalisk::Mutalisk()
{
	health = 120;
}

Mutalisk::~Mutalisk()
{

}

// Decide the amount of damage the mutalisk will do
int Mutalisk::attack()
{
	return 27;
}

// Decrease mutalisk health by the amount of damage taken from humans
void Mutalisk::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}