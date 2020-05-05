#include "Player.h"
#include "GameDefines.h"
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

void Player::draw()
{
	cout << PLAYER_TILE;
}

bool Player::executeCommand(int command)
{
    switch (command)
    {
    case KEY_RIGHT:
        if (m_gridPosition.x < GRID_WIDTH - 1)
            m_gridPosition.x++;
        return true;
    case KEY_LEFT:
        if (m_gridPosition.x > 0)
            m_gridPosition.x--;
        return true;
    case KEY_UP:
        if (m_gridPosition.y > 0)
            m_gridPosition.y--;
        return true;
    case KEY_DOWN:
        if (m_gridPosition.y < GRID_HEIGHT - 1)
            m_gridPosition.y++;
        return true;
    }
    return false;
}