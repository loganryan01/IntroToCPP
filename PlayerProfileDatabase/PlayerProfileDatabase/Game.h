#pragma once

#include "GameDefines.h"
#include "Slot.h"

class Game
{
public:
	// Constructor
	Game();

	// Destructor
	~Game();

public:
	// Set up the game when it begins.
	bool startup();

	// Update the game overtime.
	void update();

	// Draw the game.
	void draw();

	// Check if the game is over.
	bool isGameOver();

private:
	// Check if virtual terminal is set up.
	bool enableVirtualTerminal();

	// Setup the table to display player information.
	void initializeTable();

	// Load the player information from the binary file.
	void load();

	// Welcome the user to the database.
	void drawWelcomeMessage();

	// Draw the player information table.
	void drawTable();

	// Draw the command list for the user to know what the possible commands are.
	void drawCommandList();

	// Hide the command list.
	void hideCommandList();

	// Update the score for the player.
	void updateScore();

	// Update the name for the player.
	void updateInitials();

	// Get the choice of what command the user wants to do.
	int getChoice();

	// Check that the initials are correct.
	bool correctInitials(char input[4]);

	// Check that there is an available row on the player information table.
	bool availableRow();

	// Sorts the player information table alphabetically.
	void sort();


private:
	// Is the game over?
	bool m_gameOver;

	// The new score for the player.
	int m_score;

	// Which player are we adding or updating?
	int m_playerNumber;

	// The new name for the player.
	char m_initials[4];

	// The table to display the names and highscores.
	Slot m_table[DISPLAY_HEIGHT][DISPLAY_WIDTH];
};