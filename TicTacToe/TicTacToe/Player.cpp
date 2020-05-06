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