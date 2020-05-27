#pragma once

const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

// Move 5 spaces to right.
const char* const INDENT = "\x1b[5C";

// Change the text colour to red.
const char* const RED = "\x1b[91m";

// Change the text colour to yellow.
const char* const YELLOW = "\x1b[93m";

// Change the text colour to blue.
const char* const BLUE = "\x1b[94m";

// Change the text colour to magenta.
const char* const MAGENTA = "\x1b[95m";

// Change the text colour to white.
const char* const RESET_COLOR = "\x1b[0m";

// The square is empty.
const int EMPTY = 0;

// The square has a knot token in it.
const int KNOT = 1;

// The square has a cross token in it.
const int CROSS = 2;

// The grid width and height is 3 but I had to make it 4 so in the draw
// grid function so it can draw the row number at the start.
const int GRID_WIDTH = 4;
const int GRID_HEIGHT = 4;

// Move 5 spaces to right.
const int INDENT_X = 5;

// X and Y positioning for player input
const int PLAYER_INPUT_X = 70;
const int PLAYER_INPUT_Y = 11;