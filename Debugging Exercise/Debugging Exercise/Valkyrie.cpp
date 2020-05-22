#include "Valkyrie.h"


// set the health for the valkyrie
Valkyrie::Valkyrie()
{
	health = 80;
	srand((unsigned)time(0));
}

Valkyrie::~Valkyrie()
{

}

// Generate a number between 1 and 10
int Valkyrie::attack()
{
	int attack = rand() % 10 + 1;
	return attack;
}