#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

Game::Game() : player1Name{ }, player2Name{ }
{
	m_gameOver = false;
}

Game::~Game()
{

}

bool Game::startup()
{
	m_player.setPosition(Point2D{ 0,0 });

	return true;
}

bool Game::isGameOver()
{
	return m_gameOver;
}

void Game::drawWelcomeMessage()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Print title of game
	SetConsoleTextAttribute(h, 13 | FOREGROUND_INTENSITY);
	cout << INDENT << INDENT << "Welcome to Tic-Tac-Toe" << endl;

	// Print game description
	SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
	cout << INDENT << "Tic-Tac-Toe is a game for two players who take turns marking the spaces in a 3x3 grid." << endl;
	cout << INDENT << "The player wins the game by placing 3 of their marks diagonally, vertically or horizontally." << endl << endl;
}

void Game::setPlayerNames(char player1Name[50], char player2Name[50])
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set player 1 name
    cout << endl;
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "Player 1, What is your name? " << INDENT;
    SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
    cin >> player1Name;
    cout << endl;

    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
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
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "Player 2, What is your name? " << INDENT;
    SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
    cin >> player2Name;
    cout << endl;

    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
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
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "So we have " << player1Name << " vs. " << player2Name << endl;
    cout << INDENT << "Let the game begin" << endl;

    cout << endl << INDENT << "Press 'Enter' to begin the game." << endl;
    cin.get();
}

void Game::drawGrid()
{
	Point2D position = m_player.getPosition();

    // Draw grid
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        cout << INDENT;
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (position.x == x && position.y == y)
            {
                cout << PLAYER_TILE;
                continue;
            }

			m_grid[y][x].draw();
        }
        cout << endl;
    }
	cout << endl;
}

void Game::drawValidDirections()
{
    Point2D position = m_player.getPosition();
    
    cout << INDENT << "You can move " <<
        ((position.x > 0) ? "left, " : "") <<
        ((position.x < GRID_WIDTH - 1) ? "right, " : "") <<
        ((position.y > 0) ? "up, " : "") <<
        ((position.y < GRID_HEIGHT - 1) ? "down, " : "") << endl;
}

void Game::update()
{
    Point2D playerPos = m_player.getPosition();

    int command = getch();

    if (m_player.executeCommand(command))
        return;
}

void Game::draw()
{
    Point2D playerPos = m_player.getPosition();
    system("cls");
    drawWelcomeMessage();
    drawValidDirections();
    drawGrid();
}