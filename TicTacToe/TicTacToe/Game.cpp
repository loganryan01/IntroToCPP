#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

Game::Game() : m_gameOver{ false }, m_player1Turn{ true }, m_player2Turn{ false }
{
}

Game::~Game()
{
}

bool Game::startup()
{
    initializeGrid();

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

void Game::initializeGrid()
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            m_grid[y][x].setPosition(Point2D{ x, y });
        }
    }
}

void Game::drawGrid()
{
    Point2D position = { 0, 0 };

    cout << INDENT << "    1" << "    2" << "    3" << endl;
    for (position.y = 1; position.y < GRID_HEIGHT; position.y++)
    {
        cout << INDENT;
        cout << position.y << " ";
        for (position.x = 1; position.x < GRID_WIDTH; position.x++)
        {
            m_grid[position.y][position.x].draw();
        }
        cout << endl;
    }
}

void Game::getCommand()
{
    int command;

    cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

    cout << INDENT << "Insert the number row and column you want to place your token:";

    cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";

    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());

    cin >> command;
    switch (command)
    {
    case 11:
        if (m_grid[1][1].getType() == EMPTY)
        {
            if (m_player1Turn)
            {
                m_grid[1][1].setType(KNOT);
                m_player1Turn = false;
                m_player2Turn = true;
            }
            else if (m_player2Turn)
            {
                m_grid[1][1].setType(CROSS);
                m_player2Turn = false;
                m_player1Turn = true;
            }
            draw();
            cout << CSI << 10 << ";" << 0 << "H";
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 12:
        if (m_grid[1][2].getType() == EMPTY)
        {
            if (m_player1Turn)
            {
                m_grid[1][2].setType(KNOT);
            }
            else if (m_player2Turn)
            {
                m_grid[1][2].setType(CROSS);
            };
            draw();
            cout << CSI << 10 << ";" << 0 << "H";
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 13:
        if (m_grid[1][3].getType() == EMPTY)
        {
            m_grid[1][3].setType(KNOT);
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 21:
        if (m_grid[2][1].getType() == EMPTY)
        {
            m_grid[2][1].setType(KNOT);
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 22:
        if (m_grid[2][2].getType() == EMPTY)
        {
            m_grid[2][2].setType(KNOT);
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 23:
        if (m_grid[2][3].getType() == EMPTY)
        {
            m_grid[2][3].setType(KNOT);
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 31:
        if (m_grid[3][1].getType() == EMPTY)
        {
            m_grid[3][1].setType(KNOT);
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 32:
        if (m_grid[3][2].getType() == EMPTY)
        {
            m_grid[3][2].setType(KNOT);
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    case 33:
        if (m_grid[3][3].getType() == EMPTY)
        {
            m_grid[3][3].setType(KNOT);
            cout << INDENT << "Good choice!" << endl;
        }
        else
        {
            cout << INDENT << "This square is already filled! Please choose another!" << endl;
        }
        break;
    default:
        cout << "Invalid Command." << endl;
        getCommand();
    }
    

    cout << INDENT << "Press 'Enter' to continue.";
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();
}

void Game::player1Turn()
{
    cout << CSI << 10 << ";" << 0 << "H";
    cout << INDENT << "It's 'O' turn!" << endl;
    getCommand();
    cout << CSI << 9 << ";" << 0 << "H";
    cout << CSI << "0J";
}

void Game::player2Turn()
{
    cout << CSI << 10 << ";" << 0 << "H";
    cout << INDENT << "It's 'X' turn" << endl;
    getCommand();
    cout << CSI << 10 << ";" << 0 << "H";
    cout << CSI << "0J";
}

void Game::update()
{
    Point2D playerPos = m_player.getPosition();

    if (m_player1Turn)
    {
        player1Turn();
    }
    if (m_player2Turn)
    {
        player2Turn();
    }
}

void Game::draw()
{
    Point2D playerPos = m_player.getPosition();
    system("cls");
    drawWelcomeMessage();
    drawGrid();
}