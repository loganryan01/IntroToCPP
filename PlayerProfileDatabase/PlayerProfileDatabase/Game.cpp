/*-----------------------------------------------------------------------
    File Name: Game.cpp
    Purpose: Runs the game.
    Author: Logan Ryan
    Modified: 25 May 2020
-------------------------------------------------------------------------
    Copyright 2020 Logan Ryan.
-----------------------------------------------------------------------*/

#include "Game.h"
#include <iostream>
#include <windows.h>
#include <cctype>
#include <fstream>

//---------------------------------------------------------------
// Initialise all the variables in this class.
//   m_gameOver: Is the game over?
//               The default is false.
//   m_score: The new score for the player.
//            The default is 0.
//   m_playerNumber: Which player are we adding or updating?
//                   Values can range from 0-9. The default is 0.
//   m_initials: The new name for the player.
//---------------------------------------------------------------
Game::Game() : m_gameOver{ false }, m_score{ 0 }
{
    m_playerNumber = 0;
    strncpy_s(m_initials, "\0", 4);
}

Game::~Game()
{

}

//--------------------------
// Update the game overtime.
//--------------------------
void Game::update()
{
    char inputOldInitials[4];
    
    // Show the player the possible commands.
    drawCommandList();

    // get the choice form the player.
    int choice = getChoice();

    // Hide the command list.
    hideCommandList();

    switch (choice)
    {
    case 1: // Add player info to table
        // Check that there is a space in the table first.
        if (availableRow())
        {
            // Get the new initials.
            updateInitials();

            // Save the initials to binary file.
            m_table[m_playerNumber][0].saveInitials(m_playerNumber, m_playerNumber);
            
            // Get the new initials.
            updateScore();

            // Save the score to binary file.
            m_table[m_playerNumber][1].saveScore(m_playerNumber, m_playerNumber);
        }
        else
        {
            std::cout << INDENT << "There is no room available on the table at the moment." << std::endl;
            std::cout << std::endl << INDENT << "Press 'Enter' to continue.";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get();
        }
        
        break;
    case 2: // Change player name
        // Move to correct position.
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

        // Get the old initials from the player.
        std::cout << INDENT << "Input old initials: " << YELLOW;
        std::cin >> inputOldInitials;
        std::cout << RESET_COLOR;

        // Check if the initials exist in the table.
        if (correctInitials(inputOldInitials))
        {
            // Get the old initials position in the binary file.
            int binaryFilePosition = m_table[m_playerNumber][0].checkBinaryInitials(inputOldInitials);
            
            // Get the new initials.
            updateInitials();
            
            // If the name does exist in the binary file.
            if (binaryFilePosition > -1)
            {
                // Place the new initials in the old initals position in the
                // binary file.
                m_table[m_playerNumber][0].saveInitials(m_playerNumber, binaryFilePosition);
            }
            else
            {
                // Tell the player that the name didn't save due to the
                // name not existing in the binary file.
                std::cout << INDENT << "Unable to save." << std::endl;
                std::cout << INDENT << "Press 'Enter' to continue.";

                // Return to the top of the loop and try again.
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin.get();
            }
        }
        else
        {
            std::cout << INDENT << "That name does not exist" << std::endl;
            std::cout << INDENT << "Press 'Enter' to continue.";
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get();
        }
        break;
    case 3: // Change player score.
        // Move cursor to the correct position.
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

        // Get the old initials from the player.
        std::cout << INDENT << "Whose score do you want to change?" << std::endl;
        std::cout << INDENT << "Input old initials: " << YELLOW;
        std::cin >> inputOldInitials;
        std::cout << RESET_COLOR;

        // Check if the initials exist in the table.
        if (correctInitials(inputOldInitials))
        {
            // Get the old score position in the binary file by getting
            // the old initials position.
            int binaryFilePosition = m_table[m_playerNumber][0].checkBinaryInitials(inputOldInitials);
            
            // Get the new score.
            updateScore();
            
            // If the name does exist in the binary file.
            if (binaryFilePosition > -1)
            {
                // Place the new score in the old score position in the
                // binary file.
                m_table[m_playerNumber][1].saveScore(m_playerNumber, binaryFilePosition);
            }
            else
            {
                // Tell the player that the score didn't save due to the
                // name not existing in the binary file.
                std::cout << INDENT << "Unable to save." << std::endl;
                std::cout << INDENT << "Press 'Enter' to continue.";
                
                // Return to the top of the loop and try again.
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin.get();
            }
        }
        else
        {
            // Tell the player that the name doesn't exist.
            std::cout << INDENT << "That name does not exist" << std::endl;
            std::cout << INDENT << "Press 'Enter' to continue.";
            
            // Return to the top of the loop and try again.
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get();
        }
        break;
    case 4: // Search database
        // Move the cursor to the correct position.
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
        
        // Get the old initials from the player.
        std::cout << INDENT << "Who are you looking for?" << std::endl;
        std::cout << INDENT << "Input initials: " << YELLOW;
        std::cin >> inputOldInitials;
        std::cout << RESET_COLOR;

        // Check if the name exists in the table.
        if (correctInitials(inputOldInitials))
        {
            // Tell the player that the name does exist.
            std::cout << INDENT << "That name exist" << std::endl;
            std::cout << INDENT << "Press 'Enter' to continue.";
            
            // Return to the top of the loop and try again.
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get();
        }
        else
        {
            // Tell the player that the name doesn't exist.
            std::cout << INDENT << "That name does not exist" << std::endl;
            std::cout << INDENT << "Press 'Enter' to continue.";

            // Return to the top of the loop and try again.
            std::cin.clear();
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            std::cin.get();
        }
        break;
    case 5: // Exit from database
        // Move cursor to the correct position.
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

        // Display instructions to how to exit from the program.
        std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();

        // Move the exit message to the correct position.
        std::cout << CSI << PLAYER_INPUT_Y + 10 << ";" << 0 << "H";
        exit(0);
        break;
    default: // Incorrect number or an invalid position.
        // Move cursor to the correct position.
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

        // Tell the player that there decision is invalid.
        std::cout << INDENT << "Invalid Choice" << std::endl;
        std::cout << INDENT << "Press 'Enter' to continue.";

        // Return to the top of the loop and try again.
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

//---------------
// Draw the game.
//---------------
void Game::draw()
{
    sort();
    drawTable();
}

//-----------------------------------------------------
// Set up the game when it begins.
//   return (bool): Return whether it succeeded or not.
//-----------------------------------------------------
bool Game::startup()
{
    if (enableVirtualTerminal() == false)
    {
        std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
        std::cout << "Press 'Enter' to exit." << std::endl;
        std::cin.get();
        return false;
    }

    load();

    initializeTable();

    drawWelcomeMessage();

    return true;
}

//-------------------------------------------------
// Check if the game is over.
//   return (bool): Return the game is over or not.
//-------------------------------------------------
bool Game::isGameOver()
{
    return m_gameOver;
}

//-------------------------------------------------
// Check if virtual terminal is set up.
//   return (bool): Return the game is over or not.
//-------------------------------------------------
bool Game::enableVirtualTerminal()
{
    //Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}

//-------------------------------------------------
// Setup the table to display player information.
//-------------------------------------------------
void Game::initializeTable()
{
    // Go through the 2D array
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            if (x == 0)
            {
                // Check if there is a name in the slot
                if (m_table[y][0].getInitial(y, 0) != NULL)
                {
                    m_table[y][0].setType(INITIALS);
                }
                else
                {
                    m_table[y][0].setType(EMPTY);
                }
            }
            if (x == 1)
            {
                // Check if there is a score in the slot
                if (m_table[y][1].getScore(y) < NULL)
                {
                    m_table[y][1].setType(EMPTY);
                }
                else
                {
                    m_table[y][1].setType(SCORE);
                }
            }
            // Move the slot to the correct position
            m_table[y][x].setPosition(Point2D{ x, y });
        }
    }
}

//--------------------------------------------------
// Load the player information from the binary file.
//--------------------------------------------------
void Game::load()
{
    std::fstream file;

    // Check if the file exists.
    file.open("information.out");
    if (file.is_open())
    {
        file.close();
        // If it does exists load the information from it.
        for (int y = 0; y < DISPLAY_HEIGHT; y++)
        {
            m_table[y][0].loadInitials(y);
            m_table[y][1].loadScore(y);
        }
    }
    else
    {
        file.close();
        file.open("information.out", std::ios::out | std::ios::binary);
        file.close();
        // If it doesn't exists create the file.
        for (int y = 0; y < DISPLAY_HEIGHT; y++)
        {
            m_table[y][0].saveInitials(y, y);
            m_table[y][1].saveScore(y, y);
        }
    }
    
}

//----------------------------------
// Welcome the user to the database.
//----------------------------------
void Game::drawWelcomeMessage()
{
    std::cout << TITLE << MAGENTA << "Welcome to the player profile database!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "This database holds 10 high-scores and who owns those high-scores." << std::endl;
    std::cout << INDENT << "It can be used for any game you wish." << std::endl << std::endl;
}

//-----------------------------------
// Draw the player information table.
//-----------------------------------
void Game::drawTable()
{
    Point2D position = { 0, 0 };

    // Reset draw colors
    std::cout << RESET_COLOR;

    // Move the cursor to the correct positions and draw the titles.
    std::cout << CSI << "9;70H" << CSI << "4m";
    std::cout << GREEN << "|" << RED << " Name " << GREEN << "|" << std::endl;
    std::cout << CSI << "9;78H";
    std::cout << BLUE << " High-Score" << std::endl;
    std::cout << CSI << "24m" << RESET_COLOR;

    // Go through all the slots and draw the information that is meant to
    // be in those slots.
    for (position.y = 0; position.y < DISPLAY_HEIGHT; position.y++)
    {
        for (position.x = 0; position.x < DISPLAY_WIDTH; position.x++)
        {
            m_table[position.y][position.x].drawSlots();
        }
        std::cout << std::endl;
    }
}

//---------------------------------------------------------------------------
// Draw the command list for the user to know what the possible commands are.
//---------------------------------------------------------------------------
void Game::drawCommandList()
{
    std::cout << CSI << 9 << ";" << 1 << "H";
    std::cout << INDENT << "--------------Commands----------------" << std::endl;
    std::cout << INDENT << "1 = Add new player                     " << std::endl;
    std::cout << INDENT << "2 = Update player name                 " << std::endl;
    std::cout << INDENT << "3 = Update player score                " << std::endl;
    std::cout << INDENT << "4 = Search player                      " << std::endl;
    std::cout << INDENT << "5 = Exit from database                 " << std::endl;
}

//-----------------------
// Hide the command list.
//-----------------------
void Game::hideCommandList()
{
    // Starting from line 9 clear all the writing on the screen
    for (int i = 9; i < 16; i++)
    {
        std::cout << CSI << i << ";" << 43 << "H";
        std::cout << CSI << "1K";
    }
}

//---------------------------------
// Update the score for the player.
//---------------------------------
void Game::updateScore()
{
    // Clear the player input area.
    for (int i = 0; i < 2; i++)
    {
        std::cout << CSI << PLAYER_INPUT_Y + i << ";" << 0 << "H";
        std::cout << CSI << "40X";
    }
    
    // Get the high-score from the user.
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << INDENT << "Enter High-Score: " << INDENT << std::endl;
    std::cout << INDENT << "Maximum 9 digit number." << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";
    std::cin >> m_score;
    if (!std::cin.good() || m_score > 999999999)
    {
        // If the score is invalid, tell the user to try again.
        std::cout << RESET_COLOR;
        std::cout << INDENT << "You have inputed an invalid score." << std::endl;
        std::cout << INDENT << "Press 'Enter' to return to the main menu." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        return;
    }
    else
    {
        // Set the high score for the player.
        m_table[m_playerNumber][1].setType(SCORE);
        m_table[m_playerNumber][1].setScore(m_score, m_playerNumber);
    }
}

//---------------------------------
// Update the name for the player.
//---------------------------------
void Game::updateInitials()
{
    // Clear the player input area.
    std::cout << RESET_COLOR;
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";

    // Get the name from the user.
    std::cout << INDENT << "Enter initials of your name: " << INDENT << std::endl;
    std::cout << INDENT << "Maximum 3 letters." << YELLOW;

    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";
    std::cin >> m_initials;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail() || !isalpha(m_initials[0]) || !isalpha(m_initials[1]) || !isalpha(m_initials[2]))
    {
        // If the name is invalid, tell the user to try again.
        std::cout << INDENT << "You have inputed an invalid letter(s).";
        std::cout << INDENT << "Press 'Enter' to return to the main menu." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
    else
    {
        // Set the name for the player.
        m_table[m_playerNumber][0].setType(INITIALS);
        m_table[m_playerNumber][0].setInitials(m_initials, m_playerNumber);
    }
}

//---------------------------------------------------------------------
// Get the choice of what command the user wants to do.
//   Return (int): Return the command number that the user wants to do.
//---------------------------------------------------------------------
int Game::getChoice()
{
    int choice = 0;
    
    // Ask the user what they want to do.
    std::cout << CSI << COMMAND_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";
    std::cout << INDENT << "What do you want to do?";

    // Get the choice from the user.
    std::cout << CSI << COMMAND_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> choice;
    std::cout << RESET_COLOR;

    // Return that choice
    return choice;
}

//-----------------------------------------------------------------------
// Check that the initials are correct.
//   inputOldInitials (char[4]): What were the old initials of the player 
//                               name?
//   Return (bool): Return whether the initials are correct or not.
//-----------------------------------------------------------------------
bool Game::correctInitials(char input[4])
{
    // Go through each of the name slots
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        // If the name is correct, set player number value to correct row
        // number value.
        if (m_table[y][0].binarySearch(input, y) > -1)
        {
            m_playerNumber = y;
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------
// Check that there is an available row on the player information table.
//   Return (bool): Return whether there is an available spot or not.
//----------------------------------------------------------------------
bool Game::availableRow()
{
    // Go through each of the name slots
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        // If there is no name in that slot, then there is no score to go 
        // with it therefore the row is empty
        if (m_table[y][0].getType() == EMPTY)
        {
            m_playerNumber = y;
            return true;
        }
    }
    return false;
}

//---------------------------------------------------
// Sorts the player information table alphabetically.
//---------------------------------------------------
void Game::sort()
{
    bool sorted = false;

    while (!sorted)
    {
        // At first we assume that the table is sorted.
        sorted = true;

        // Then we go through the name column.
        for (int i = 0; i < DISPLAY_HEIGHT - 1; i++)
        {
            // If the ASCII value of the first initial of the currently 
            // selected name is less than the ASCII value of the first 
            // initial of the next name then the names will swap along
            // with their respected score.
            if ((int)m_table[i + 1][0].getInitial(i + 1, 0) < (int)m_table[i][0].getInitial(i, 0) &&
                m_table[i][1].getType() != EMPTY && m_table[i + 1][1].getType() != EMPTY)
            {
                // Score of the currently selected player.
                int temp1 = m_table[i][1].getScore(i);

                // Score of the next player.
                int temp2 = m_table[i + 1][1].getScore(i + 1);

                // Name of the currently selected player.
                char temp3[4] = { m_table[i][0].getInitial(i, 0),
                                  m_table[i][0].getInitial(i, 1),
                                  m_table[i][0].getInitial(i, 2) };

                // Name of the next player.
                char temp4[4] = { m_table[i + 1][0].getInitial(i + 1, 0),
                                  m_table[i + 1][0].getInitial(i + 1, 1),
                                  m_table[i + 1][0].getInitial(i + 1, 2) };

                // Swap scores
                m_table[i][1].setScore(temp2, i);
                m_table[i + 1][1].setScore(temp1, i + 1);

                // Swap names
                m_table[i][0].setInitials(temp4, i);
                m_table[i + 1][0].setInitials(temp3, i + 1);

                // The table is not yet sorted and we must repeat the process.
                sorted = false;
            }
        }
    }
}