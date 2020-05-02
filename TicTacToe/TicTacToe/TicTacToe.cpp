// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

const char* INDENT = "\t";
const char* EMPTY_TILE = "[   ]";
const char* KNOT_TILE = "[ O ]";
const char* CROSS_TILE = "[ X ]";
const char* PLAYER_TILE = "[ # ]";

const int EMPTY = 0;
const int KNOT = 1;
const int CROSS = 2;
const int PLAYER = 3;

const int GRID_WIDTH = 3;
const int GRID_HEIGHT = 3;

const int LEFT = 4;
const int RIGHT = 6;
const int UP = 8;
const int DOWN = 2;

void drawWelcomeMessage();
void drawGrid(int grid[GRID_HEIGHT][GRID_WIDTH], int playerX, int playerY);
void setPlayerNames(char player1Name[50], char player2Name[50]);
void drawValidDirections(int x, int y);
int getMovementDirection();

int main()
{
    char player1Name[50];
    char player2Name[50];

    int grid[GRID_HEIGHT][GRID_WIDTH];

    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            grid[y][x] = EMPTY;
        }
    }

    bool gameOver = false;
    int playerX = 0;
    int playerY = 0;

    drawWelcomeMessage();

    setPlayerNames(player1Name, player2Name);

    // game loop
    while (!gameOver)
    {
        system("cls");

        drawWelcomeMessage();
        //output the grid
        drawGrid(grid, playerX, playerY);

        drawValidDirections(playerX, playerY);
        cout << INDENT << player1Name << " Where to now?" << INDENT;

        int player1direction = getMovementDirection();

        switch (player1direction)
        {
        case RIGHT:
            if (playerX < GRID_WIDTH - 1)
                playerX++;
            break;
        case LEFT:
            if (playerX > 0)
                playerX--;
            break;
        case UP:
            if (playerY > 0)
                playerY--;
            break;
        case DOWN:
            if (playerY < GRID_HEIGHT - 1)
                playerY++;
        default:
            // do nothing, go back to the top of the loop and ask again
            break;
        }
    }

    return 0;
}

void drawWelcomeMessage()
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

void drawGrid(int grid[GRID_HEIGHT][GRID_WIDTH], int playerX, int playerY)
{
    // Draw grid
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        cout << INDENT;
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (playerX == x && playerY == y)
            {
                cout << PLAYER_TILE;
                continue;
            }

            switch (grid[y][x])
            {
            case EMPTY:
                cout << EMPTY_TILE;
            }
        }
        cout << endl;
    }
}

void setPlayerNames(char player1Name[50], char player2Name[50])
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

void drawValidDirections(int x, int y)
{
    cout << INDENT << "You can move " <<
        ((x > 0) ? "left, " : "") <<
        ((x < GRID_WIDTH - 1) ? "right, " : "") <<
        ((y > 0) ? "up, " : "") <<
        ((y < GRID_HEIGHT - 1) ? "down, " : "") << endl;
}

int getMovementDirection()
{
    // clear the input buffer, ready for player input
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());

    int direction = 0;
    cin >> direction;

    if (cin.fail())
        return 0;
    return direction;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
