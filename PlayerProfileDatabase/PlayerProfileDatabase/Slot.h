#pragma once
#include "Structures.h"

class Slot
{
public:
	Slot();
	~Slot();

	void setPosition(Point2D position);
	void setType(int type);
	void setScore(int score);
	void setInitials(char initials[4]);

	int getType();

	void drawSlots();

private:
	Point2D m_tablePosition;
	int m_type;
	Player m_player;
};

