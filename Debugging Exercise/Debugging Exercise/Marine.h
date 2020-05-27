#pragma once
#include "Entity.h"

class Marine : public Entity
{
public:
	// Constructor 
	Marine();

	// Destructor
	~Marine();

	// Generate a random attack number between 1 and 5.
	int attack() override;
};

