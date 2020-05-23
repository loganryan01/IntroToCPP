#pragma once

#include "GameDefines.h"
#include "Squares.h"

class Squares;

class Game
{
public:
	// Default Constructor
	Game();

	// Destructor
	~Game();

public:
	// This function sets up the game
	void startup();

	void update();
	void draw();

	// This function checks if the game is over
	bool isGameOver();
	
private:
	// This function sets up the grid
	void initializeGrid();
	
	// This function draws the grid
	void drawGrid();

	// This function tells the player information about the game
	void drawWelcomeMessage();

	// This function gets the command from the players
	int getCommand();

	// This function executes the command
	void executeCommand();

	// This function updates the squares
	void updateSquare(int row, int column);

	// This function tells the users whose turn it is
	void playerTurn();

	// This function checks if player 1 wins
	void player1Wins();

	// This function checks if player 2 wins
	void player2Wins();

	// This function checks if the grid is full
	void playersTie();

private:
	bool m_gameOver; // Is the game over?
	bool m_player1Turn; // Is it player 1's turn?
	bool m_player2Turn; // Is it player 2's turn?
	
	// 2D array for grid 
	Squares m_grid[GRID_HEIGHT][GRID_WIDTH]; 
};

