#include "Slot.h"
#include "GameDefines.h"
#include <iostream>

Slot::Slot() : m_type{ EMPTY }, m_arraySize{ 0 }, m_tablePosition{ 0, 0 }, m_player{ new Player[m_arraySize] }
{
}

Slot::~Slot()
{
    delete[] m_player;
}

void Slot::setPosition(Point2D position)
{
	m_tablePosition = position;
}

void Slot::setType(int type)
{
	m_type = type;
}

void Slot::setScore(int score, int position)
{
    m_arraySize = position;
    m_player[m_arraySize].score = score;
}

void Slot::setInitials(char initials[4], int position)
{
    m_arraySize = position;
    strncpy_s(m_player[m_arraySize].initials, initials, 4);
}

int Slot::getType()
{
	return m_type;
}

bool Slot::initialsMatch(int y, char initials[4])
{
    int correct = 0;
    
    for (int i = 0; i < 4; i++)
    {
        if (initials[i] == m_player[y].initials[i])
            correct++;
    }

    if (correct == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Slot::drawSlots(int y)
{
    // find the console output position
    int outX = INDENT_X + (7 * m_tablePosition.x) + 65;
    int outY = DISPLAY_Y + m_tablePosition.y;

    std::cout << CSI << outY << ";" << outX << "H";
    // draw the room
    switch (m_type)
    {
    case SCORE:
        std::cout << "| " << m_player[y].score;
        break;
    case INITIALS:
        std::cout << "| " << m_player[y].initials;
        break;
    }
}