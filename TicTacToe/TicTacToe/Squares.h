#pragma once
#include "Point2D.h"

class Squares
{
public:
	// Default Constructor
	Squares();

	// Destructor
	~Squares();

	// This function changes the position of the square
	void setPosition(Point2D position);

	// This function changes the type of square it is
	void setType(int type);

	// This function gets the type of square it is.
	int getType();

	// This function draws the square depending on what type it is
	void draw();

private:
	Point2D m_gridPosition; // This stores the position of the square
	int m_type; // This stores the number of what type of square it is
};

