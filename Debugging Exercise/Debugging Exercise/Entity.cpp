#include "Entity.h"


// The default health for all entities is 50
Entity::Entity() : health{ 50 }
{
}


Entity::~Entity()
{
}

int Entity::attack()
{
	return 10;
}

// This calculates the new health for the entities
void Entity::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}

// Checks if a single entity is alive
bool Entity::isAlive()
{
	if (health > 0)
	{
		return true;
	}
	return false;
}
