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
	void setPlayerNames(char player1Name[50], char player2Name[50]);
	
private:
	void drawGrid();

private:
	bool m_gameOver;
	char player1Name[50];
	char player2Name[50];
	Squares m_grid[GRID_HEIGHT][GRID_WIDTH];
	Player m_player;
};

