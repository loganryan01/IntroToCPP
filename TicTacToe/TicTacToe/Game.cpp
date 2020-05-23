#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

// This constructor initialises the variables for this class
Game::Game() : m_gameOver{ false }, m_player1Turn{ true }, m_player2Turn{ false }
{
}

Game::~Game()
{
}

// This function sets up the game by setting up the grid
void Game::startup()
{
    initializeGrid();
}

// This function checks if the game is over by checking if the bollean 
// variable is set to true
bool Game::isGameOver()
{
	return m_gameOver;
}

// The following lines tell the player what game they are playing and how 
// to play it
void Game::drawWelcomeMessage()
{
	// Print title of game
	cout << INDENT << INDENT << MAGENTA << "Welcome to Tic-Tac-Toe" << RESET_COLOR << endl;

	// Print game description
	cout << INDENT << "Tic-Tac-Toe is a game for two players who take turns marking the spaces in a 3x3 grid." << endl;
	cout << INDENT << "The player wins the game by placing 3 of their marks diagonally, vertically or horizontally." << endl << endl;
}

// This function sets up the grid by placing the squares into the correct 
// position
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

// This function draws the grid by going through the squares and drawing 
// them based on what type of squares they are.
void Game::drawGrid()
{
    Point2D position = { 0, 0 };

    // This shows the column numbers for the players to make decision of
    // which column they want to place their token
    cout << INDENT << "    1" << "    2" << "    3" << endl;
    for (position.y = 1; position.y < GRID_HEIGHT; position.y++)
    {
        cout << INDENT;
        // This shows the row numbers for the players to make decision of
        // which column they want to place their token
        cout << position.y << " ";
        for (position.x = 1; position.x < GRID_WIDTH; position.x++)
        {
            m_grid[position.y][position.x].draw();
        }
        cout << endl;
    }
}

// This function gets the command from the players by getting the integer
// that the players inputed.
int Game::getCommand()
{
    int command;

    // This moves the cursor to correct position so the instructions for  
    // the players can be displayed
    cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

    cout << INDENT << "Insert the number row and column you want to place your token:";

    // This moves the cursor to correct position so the input doesn't 
    // overwrite the grid, the messages if there is an error or the 
    // instructions
    cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    cout << YELLOW;
    std::cin >> command;
    cout << RESET_COLOR;

    return command;
}

// This function executes the command
void Game::executeCommand()
{
    int square = getCommand();

    switch (square)
    {
    case 11:
        updateSquare(1, 1);
        break;
    case 12:
        updateSquare(1, 2);
        break;
    case 13:
        updateSquare(1, 3);
        break;
    case 21:
        updateSquare(2, 1);
        break;
    case 22:
        updateSquare(2, 2);
        break;
    case 23:
        updateSquare(2, 3);
        break;
    case 31:
        updateSquare(3, 1);
        break;
    case 32:
        updateSquare(3, 2);
        break;
    case 33:
        updateSquare(3, 3);
        break;
    default:
        // If the players don't input a correct command it will then start
        // again
        cout << INDENT << "Invalid Command." << endl;
    }
    cout << INDENT << "Press 'Enter' to continue.";
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
}

// This function updates the squares
void Game::updateSquare(int row, int column)
{
    // First it checks if that square is empty
    if (m_grid[row][column].getType() == EMPTY)
    {
        // Then, depending on whose turn it is, set the type of square 
        // to that player's token.
        if (m_player1Turn)
        {
            m_grid[row][column].setType(KNOT);
            // It then switches to the next player
            m_player1Turn = false;
            m_player2Turn = true;
        }
        else if (m_player2Turn)
        {
            m_grid[row][column].setType(CROSS);
            m_player2Turn = false;
            m_player1Turn = true;
        }
        // The grid will be updated with that decision
        draw();
        cout << CSI << 10 << ";" << 0 << "H";
        cout << INDENT << "Good choice!" << endl;
    }
    else
    {
        // This will let the player know why they cannot place their 
        // token there
        cout << INDENT << "This square is already filled! Please choose another!" << endl;
    }
}

// This function tells the users whose turn it is
void Game::playerTurn()
{
    cout << CSI << 10 << ";" << 0 << "H";
    if (m_player1Turn)
    {
        cout << INDENT << "It's 'O' turn!" << endl;
    }
    else if (m_player2Turn)
    {
        cout << INDENT << "It's 'X' turn!" << endl;
    }
    executeCommand();
    cout << CSI << 9 << ";" << 0 << "H";
    cout << CSI << "0J";
}

// This function checks if player 1 wins
void Game::player1Wins()
{
    // The game goes through the grid to check if the knots form a 
    // horizontal, vertical or diagonal line
    if (m_grid[1][1].getType() == KNOT && m_grid[1][2].getType() == KNOT && m_grid[1][3].getType() == KNOT ||
        m_grid[2][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[2][3].getType() == KNOT ||
        m_grid[3][1].getType() == KNOT && m_grid[3][2].getType() == KNOT && m_grid[3][3].getType() == KNOT ||
        m_grid[1][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[3][3].getType() == KNOT ||
        m_grid[3][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[1][3].getType() == KNOT ||
        m_grid[1][1].getType() == KNOT && m_grid[2][1].getType() == KNOT && m_grid[3][1].getType() == KNOT ||
        m_grid[2][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[3][2].getType() == KNOT ||
        m_grid[3][1].getType() == KNOT && m_grid[3][2].getType() == KNOT && m_grid[3][3].getType() == KNOT)
    {
        // If it is true, then the game is over and player 1 wins
        m_gameOver = true;
        cout << CSI << 10 << ";" << 0 << "H";
        cout << CSI << "0J";
        cout << INDENT << "'O' Wins!" << endl;
        cout << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

// This function checks if player 2 wins
void Game::player2Wins()
{
    // The game goes through the grid to check if the crosses form a 
    // horizontal, vertical or diagonal line
    if (m_grid[1][1].getType() == CROSS && m_grid[1][2].getType() == CROSS && m_grid[1][3].getType() == CROSS ||
        m_grid[2][1].getType() == CROSS && m_grid[2][2].getType() == CROSS && m_grid[2][3].getType() == CROSS ||
        m_grid[3][1].getType() == CROSS && m_grid[3][2].getType() == CROSS && m_grid[3][3].getType() == CROSS ||
        m_grid[1][1].getType() == CROSS && m_grid[2][2].getType() == CROSS && m_grid[3][3].getType() == CROSS ||
        m_grid[3][1].getType() == CROSS && m_grid[2][2].getType() == CROSS && m_grid[1][3].getType() == CROSS ||
        m_grid[1][1].getType() == CROSS && m_grid[2][1].getType() == CROSS && m_grid[3][1].getType() == CROSS ||
        m_grid[2][1].getType() == CROSS && m_grid[2][2].getType() == CROSS && m_grid[3][2].getType() == CROSS ||
        m_grid[3][1].getType() == CROSS && m_grid[3][2].getType() == CROSS && m_grid[3][3].getType() == CROSS)
    {
        // If it is true, then the game is over and player 2 wins
        m_gameOver = true;
        cout << CSI << 10 << ";" << 0 << "H";
        cout << CSI << "0J";
        cout << INDENT << "'X' Wins!" << endl;
        cout << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

// This function checks if the grid is full
void Game::playersTie()
{
    if (m_grid[1][1].getType() != EMPTY && m_grid[1][2].getType() != EMPTY && m_grid[1][3].getType() != EMPTY &&
        m_grid[2][1].getType() != EMPTY && m_grid[2][2].getType() != EMPTY && m_grid[2][3].getType() != EMPTY &&
        m_grid[3][1].getType() != EMPTY && m_grid[3][2].getType() != EMPTY && m_grid[3][3].getType() != EMPTY)
    {
        // If the gird is full the game is over and nobody wins
        m_gameOver = true;
        cout << CSI << 10 << ";" << 0 << "H";
        cout << CSI << "0J";
        cout << INDENT << "It is a draw." << endl;
        cout << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

// This function constantly updates the game
void Game::update()
{
    playerTurn();
    player1Wins();
    player2Wins();
    playersTie();
}

// This function draws the game
void Game::draw()
{
    system("cls");
    drawWelcomeMessage();
    drawGrid();
}