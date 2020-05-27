#pragma once

const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

// Positioning for the title.
const char* const TITLE = "\x1b[5;20H";

// Move 5 spaces along the X position.
const char* const INDENT = "\x1b[5C";

// Change the text colour to yellow.
const char* const YELLOW = "\x1b[93m";

// Change the text colour to magenta.
const char* const MAGENTA = "\x1b[95m";

// Change the text colour to white.
const char* const RESET_COLOR = "\x1b[0m";

// The slot is empty.
const int EMPTY = 0;

// The slot has a score in it.
const int SCORE = 1;

// The slot has a score in it.
const int INITIALS = 2;

// The height and width of the table that will display the names and their 
// respected scores.
const int DISPLAY_WIDTH = 2;
const int DISPLAY_HEIGHT = 10;

// Move 70 spaces along the X position;
const int INDENT_X = 70;

// Move 10 lines down.
const int DISPLAY_Y = 10;

// The Y position for the starting command input.
const int COMMAND_INPUT_Y = 15;

// The positioning for the player's input.
const int PLAYER_INPUT_X = 35;
const int PLAYER_INPUT_Y = 9;