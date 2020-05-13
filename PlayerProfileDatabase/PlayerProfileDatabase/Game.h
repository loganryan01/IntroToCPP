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

	void drawWelcomeMessage();
	void drawTable();

	void updateScore(int choice);
	void updateInitials(int choice);

	int getChoice();

private:
	bool m_gameOver;
	int m_score;
	char m_initials[4];
	Slot m_table[DISPLAY_HEIGHT][DISPLAY_WIDTH];
};

