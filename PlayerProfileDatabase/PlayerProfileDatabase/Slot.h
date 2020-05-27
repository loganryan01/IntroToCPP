#pragma once
#include "Structures.h"

class Slot
{
public:
	// Constructor
	Slot();

	// Destructor
	~Slot();

	// Changes the position of the slot.
	void setPosition(Point2D position);

	// Changes the type of information that the slot is holding.
	void setType(int type);

	// Changes the score of the player.
	void setScore(int score, int playerNumber);

	// Changes the initials of the player.
	void setInitials(char initials[4], int playerNumber);

	// Get the type of information that the slot is holding.
	int getType();

	// Get the score of the specified player. 
	int getScore(int playerNumber);

	// Get an initial of the specified player. 
	char getInitial(int playerNumber, int initialsPosition);

	// Search the dynamic array for the matching initials.
	int binarySearch(char initials[4], int arraySize);
	
	// Save the player score to binary file.
	void saveScore(int playerNumber, int binaryFilePosition);

	// Save the player name to binary file.
	void saveInitials(int playerNumber, int binaryFilePosition);

	// Load the player name from the binary file.
	void loadInitials(int playerNumber);

	// Load the player score from the binary file.
	void loadScore(int playerNumber);

	// Check the initials in the binary file.
	int checkBinaryInitials(char oldInitials[4]);

	// Draw the slots.
	void drawSlots();

private:
	// Where is this slot positioned ?
	Point2D m_tablePosition;
	
	// What type of information is in the slot?
	int m_type;

	// The dynamic array to store all the player information.
	Player* m_player;
};

