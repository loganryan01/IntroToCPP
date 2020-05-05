#include "Player.h"
#include "GameDefines.h"
#include "Squares.h"
#include <iostream>

using namespace std;

Player::Player() : m_gridPosition(Point2D{ 0, 0 })
{
}

Player::Player(int x, int y) : m_gridPosition(Point2D{ x, y })
{
}

Player::~Player()
{

}

void Player::setPosition(Point2D position)
{
	m_gridPosition = position;
}

Point2D Player::getPosition()
{
	return m_gridPosition;
}

void Player::executeCommand(int command)
{
    /*switch (command)
    {
    case 1:
        if (m_grid[ROW][COLUMN].getType() == 0)
        {
            m_grid[ROW][COLUMN].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
            drawKnots();
        } 
        break;
    case 2:
        ROW = 0; COLUMN = 1; break;
    case 3:
        ROW = 0; COLUMN = 2; break;
    case 4:
        ROW = 1; COLUMN = 0; break;
    case 5:
        ROW = 1; COLUMN = 1; break;
    case 6:
        ROW = 1; COLUMN = 2; break;
    case 7:
        ROW = 2; COLUMN = 0; break;
    case 8:
        ROW = 2; COLUMN = 1; break;
    case 9:
        ROW = 2; COLUMN = 2; break;
    }*/
}