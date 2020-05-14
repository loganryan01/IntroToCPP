#include "Game.h"
#include <iostream>
#include <windows.h>
#include <cctype>

Game::Game() : m_gameOver{ false }, m_score{ 0 }
{
    strncpy_s(m_initials, "\0", 4);
}

Game::~Game()
{

}

void Game::update()
{
    int choice = getChoice();

    switch (choice)
    {
    case 1: // Add player info to table
        updateInitials();
        updateScore();
        break;
    case 2: // Change player initials
        char input[4];
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
        std::cout << CSI << "40X";
        std::cout << INDENT << "Input old initials: " << YELLOW;
        std::cin >> input;
        std::cout << RESET_COLOR;
        if (correctInitials(input))
        {
            updateInitials();
        }
        break;
    case 3: // Change player score
        updateScore();
        break;
    case 4: // Exit form database
        exit(0);
        break;
    }
}

void Game::draw()
{
    drawTable();
}

bool Game::startup()
{
    if (enableVirtualTerminal() == false)
    {
        std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
        std::cout << "Press 'Enter' to exit." << std::endl;
        std::cin.get();
        return false;
    }

    initializeTable();

    drawWelcomeMessage();

    return true;
}

bool Game::isGameOver()
{
    return m_gameOver;
}

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

void Game::initializeTable()
{
    // fill the arrays with 0
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            if (x == 0)
            {
                m_table[y][0].setType(EMPTY);
            }
            if (x == 1)
            {
                m_table[y][1].setType(EMPTY);
            }
            m_table[y][x].setPosition(Point2D{ x, y });
        }
    }
}

void Game::drawWelcomeMessage()
{
    std::cout << TITLE << MAGENTA << "Welcome to the player profile database!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "This database holds high-scores and who owns those high-scores." << std::endl;
    std::cout << INDENT << "It can be used for any game you wish." << std::endl << std::endl;
}

void Game::drawTable()
{
    Point2D position = { 0, 0 };

    // reset draw colors
    std::cout << RESET_COLOR;
    std::cout << CSI << "9;70H";
    std::cout << "| Name |" << std::endl;
    std::cout << CSI << "9;79H";
    std::cout << "High-Score |" << std::endl;
    for (position.y = 0; position.y < DISPLAY_HEIGHT; position.y++)
    {
        for (position.x = 0; position.x < DISPLAY_WIDTH; position.x++)
        {
            m_table[position.y][position.x].drawSlots(position.y);
        }
        std::cout << std::endl;
    }
}

void Game::updateScore()
{
    int position = 0;
    
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";
    std::cout << INDENT << "Enter High-Score: " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";
    std::cin >> m_score;
    if (!std::cin.good())
    {
        std::cout << RESET_COLOR;
        std::cout << INDENT << "You have inputed an invalid score.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        return;
    }
    else
    {
        m_table[position][1].setType(SCORE);
        m_table[position][1].setScore(m_score, position);
        position++;
    }
}

void Game::updateInitials()
{
    int position = 0;

    std::cout << RESET_COLOR;
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";
    std::cout << INDENT << "Enter initials of your name: " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";
    std::cin >> m_initials;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail() || !isalpha(m_initials[0]) || !isalpha(m_initials[1]) || !isalpha(m_initials[2]))
    {
        std::cout << INDENT << "You have inputed an invalid letter(s).";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
    else
    {
        m_table[position][0].setType(INITIALS);
        m_table[position][0].setInitials(m_initials, position);
        position++;
    }
}

int Game::getChoice()
{
    int input = 0;
    
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";
    std::cout << INDENT << "What do you want to do?";
    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> input;
    std::cout << RESET_COLOR;

    return input;
}

bool Game::correctInitials(char input[4])
{
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        if (m_table[y][0].initialsMatch(y, input)  == EMPTY)
        {
            return true;
        }
    }
    return false;
}