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

int Slot::binarySearch(char initials[4])
{
    int l = 0;
    int r = 10 - 1;
    while (l <= r)
    {
        int m = ((l + r) / 2);
        if (m_player[m].initials[0] == initials[0] && m_player[m].initials[1] == initials[1] && m_player[m].initials[2] == initials[2])
        {
            return m;
        }

        if (m_player[m].initials[0] < initials[0] || m_player[m].initials[1] < initials[1] || m_player[m].initials[2] < initials[2])
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }
    }
    return -1;
}

void Slot::saveScore(int j)
{
    std::fstream file;
    file.open("data.out", std::ios::in | std::ios::binary | std::ios::out);
    if (file.is_open())
    {
        file.seekp(sizeof(Slot) * j + 8, std::ios::beg);
        file.write((char*)&m_player[j].score, sizeof(int));
        file.close();
    }
}

void Slot::saveInitials(int j)
{
    std::fstream file;
    file.open("data.out", std::ios::in | std::ios::binary | std::ios::out);
    if (file.is_open())
    {
        file.seekp(sizeof(Slot) * j, std::ios::beg);
        file.write((char*)&m_player[j].initials, sizeof(Player));
        file.close();
    }
}

void Slot::loadInitials(int j)
{
    std::fstream file;
    file.open("data.out", std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        Player tempPlayer;
        file.seekg(j * sizeof(Slot), std::ios::beg);
        file.read((char*)&tempPlayer, sizeof(Player));
        m_player[j].initials[0] = tempPlayer.initials[0];
        m_player[j].initials[1] = tempPlayer.initials[1];
        m_player[j].initials[2] = tempPlayer.initials[2];
        file.close();
    }
}

void Slot::loadScore(int j)
{
    std::fstream file;
    file.open("data.out", std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        int newScore;
        file.seekg(sizeof(Slot) * j + 8, std::ios::beg);
        file.read((char*)&newScore, sizeof(int));
        m_player[j].score = newScore;
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