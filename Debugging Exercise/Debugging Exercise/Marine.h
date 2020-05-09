#pragma once
#include "Entity.h"

class Marine : public Entity
{
public:
	Marine();
	~Marine();

	int attack() override;
	void takeDamage(int damage) override;

};

