#include "Squares.h"
#include "GameDefines.h"
#include <iostream>

using namespace std;

Squares::Squares()
{
	m_type = EMPTY;
	m_gridPosition.x = 0;
	m_gridPosition.y = 0;
}

Squares::~Squares()
{

}

void Squares::setPosition(Point2D position)
{
	m_gridPosition = position;
}

void Squares::setType(int type)
{
	m_type = type;
}

int Squares::getType()
{
	return m_type;
}

void Squares::draw()
{
	switch (m_type)
	{
	case EMPTY:
		cout << EMPTY_TILE;
		break;
	}
}