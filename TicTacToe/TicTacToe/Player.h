#pragma once
#include "Point2D.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void setPosition(Point2D position);

	Point2D getPosition();

	void draw();

	bool executeCommand(int command);

private:
	Point2D m_gridPosition;
};

