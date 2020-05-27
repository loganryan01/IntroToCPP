#pragma once
#include <cstdlib>
#include <ctime>
class Entity
{
public:
	// Constructor
	Entity();

	// Destructor
	~Entity();

	// Default attack number
	virtual int attack();
	void takeDamage(int damage);
	bool isAlive();

public:
	int health;
};