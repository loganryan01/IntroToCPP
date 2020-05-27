#pragma once
#include "Entity.h"

class Valkyrie : public Entity
{
public:
	// Constructor
	Valkyrie();

	// Destructor
	~Valkyrie();

	// Generate a random attack number between 1 and 10.
	int attack() override;
};

