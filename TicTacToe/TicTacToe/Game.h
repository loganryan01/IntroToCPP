#pragma once

#include "GameDefines.h"
#include "Squares.h"
#include "Player.h"

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

	void drawWelcomeMessage(); 
	
private:
	void initializeGrid();
	
	void drawGrid();

	void getCommand();
	void player1Turn();
	void player2Turn();

private:
	bool m_gameOver;
	bool m_player1Turn;
	bool m_player2Turn;
	
	Squares m_grid[GRID_HEIGHT][GRID_WIDTH];
	Player m_player;
};

