#pragma once

#include "Entity.h"
class Zergling : public Entity
{
public:
	Zergling();
	~Zergling();

	int attack() override;
	void takeDamage(int damage) override;

};

