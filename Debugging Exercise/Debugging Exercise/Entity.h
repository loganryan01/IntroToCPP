#pragma once
#include <cstdlib>
#include <ctime>
class Entity
{
public:
	Entity();
	~Entity();

	virtual int attack();
	void takeDamage(int damage);
	bool isAlive();

public:
	int health;
};