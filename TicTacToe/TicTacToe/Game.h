#pragma once

#include "GameDefines.h"
#include "Squares.h"

class Squares;

class Game
{
public:
	// Constructor
	Game();

	// Destructor
	~Game();

public:
	// Sets up the game by setting up the grid.
	void startup();

	// Update the game.
	void update();

	// Draw the game.
	void draw();

	// Checks if the game is over.
	bool isGameOver();
	
private:
	// Sets up the grid.
	void initializeGrid();

	// Draws the grid.
	void drawGrid();

	// Welcome the players to tic tac toe.
	void drawWelcomeMessage();

	// Gets the square from the players.
	int getCommand();

	// Checks that the command is valid.
	void executeCommand();

	// Updates the squares
	void updateSquare(int row, int column);

	// Tells the users whose turn it is.
	void playerTurn();

	// Check if player 1 wins.
	void player1Wins();

	// Check if player 2 wins.
	void player2Wins();

	// Checks if the grid is full.
	void playersTie();

private:
	// Is the game over?
	bool m_gameOver; 

	// Is it player 1's (Knots) turn?
	bool m_player1Turn; 

	// Is it player 2's (Crosses) turn?
	bool m_player2Turn; 
	
	// 2D array for grid 
	Squares m_grid[GRID_HEIGHT][GRID_WIDTH]; 
};

