#include "Slot.h"
#include "GameDefines.h"
#include <iostream>
#include <fstream>

Slot::Slot() : m_type{ EMPTY }, m_arraySize{ 0 }, m_tablePosition{ 0, 0 }, m_player{ new Player[10] }
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
    m_player[position].score = score;
}

void Slot::setInitials(char initials[4], int position)
{
    strncpy_s(m_player[position].initials, initials, 4);
}

int Slot::getType()
{
	return m_type;
}

int Slot::getScore(int slot)
{
    return m_player[slot].score;
}

char Slot::getInitial(int slot1, int slot2)
{
    return m_player[slot1].initials[slot2];
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

void Slot::save(int j)
{
    std::fstream file;
    file.open("data.dat", std::ios::out | std::ios::binary);
    if (file.is_open())
    {
        file.seekp(8 * j, std::ios::beg);
        file.write((char*)&m_player[j], sizeof(Player));
        file.close();
    }
}

void Slot::saveScore(int j)
{
    std::fstream file;
    file.open("data.dat", std::ios::out | std::ios::binary);
    if (file.is_open())
    {
        file.seekp(8 * j, std::ios::beg);
        file.write((char*)&m_player[j].score, sizeof(Player));
        file.close();
    }
}

void Slot::saveInitials(int j)
{
    std::fstream file;
    file.open("data.dat", std::ios::out | std::ios::binary);
    if (file.is_open())
    {
        file.seekp((8 * j) + 4, std::ios::beg);
        file.write((char*)&m_player[j].score, sizeof(Player));
        file.close();
    }
}

void Slot::load()
{
    std::fstream file;
    file.open("data.dat", std::ios::out | std::ios::binary);
    if (file.is_open())
    {
        for (int i = 0; i < 10; i++)
        {
            Player tempPlayer;
            file.read((char*)&tempPlayer, sizeof(Player));
            m_player[i].initials[0] = tempPlayer.initials[0];
            m_player[i].initials[1] = tempPlayer.initials[1];
            m_player[i].initials[2] = tempPlayer.initials[2];
            m_player[i].score = tempPlayer.score;
        }
        file.close();
    }
}

void Slot::drawSlots()
{
    // find the console output position
    int outX = INDENT_X + (7 * m_tablePosition.x) + 65;
    int outY = DISPLAY_Y + m_tablePosition.y;

    std::cout << CSI << outY << ";" << outX << "H";
    // draw the room
    switch (m_type)
    {
    case EMPTY:
        std::cout << "|";
        break;
    case SCORE:
        std::cout << "| " << m_player[m_tablePosition.y].score;
        break;
    case INITIALS:
        std::cout << "| " << m_player[m_tablePosition.y].initials;
        break;
    }

}