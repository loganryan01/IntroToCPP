#pragma once
#include "Entity.h"

class Zergling : public Entity
{
public:
	// Constructor
	Zergling();

	// Destructor
	~Zergling();

	// Generate a random attack number between 1 and 5.
	int attack() override;
};

