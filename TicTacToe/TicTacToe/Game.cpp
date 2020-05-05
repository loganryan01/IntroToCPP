#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

Game::Game() : player1Name{ }, player2Name{ }, m_gameOver{ false }
{
}

Game::~Game()
{
}

bool Game::startup()
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            m_grid[y][x].setType(0);
        }
    }

	return true;
}

bool Game::isGameOver()
{
	return m_gameOver;
}

void Game::drawWelcomeMessage()
{
	// Print title of game
	cout << INDENT << INDENT << MAGENTA << "Welcome to Tic-Tac-Toe" << RESET_COLOR << endl;

	// Print game description
	cout << INDENT << "Tic-Tac-Toe is a game for two players who take turns marking the spaces in a 3x3 grid." << endl;
	cout << INDENT << "The player wins the game by placing 3 of their marks diagonally, vertically or horizontally." << endl << endl;
}

void Game::setPlayerNames(char player1Name[50], char player2Name[50])
{
    // Set player 1 name
    cout << endl;
    cout << INDENT << "Player 1, What is your name? " << INDENT << YELLOW;
    cin >> player1Name;
    cout << RESET_COLOR << endl;

    if (cin.fail())
    {
        cout << INDENT << "You cannot use that name." << endl;
    }
    else
    {
        cout << INDENT << "Welcome " << player1Name << ", You will be 'O'." << endl;
        cout << INDENT << "Press 'Enter' to continue." << endl;
    }
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();

    // Set player 2 name
    cout << INDENT << "Player 2, What is your name? " << INDENT << YELLOW;
    cin >> player2Name;
    cout << RESET_COLOR << endl;

    if (cin.fail())
    {
        cout << INDENT << "You cannot use that name." << endl;
    }
    else
    {
        cout << INDENT << "Welcome " << player2Name << ", You will be 'X'." << endl;
        cout << INDENT << "Press 'Enter' to continue." << endl;
    }
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();

    // Print player names
    cout << INDENT << "So we have " << player1Name << " vs. " << player2Name << endl;
    cout << INDENT << "Let the game begin" << endl;

    cout << endl << INDENT << "Press 'Enter' to begin the game." << endl;
    cin.get();
}

void Game::drawGrid()
{
    Point2D position = { 0, 0 };

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        cout << INDENT;
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            m_grid[y][x].draw();
        }
        cout << endl;
    }
}

void Game::update()
{
    Point2D playerPos = m_player.getPosition();

    int command;
    cin >> command;

    switch (command)
    {
    case 1:
        if (m_grid[0][0].getType() == EMPTY)
        {
            m_grid[0][0].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 2:
        if (m_grid[0][1].getType() == 0)
        {
            m_grid[0][1].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 3:
        if (m_grid[0][2].getType() == 0)
        {
            m_grid[0][2].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 4:
        if (m_grid[1][0].getType() == 0)
        {
            m_grid[1][0].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 5:
        if (m_grid[1][1].getType() == 0)
        {
            m_grid[1][1].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 6:
        if (m_grid[1][2].getType() == 0)
        {
            m_grid[1][2].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 7:
        if (m_grid[2][0].getType() == 0)
        {
            m_grid[2][0].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 8:
        if (m_grid[2][1].getType() == 0)
        {
            m_grid[2][1].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    case 9:
        if (m_grid[2][2].getType() == 0)
        {
            m_grid[2][2].setType(KNOT);
        }
        else
        {
            cout << "This square is already filled! Please choose another!";
        }
        break;
    }
}

void Game::draw()
{
    Point2D playerPos = m_player.getPosition();
    system("cls");
    drawWelcomeMessage();
    drawGrid();
}