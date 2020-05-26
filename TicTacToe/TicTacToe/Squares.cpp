/*--------------------------------------
	File Name: Squares.cpp
	Purpose: Draws sqaure on the screen.
	Author: Logan Ryan
	Modified: 26 May 2020
----------------------------------------
	Copyright 2020 Logan Ryan.
--------------------------------------*/

#include "Squares.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

//--------------------------------------------------------------------- 
// Initialise the variables in the class.
//	 m_type (int): This stores the number of what type of square it is.
//   m_gridPosition (Point2D): This stores the position of the square.
//--------------------------------------------------------------------- 
Squares::Squares() : m_type(EMPTY), m_gridPosition(Point2D{ 0, 0 })
{
}

Squares::~Squares()
{

}

//-------------------------------------------------
// Changes the position of the square.
//   position (Point2D): Where is the square going?
//-------------------------------------------------
void Squares::setPosition(Point2D position)
{
	m_gridPosition = position; 
}

//-----------------------------------------------------
// Changes the type of symbol is in the square.
//   type (int): What type of square is it going to be?
//-----------------------------------------------------
void Squares::setType(int type)
{
	m_type = type;
}

//-------------------------------------------------------------
// Gets the type of symbol is in the square.
//   return (int): Returns the type of symbol is in the square.
//-------------------------------------------------------------
int Squares::getType()
{
	return m_type;
}

//-----------------------------------------------
// Draws the square depending on what type it is.
//-----------------------------------------------
void Squares::draw()
{
	// Check what type of information is in the square.
	switch (m_type)
	{
	case EMPTY:
		// If it's empty then draw an empty square.
		cout << "[   ]"; 
		break;
	case KNOT:
		// If the knot player chose this square to be a knot then draw a knot.
		cout << "[ " << BLUE << "O" << RESET_COLOR << " ]"; 
		break;
	case CROSS:
		// If the cross player chose this square to be a knot then draw a cross.
		cout << "[ " << RED << "X" << RESET_COLOR << " ]"; 
		break;
	}
}