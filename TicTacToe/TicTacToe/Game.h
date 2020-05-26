#pragma once

#include "GameDefines.h"
#include "Squares.h"

class Squares;

class Game
{
public:
	Game();
	~Game();

public:
	void startup();

	void update();
	void draw();

	bool isGameOver();
	
private:
	void initializeGrid();
	void drawGrid();
	void drawWelcomeMessage();
	int getCommand();
	void executeCommand();
	void updateSquare(int row, int column);
	void playerTurn();
	void player1Wins();
	void player2Wins();
	void playersTie();

private:
	bool m_gameOver; 
	bool m_player1Turn; 
	bool m_player2Turn; 
	
	// 2D array for grid 
	Squares m_grid[GRID_HEIGHT][GRID_WIDTH]; 
};

