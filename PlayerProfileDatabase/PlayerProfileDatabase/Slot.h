#pragma once
#include "Structures.h"

class Slot
{
public:
	Slot();
	~Slot();

	void setPosition(Point2D position);
	void setType(int type);
	void setScore(int score, int playerNumber);
	void setInitials(char initials[4], int playerNumber);

	int getType();
	int getScore(int playerNumber);
	char getInitial(int playerNumber, int initialsPosition);

	int binarySearch(char initials[4]);
	
	void saveScore(int playerNumber);
	void saveInitials(int playerNumber);
	void loadInitials(int playerNumber);
	void loadScore(int playerNumber);

	void drawSlots();

private:
	Point2D m_tablePosition;
	int m_type;
	Player* m_player;
};

