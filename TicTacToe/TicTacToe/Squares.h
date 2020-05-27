#pragma once
#include "Point2D.h"

class Squares
{
public:
	// Constructor
	Squares();

	// Destructor
	~Squares();

	// Changes the position of the square.
	void setPosition(Point2D position);

	// Changes the type of symbol is in the square.
	void setType(int type);

	// Gets the type of symbol is in the square.
	int getType();

	// Draws the square depending on what type it is.
	void draw();

private:
	// This stores the position of the square.
	Point2D m_gridPosition; 

	// This stores the number of what type of square it is.
	int m_type; 
};