#pragma once

const char* const ESC = "\x1b";
const char* const CSI = "\x1b[";

const char* const TITLE = "\x1b[5;20H";
const char* const INDENT = "\x1b[5C";
const char* const YELLOW = "\x1b[93m";
const char* const MAGENTA = "\x1b[95m";
const char* const RED = "\x1b[91m";
const char* const BLUE = "\x1b[94m";
const char* const WHITE = "\x1b[97m";
const char* const GREEN = "\x1b[92m";
const char* const RESET_COLOR = "\x1b[0m";

const int EMPTY = 0;
const int POSITION = 1;
const int SCORE = 2;
const int INITIALS = 3;

const int DISPLAY_WIDTH = 2;
const int DISPLAY_HEIGHT = 10;

const int INDENT_X = 5;
const int DISPLAY_Y = 10;
const int PLAYER_INPUT_X = 35;
const int PLAYER_INPUT_Y = 9;