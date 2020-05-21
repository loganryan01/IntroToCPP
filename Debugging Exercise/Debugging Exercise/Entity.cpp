#include "Entity.h"



Entity::Entity() : health{ 50 }
{
}


Entity::~Entity()
{
}

int Entity::attack()
{
	return 0;
}

void Entity::takeDamage(int damage)
{
}

bool Entity::isAlive()
{
	return health;
}
