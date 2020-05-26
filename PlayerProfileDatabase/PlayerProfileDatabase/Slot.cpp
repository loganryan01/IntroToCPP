/*-----------------------------------------------------------------------
    File Name: Slot.cpp
    Purpose: Draws the slots on the screen, saves the data to binary file
             and loads the data from the binary file.
    Author: Logan Ryan
    Modified: 25 May 2020
-------------------------------------------------------------------------
    Copyright 2020 Logan Ryan.
-----------------------------------------------------------------------*/

#include "Slot.h"
#include "GameDefines.h"
#include <iostream>
#include <fstream>

//----------------------------------------------------------------------
// Initialise all the variables in this class.
//   m_type: What type of information is in the slot?
//           The default is empty.
//   m_tablePosition: Where is this slot positioned?
//                    The default is 0, 0.
//   m_player: The dynamic array to store all the player information.
//             The array is created in each of the slots and can hold 10
//             players in it.
//----------------------------------------------------------------------
Slot::Slot() : m_type{ EMPTY }, m_tablePosition{ 0, 0 }, 
m_player{ new Player[10] }
{
}

//---------------------------------------------------------------
// Destroys the dynamic array when the class is no longer in use.
//---------------------------------------------------------------
Slot::~Slot()
{
    delete[] m_player;
}

//----------------------------------------------------
// Changes the position of the slot.
//   position (Point2D): The new position of the slot.
//----------------------------------------------------
void Slot::setPosition(Point2D position)
{
	m_tablePosition = position;
}

//--------------------------------------------------------------------
// Changes the type of information that the slot is holding.
//   type (int): The new type of information that the slot is holding.
//               Valid values are:
//               0 = Empty, 1 = Score, 2 = Initials
//--------------------------------------------------------------------
void Slot::setType(int type)
{
	m_type = type;
}

//------------------------------------------------------------
// Changes the score of the player.
//   score (int): The new score for the player.
//   playerNumber (int): Which player's score are we changing?
//                       Valid values are 0-9
//------------------------------------------------------------
void Slot::setScore(int score, int playerNumber)
{
    m_player[playerNumber].score = score;
}

//------------------------------------------------------------
// Changes the initials of the player.
//   initials (char[4]): The new name for the player.
//   playerNumber (int): Which player's score are we changing?
//                       Valid values are 0-9
//------------------------------------------------------------
void Slot::setInitials(char initials[4], int playerNumber)
{
    strncpy_s(m_player[playerNumber].initials, initials, 4);
}

//-----------------------------------------------------------------
// Get the type of information that the slot is holding.
//   return (int): Returns the type of information that the slot is
//                 holding.
//-----------------------------------------------------------------
int Slot::getType()
{
	return m_type;
}

//-----------------------------------------------------------
// Get the score of the specified player. 
//   playerNumber (int): Which player's score are we getting?
//                       Valid values are 0-9
//   return (int): Returns the score of the specified player.
//-----------------------------------------------------------
int Slot::getScore(int playerNumber)
{
    return m_player[playerNumber].score;
}

//--------------------------------------------------------------
// Get an initial of the specified player. 
//   playerNumber (int): Which player's score are we getting?
//                       Valid values are 0-9
//   initialsPosition (int): Which initial are we getting?
//   return (char): Returns the initial of the specified player.
//--------------------------------------------------------------
char Slot::getInitial(int playerNumber, int initialsPosition)
{
    return m_player[playerNumber].initials[initialsPosition];
}

//-------------------------------------------------------------------
// Search the dynamic array for the matching initials.
//   initials (char[4]): The name of the player we are searching for.
//   return (int): Returns the position of the initials in the array.
//-------------------------------------------------------------------
int Slot::binarySearch(char initials[4], int arraySize)
{
    int startIndex = 0;
    int endIndex = arraySize;

    // Loop while startIndex is less or equal to endIndex.
    while (startIndex <= endIndex)
    {
        int middleIndex = ((startIndex + endIndex) / 2);

        // Check if we've found the right number already here, and return
        // the middle index if we have.
        if (m_player[middleIndex].initials[0] == initials[0] && 
            m_player[middleIndex].initials[1] == initials[1] && 
            m_player[middleIndex].initials[2] == initials[2])
        {
            return middleIndex;
        }

        // If we haven't found the right number, we compare the ASCII
        // values of the characters of the initials and change the
        // start and end indexes to shrink our search range for the next
        // iteration.
        if (initials[0] < m_player[middleIndex].initials[0] ||
            initials[1] < m_player[middleIndex].initials[1] ||
            initials[2] < m_player[middleIndex].initials[2])
        {
            endIndex = middleIndex - 1;
        }
        else
        {
            startIndex = middleIndex + 1;
        }
    }

    // If we get here we haven't found the correct name and we return -1
    // to indicate failure.
    return -1;
}

//--------------------------------------------------------------
// Save the player score to binary file.
//   playerNumber (int): Whose score are we saving?
//   binaryFilePosition (int): Where are we saving the initials?
//   Valid values for bothe parameters is 0-9
//--------------------------------------------------------------
void Slot::saveScore(int playerNumber, int binaryFilePosition)
{
    std::fstream file;

    // Open the file ready to write.
    file.open("information.out", std::ios::in | std::ios::binary | std::ios::out);
    
    // Check that the file is open.
    if (file.is_open())
    {
        // Move the write marker to the correct byte in the file by
        // starting from the beginning of the file then multiplying 
        // the size of the Slot class by the binaryFilePosition and add 8.
        file.seekp(sizeof(Slot) * binaryFilePosition + 8, std::ios::beg);

        // Write the players score.
        file.write((char*)&m_player[playerNumber].score, sizeof(int));

        // Close the file when the operation is done.
        file.close();
    }
}

//--------------------------------------------------------------
// Save the player name to binary file.
//   playerNumber (int): Whose initials are we saving?
//   binaryFilePosition (int): Where are we saving the initials?
//   Valid values for bothe parameters is 0-9
//--------------------------------------------------------------
void Slot::saveInitials(int playerNumber, int binaryFilePosition)
{
    std::fstream file;

    // Open the file ready to write.
    file.open("information.out", std::ios::in | std::ios::binary | std::ios::out);
    
    // Check that the file is open.
    if (file.is_open())
    {
        // Move the write marker to the correct byte in the file by
        // starting from the beginning of the file then multiplying 
        // the size of the Slot class by the binaryFilePosition.
        file.seekp(sizeof(Slot) * binaryFilePosition, std::ios::beg);

        // Write the players name.
        file.write((char*)&m_player[playerNumber].initials, sizeof(Player));
        
        // Close the file when the operation is done.
        file.close();
    }
}

//----------------------------------------------------------------
// Load the player name from the binary file.
//   playerNumber (int): Where is the initials going in the array?
//   Valid values is 0-9
//----------------------------------------------------------------
void Slot::loadInitials(int playerNumber)
{
    std::fstream file;

    // Open the file ready to read.
    file.open("information.out", std::ios::in | std::ios::binary);

    // Check that the file is open.
    if (file.is_open())
    {
        Player tempPlayer;

        // Move the read marker to the correct byte in the file by
        // starting from the beginning of the file then multiplying 
        // the size of the Slot class by the playerNumber.
        file.seekg(playerNumber * sizeof(Slot), std::ios::beg);

        // Read the player name
        file.read((char*)&tempPlayer, sizeof(Player));

        // Set the player name to the correct position
        m_player[playerNumber].initials[0] = tempPlayer.initials[0];
        m_player[playerNumber].initials[1] = tempPlayer.initials[1];
        m_player[playerNumber].initials[2] = tempPlayer.initials[2];

        // Close the file when the operation is done.
        file.close();
    }
}

//-------------------------------------------------------------
// Load the player score from the binary file.
//   playerNumber (int): Where is the score going in the array?
//   Valid values is 0-9
//-------------------------------------------------------------
void Slot::loadScore(int playerNumber)
{
    std::fstream file;

    // Open the file ready to read.
    file.open("information.out", std::ios::in | std::ios::binary);

    // Check that the file is open.
    if (file.is_open())
    {
        int newScore;

        // Move the read marker to the correct byte in the file by
        // starting from the beginning of the file then multiplying 
        // the size of the Slot class by the playerNumber and add 8.
        file.seekg(sizeof(Slot) * playerNumber + 8, std::ios::beg);

        // Read the player score
        file.read((char*)&newScore, sizeof(int));

        // Set the player score to the correct position
        m_player[playerNumber].score = newScore;

        // Close the file when the operation is done.
        file.close();
    }
}

//------------------------------------------------------------------------
// Check the initials in the binary file.
//   oldInitals (char[4]): The name that the program is looking for in the
//                         binary file.
//   return (bool): Return if the name is found or not.
//------------------------------------------------------------------------
int Slot::checkBinaryInitials(char oldInitials[4])
{
    std::fstream file;

    // Open the file ready to read.
    file.open("information.out", std::ios::in | std::ios::binary);

    // Check that the file is open.
    if (file.is_open())
    {
        Player tempPlayer;

        // Read through the whole file
        for (int y = 0; y < 9; y++)
        {
            // Move the read marker to the correct byte in the file by
            // starting from the beginning of the file then multiplying 
            // the size of the Slot class by the playerNumber.
            file.seekg(y * sizeof(Slot), std::ios::beg);

            // Read the player name
            file.read((char*)&tempPlayer, sizeof(Player));

            // If the old name match any of the names in the binary file
            // write over it.
            if (tempPlayer.initials[0] == oldInitials[0] &&
                tempPlayer.initials[1] == oldInitials[1] &&
                tempPlayer.initials[2] == oldInitials[2])
            {
                // Close the file and tell the user that there is a name in
                // the file.
                file.close();
                return y;
            }
        }

        // Close the file when the operation is done and tell the user that
        // the name does not exist.
        file.close();
    }
    return -1;
}

//----------------
// Draw the slots.
//----------------
void Slot::drawSlots()
{
    // Find the console output position.
    // To find the x position, first move the cursor 70 bytes in, then
    // add the slot x position multiply by 7.
    int outX = INDENT_X + (7 * m_tablePosition.x);

    // To find the y position, first move the cursor 10 bytes down, then
    // add the slot y position.
    int outY = DISPLAY_Y + m_tablePosition.y;

    // Move the cursor to the correct position.
    std::cout << CSI << outY << ";" << outX << "H";
    
    // Draw the slot depending on what type it is.
    switch (m_type)
    {
    case EMPTY:
        std::cout << "|";
        break;
    case SCORE:
        std::cout << "| " << m_player[m_tablePosition.y].score << "         ";
        break;
    case INITIALS:
        std::cout << "| " << m_player[m_tablePosition.y].initials << "         ";
        break;
    }
}