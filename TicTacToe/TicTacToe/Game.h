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
	bool startup();

	void update();
	void draw();

	bool isGameOver();
	
private:
	void initializeGrid();
	
	void drawGrid();
	void drawWelcomeMessage();

	void getCommand();
	void player1Turn();
	void player2Turn();
	void player1Wins();
	void player2Wins();
	void playersTie();

private:
	bool m_gameOver;
	bool m_player1Turn;
	bool m_player2Turn;
	bool m_player1Wins;
	bool m_player2Wins;
	
	Squares m_grid[GRID_HEIGHT][GRID_WIDTH];
};

