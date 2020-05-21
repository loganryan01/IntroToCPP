#include "Valkyrie.h"



Valkyrie::Valkyrie()
{
	health = 200;
}

Valkyrie::~Valkyrie()
{

}

// Decide the amount of damage the valkyrie will do
int Valkyrie::attack()
{
	return 48;
}

// Decrease valkyrie health by the amount of damage taken from zerg
void Valkyrie::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}