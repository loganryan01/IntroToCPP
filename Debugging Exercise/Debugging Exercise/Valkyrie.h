#pragma once
#include "Entity.h"

class Valkyrie : public Entity
{
public:
	Valkyrie();
	~Valkyrie();

	int attack() override;
};

