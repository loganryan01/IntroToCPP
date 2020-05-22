#pragma once
#include "Entity.h"

class Mutalisk : public Entity
{
public:
	Mutalisk();
	~Mutalisk();

	int attack() override;
};

