#pragma once

#include "GameDefines.h"
#include "Slot.h"

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
	bool enableVirtualTerminal();
	void initializeTable();
	void load();

	void drawWelcomeMessage();
	void drawTable();
	void drawCommandList();
	void hideCommandList();

	void updateScore();
	void updateInitials();

	int getChoice();

	bool correctInitials(char input[4]);
	bool availableRow();

	void sort();

private:
	bool m_gameOver;
	int m_score;
	int m_playerNumber;
	char m_initials[4];
	Slot m_table[DISPLAY_HEIGHT][DISPLAY_WIDTH];
};