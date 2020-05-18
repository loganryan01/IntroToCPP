#include "Game.h"
#include <iostream>
#include <windows.h>
#include <cctype>

Game::Game() : m_gameOver{ false }, m_score{ 0 }
{
    m_playerArray = 0;
    strncpy_s(m_initials, "\0", 4);
}

Game::~Game()
{

}

void Game::update()
{
    
    char input[4];

    drawCommandList();

    int choice = getChoice();

    hideCommandList();

    switch (choice)
    {
    case 1: // Add player info to table
        if (availableSpot())
        {
            updateInitials();
            updateScore();
            sort();
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
    case 2: // Change player initials
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
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
        std::cout << CSI << "40X";
        std::cout << INDENT << "Whose score do you want to change?" << std::endl;
        std::cout << INDENT << "Input old initials: " << YELLOW;
        std::cin >> input;
        std::cout << RESET_COLOR;
        if (correctInitials(input))
        {
            updateScore();
        }
        break;
    case 4: // Exit form database
        std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
        std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        std::cout << CSI << PLAYER_INPUT_Y + 10 << ";" << 0 << "H";
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

    m_table[0][0].loadInitials();
    m_table[0][1].loadScore();
    m_table[1][0].loadInitials();
    m_table[1][1].loadScore();
    m_table[2][0].loadInitials();
    m_table[2][1].loadScore();

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
                if (m_table[y][1].getScore(y) != NULL)
                {
                    m_table[y][1].setType(SCORE);
                }
                else
                {
                    m_table[y][1].setType(EMPTY);
                }
            }
            m_table[y][x].setPosition(Point2D{ x, y });
        }
    }
}

void Game::drawWelcomeMessage()
{
    std::cout << TITLE << MAGENTA << "Welcome to the player profile database!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "This database holds 10 high-scores and who owns those high-scores." << std::endl;
    std::cout << INDENT << "It can be used for any game you wish." << std::endl << std::endl;
}

void Game::drawTable()
{
    Point2D position = { 0, 0 };

    // reset draw colors
    std::cout << RESET_COLOR;
    std::cout << CSI << "9;70H" << CSI << "4m";;
    std::cout << "| Name | " << std::endl;
    std::cout << CSI << "9;79H";
    std::cout << "High-Score" << std::endl;
    std::cout << CSI << "24m";
    for (position.y = 0; position.y < DISPLAY_HEIGHT; position.y++)
    {
        for (position.x = 0; position.x < DISPLAY_WIDTH; position.x++)
        {
            m_table[position.y][position.x].drawSlots();
        }
        std::cout << std::endl;
    }
}

void Game::drawCommandList()
{
    std::cout << CSI << 9 << ";" << 1 << "H";
    std::cout << INDENT << "--------------Commands--------------" << std::endl;
    std::cout << INDENT << "1. Add new player" << std::endl;
    std::cout << INDENT << "2. Update player name" << std::endl;
    std::cout << INDENT << "3. Update player score" << std::endl;
    std::cout << INDENT << "4. Exit from database" << std::endl;
}

void Game::hideCommandList()
{
    for (int i = 9; i < 16; i++)
    {
        std::cout << CSI << i << ";" << 42 << "H";
        std::cout << CSI << "1K";
    }
}

// maximum score is a 9 digit number
void Game::updateScore()
{
    for (int i = 0; i < 2; i++)
    {
        std::cout << CSI << PLAYER_INPUT_Y + i << ";" << 0 << "H";
        std::cout << CSI << "40X";
    }
    
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
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
        m_table[m_playerArray][1].setType(SCORE);
        m_table[m_playerArray][1].setScore(m_score, m_playerArray);
        m_table[m_playerArray][1].saveScore(m_playerArray);
    }
}

void Game::updateInitials()
{
    std::cout << RESET_COLOR;
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";
    std::cout << INDENT << "Enter initials of your name: " << INDENT << YELLOW;

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
        m_table[m_playerArray][0].setType(INITIALS);
        m_table[m_playerArray][0].setInitials(m_initials, m_playerArray);
        m_table[m_playerArray][0].saveInitials(m_playerArray);
    }
}

int Game::getChoice()
{
    int input = 0;
    
    std::cout << CSI << COMMAND_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "40X";
    std::cout << INDENT << "What do you want to do?";
    std::cout << CSI << COMMAND_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;
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
        if (m_table[y][1].initialsMatch(y, input))
        {
            m_playerArray = y;
            return true;
        }
    }
    return false;
}

bool Game::availableSpot()
{
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        if (m_table[y][0].getType() == EMPTY)
        {
            m_playerArray = y;
            return true;
        }
    }
    return false;
}

void Game::sort()
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 0; i < DISPLAY_HEIGHT - 1; i++)
        {
            if ((int)m_table[i + 1][0].getInitial(i + 1, 0) < (int)m_table[i][0].getInitial(i, 0) &&
                m_table[i][1].getType() != EMPTY && m_table[i + 1][1].getType() != EMPTY)
            {
                int temp1 = m_table[i][1].getScore(i);
                int temp2 = m_table[i + 1][1].getScore(i + 1);
                char temp3[4] = { m_table[i][0].getInitial(i, 0),
                                  m_table[i][0].getInitial(i, 1),
                                  m_table[i][0].getInitial(i, 2) };
                char temp4[4] = { m_table[i + 1][0].getInitial(i + 1, 0),
                                  m_table[i + 1][0].getInitial(i + 1, 1),
                                  m_table[i + 1][0].getInitial(i + 1, 2) };
                m_table[i][1].setScore(temp2, i);
                m_table[i + 1][1].setScore(temp1, i + 1);
                m_table[i][0].setInitials(temp4, i);
                m_table[i + 1][0].setInitials(temp3, i + 1);
                sorted = false;
            }
        }
    }
}