#include "Slot.h"
#include "GameDefines.h"
#include <iostream>

Slot::Slot()
{
	m_type = EMPTY;
    m_tablePosition = { 0, 0 };
    m_player = { 0, "\0" };
}

Slot::~Slot()
{

}

void Slot::setPosition(Point2D position)
{
	m_tablePosition = position;
}

void Slot::setType(int type)
{
	m_type = type;
}

void Slot::setScore(int score)
{
    m_player.score = score;
}

void Slot::setInitials(char initials[4])
{
    strncpy_s(m_player.initials, initials, 4);
}

int Slot::getType()
{
	return m_type;
}

void Slot::drawSlots()
{
    // find the console output position
    int outX = INDENT_X + (12 * m_tablePosition.x) + 1;
    int outY = DISPLAY_Y + m_tablePosition.y;

    std::cout << CSI << outY << ";" << outX << "H";
    // draw the room
    switch (m_type)
    {
    case EMPTY:
        std::cout << "          |";
        break;
    case POSITION:
        if (m_tablePosition.y == 9)
        {
            std::cout << "   " << m_tablePosition.y + 1 << ".   |";
            break;
        }
        std::cout << "    " << m_tablePosition.y + 1 << ".   |";
        break;
    case SCORE:
        std::cout << m_player.score;
        break;
    case INITIALS:
        std::cout << m_player.initials;
        break;
    }
}