#pragma once

const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

const char* const INDENT = "\x09";
const char* const YELLOW = "\x1b[93m";
const char* const MAGENTA = "\x1b[95m";
const char* const RESET_COLOR = "\x1b[97m";

const char* const EMPTY_TILE = "[   ]";
const char* const KNOT_TILE = "[ O ]";
const char* const CROSS_TILE = "[ X ]";
const char* const PLAYER_TILE = "[ # ]";

const int EMPTY = 0;
const int KNOT = 1;
const int CROSS = 2;
const int PLAYER = 3;

const int GRID_WIDTH = 3;
const int GRID_HEIGHT = 3;