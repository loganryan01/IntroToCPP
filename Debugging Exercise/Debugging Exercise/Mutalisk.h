#pragma once
#include "Entity.h"

class Mutalisk : public Entity
{
public:
	// Constructor
	Mutalisk();

	// Destructor
	~Mutalisk();

	// Generate a random attack number between 1 and 10.
	int attack() override;
};

