#pragma once

const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

const char* const INDENT = "\x1b[5C";
const char* const YELLOW = "\x1b[93m";
const char* const MAGENTA = "\x1b[95m";
const char* const RESET_COLOR = "\x1b[0m";


const int EMPTY = 0;
const int KNOT = 1;
const int CROSS = 2;

const int GRID_WIDTH = 3;
const int GRID_HEIGHT = 3;

const int INDENT_X = 5;
const int MAP_Y = 12;
const int PLAYER_INPUT_X = 70;
const int PLAYER_INPUT_Y = 9;