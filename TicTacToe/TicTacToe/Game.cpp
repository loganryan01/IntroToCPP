/*--------------------------------------
    File Name: Game.cpp
    Purpose: Run the game.
    Author: Logan Ryan
    Modified: 26 May 2020
----------------------------------------
    Copyright 2020 Logan Ryan.
--------------------------------------*/

#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

//---------------------------------------------------------
// Initialise the variables in the class.
//	 m_gameOver (bool): Is the game over?
//   m_player1Turn (bool): Is it player 1's (Knots) turn?
//   m_player2Turn (bool): Is it player 2's (Crosses) turn?
//--------------------------------------------------------- 
Game::Game() : m_gameOver{ false }, m_player1Turn{ true }, m_player2Turn{ false }
{
}

Game::~Game()
{
}

//-----------------------------------------
// Sets up the game by setting up the grid.
//-----------------------------------------
void Game::startup()
{
    initializeGrid();
}

//----------------------------------------------------------
// Checks if the game is over.
//   return (bool): Returns whether the game is over or not.
//----------------------------------------------------------
bool Game::isGameOver()
{
	return m_gameOver;
}

//------------------------------------
// Welcome the players to tic tac toe.
//------------------------------------
void Game::drawWelcomeMessage()
{
	// Print title of game
    std::cout << INDENT << INDENT << MAGENTA << "Welcome to Tic-Tac-Toe" << RESET_COLOR << endl;

	// Print game description
    std::cout << INDENT << "Tic-Tac-Toe is a game for two players who take turns marking the spaces in a 3x3 grid." << endl;
    std::cout << INDENT << "The player wins the game by placing 3 of their marks diagonally, vertically or horizontally." << endl << endl;
}

//------------------
// Sets up the grid.
//------------------
void Game::initializeGrid()
{
    // Go through each of the squares in the grid.
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            // Set the squares to their respected positions.
            m_grid[y][x].setPosition(Point2D{ x, y });
        }
    }
}

//----------------
// Draws the grid.
//----------------
void Game::drawGrid()
{
    Point2D position = { 0, 0 };

    // Print the column numbers.
    std::cout << INDENT << "    1" << "    2" << "    3" << endl;

    // Go through the rows
    for (position.y = 1; position.y < GRID_HEIGHT; position.y++)
    {
        // Move to the correct position.
        std::cout << INDENT;

        // Print the row number.
        std::cout << position.y << " ";

        // Go through the columns
        for (position.x = 1; position.x < GRID_WIDTH; position.x++)
        {
            // Draw what is meant to be in the squares based on their types.
            m_grid[position.y][position.x].draw();
        }
        std::cout << endl;
    }
}

//------------------------------------------------------------------------
// Gets the square from the players.
//   return (int): Returns the square that the player wants to place their 
//                 token. 
//------------------------------------------------------------------------
int Game::getCommand()
{
    int command;

    // Move the cursor to correct position.
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

    // Display instructions.
    std::cout << INDENT << "Insert the number row and column you want to place your token:";

    // Move the cursor to correct position.
    std::cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H";

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    // Get command
    std::cout << YELLOW;
    std::cin >> command;
    std::cout << RESET_COLOR;

    return command;
}

//----------------------------------
// Checks that the command is valid.
//----------------------------------
void Game::executeCommand()
{
    int square = getCommand();

    // Check that the square is valid
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
        // If the players don't input a correct square it will then start
        // again.
        cout << INDENT << "Invalid Choice." << endl;
    }
    std::cout << INDENT << "Press 'Enter' to continue.";
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
}

//-----------------------------------------------
// Updates the squares
//   row (int): Which row is the square in?
//   column (int): Which column is the square in?
//-----------------------------------------------
void Game::updateSquare(int row, int column)
{
    // Checks if that square is empty.
    if (m_grid[row][column].getType() == EMPTY)
    {
        // Depending on whose turn it is, set the type of square to that 
        // player's token.
        if (m_player1Turn)
        {
            m_grid[row][column].setType(KNOT);
            // Switch to the next player.
            m_player1Turn = false;
            m_player2Turn = true;
        }
        else if (m_player2Turn)
        {
            m_grid[row][column].setType(CROSS);
            m_player2Turn = false;
            m_player1Turn = true;
        }
        // The grid will be updated with that decision.
        draw();
        std::cout << CSI << 10 << ";" << 0 << "H";
        std::cout << INDENT << "Good choice!" << endl;
    }
    else
    {
        // Let the player know why they cannot place their token there.
        std::cout << INDENT << "This square is already filled! Please choose another!" << endl;
    }
}

//----------------------------------
// Tells the users whose turn it is.
//----------------------------------
void Game::playerTurn()
{
    // Move the cursor to the correct position.
    std::cout << CSI << 10 << ";" << 0 << "H";

    // If it's player 1's turn.
    if (m_player1Turn)
    {
        std::cout << INDENT << "It's 'O' turn!" << endl;
    }
    else if (m_player2Turn) // If it's player 2's turn.
    {
        std::cout << INDENT << "It's 'X' turn!" << endl;
    }
    executeCommand();

    // Clear the input area.
    std::cout << CSI << 9 << ";" << 0 << "H";
    std::cout << CSI << "0J";
}

//------------------------
// Check if player 1 wins.
//------------------------
void Game::player1Wins()
{
    // Go through the grid to check if the knots form a horizontal, vertical
    // or diagonal line.
    if (m_grid[1][1].getType() == KNOT && m_grid[1][2].getType() == KNOT && m_grid[1][3].getType() == KNOT ||
        m_grid[2][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[2][3].getType() == KNOT ||
        m_grid[3][1].getType() == KNOT && m_grid[3][2].getType() == KNOT && m_grid[3][3].getType() == KNOT ||
        m_grid[1][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[3][3].getType() == KNOT ||
        m_grid[3][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[1][3].getType() == KNOT ||
        m_grid[1][1].getType() == KNOT && m_grid[2][1].getType() == KNOT && m_grid[3][1].getType() == KNOT ||
        m_grid[2][1].getType() == KNOT && m_grid[2][2].getType() == KNOT && m_grid[3][2].getType() == KNOT ||
        m_grid[3][1].getType() == KNOT && m_grid[3][2].getType() == KNOT && m_grid[3][3].getType() == KNOT)
    {
        // If it is true, then the game is over and player 1 wins.
        m_gameOver = true;
        std::cout << CSI << 10 << ";" << 0 << "H";
        std::cout << CSI << "0J";
        std::cout << INDENT << "'O' Wins!" << endl;
        std::cout << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

//------------------------
// Check if player 2 wins.
//------------------------
void Game::player2Wins()
{
    // Go through the grid to check if the crosses form a horizontal, 
    // vertical or diagonal line
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
        std::cout << CSI << 10 << ";" << 0 << "H";
        std::cout << CSI << "0J";
        std::cout << INDENT << "'X' Wins!" << endl;
        std::cout << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

//----------------------------
// Checks if the grid is full.
//----------------------------
void Game::playersTie()
{
    // Go through the grid to check if the grid is full.
    if (m_grid[1][1].getType() != EMPTY && m_grid[1][2].getType() != EMPTY && m_grid[1][3].getType() != EMPTY &&
        m_grid[2][1].getType() != EMPTY && m_grid[2][2].getType() != EMPTY && m_grid[2][3].getType() != EMPTY &&
        m_grid[3][1].getType() != EMPTY && m_grid[3][2].getType() != EMPTY && m_grid[3][3].getType() != EMPTY)
    {
        // If the grid is full the game is over and nobody wins.
        m_gameOver = true;
        std::cout << CSI << 10 << ";" << 0 << "H";
        std::cout << CSI << "0J";
        std::cout << INDENT << "It is a draw." << endl;
        std::cout << INDENT << "Press 'Enter' to exit the program.";
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    }
}

//-----------------
// Update the game.
//-----------------
void Game::update()
{
    playerTurn();
    player1Wins();
    player2Wins();
    playersTie();
}

//---------------
// Draw the game.
//---------------
void Game::draw()
{
    // Clear the screen.
    system("cls");
    drawWelcomeMessage();
    drawGrid();
}