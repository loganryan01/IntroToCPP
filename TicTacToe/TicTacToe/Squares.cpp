#include "Squares.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

// This sets the square to empty so when the game starts the grid is empty
Squares::Squares() : m_type(EMPTY), m_gridPosition(Point2D{ 0, 0 })
{
}

Squares::~Squares()
{

}

// This function changes the position of the square 
// by acquiring a new position through the Point2D struct
void Squares::setPosition(Point2D position)
{
	// We need to set the squares to different positions 
	// so it looks like a grid rather than just one square
	m_gridPosition = position; 
}

// This function changes the type of square it is 
// by taking the integer of the type of square it is
void Squares::setType(int type)
{
	// The must require a type so the correct image can be drawn
	m_type = type;
}

// This function gets the type of square it is
// by returning the integer of the type of room it is
int Squares::getType()
{
	// This gets the type so the game can know what type of square it is
	// and do the correct action
	return m_type;
}

// This function draws the square depending on what type it is
void Squares::draw()
{
	// It draws the square by checking what type of square it is
	switch (m_type)
	{
	case EMPTY:
		// The players haven't chosen the square to place their token so it's empty
		cout << "[   ]"; 
		break;
	case KNOT:
		// Knot player has chosen this square to be a knot
		cout << "[ " << BLUE << "O" << RESET_COLOR << " ]"; 
		break;
	case CROSS:
		// Cross player has chosen this square to be cross
		cout << "[ " << RED << "X" << RESET_COLOR << " ]"; 
		break;
	}
}