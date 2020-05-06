#pragma once

#include "Point2D.h"

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void setPosition(Point2D position);

	Point2D getPosition();

private:
	Point2D m_gridPosition;
};

