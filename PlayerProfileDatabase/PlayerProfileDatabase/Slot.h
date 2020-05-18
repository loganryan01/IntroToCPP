#pragma once
#include "Structures.h"

class Slot
{
public:
	Slot();
	~Slot();

	void setPosition(Point2D position);
	void setType(int type);
	void setScore(int score, int choice);
	void setInitials(char initials[4], int choice);

	int getType();
	int getScore(int slot);
	char getInitial(int slot1, int slot2);

	bool initialsMatch(int y, char initials[4]);
	
	void save(int j);
	void saveScore(int j);
	void saveInitials(int j);
	void load();

	void drawSlots();

private:
	Point2D m_tablePosition;
	int m_type;
	int m_arraySize;
	Player* m_player;
};

