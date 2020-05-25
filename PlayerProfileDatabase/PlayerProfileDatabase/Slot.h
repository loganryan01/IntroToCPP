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

	int binarySearch(char initials[4], int arraySize);
	
	void saveScore(int playerNumber, int binaryFilePosition);
	void saveInitials(int playerNumber, int binaryFilePosition);
	void loadInitials(int playerNumber);
	void loadScore(int playerNumber);
	int checkBinaryInitials(char oldInitials[4]);

	void drawSlots();

private:
	Point2D m_tablePosition;
	int m_type;
	Player* m_player;
};

