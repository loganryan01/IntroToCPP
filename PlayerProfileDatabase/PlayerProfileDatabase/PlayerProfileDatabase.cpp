// PlayerProfileDatabase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

const char* ESC = "\x1b";
const char* CSI = "\x1b[";

const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RED = "\x1b[91m";
const char* BLUE = "\x1b[94m";
const char* WHITE = "\x1b[97m";
const char* GREEN = "\x1b[92m";
const char* RESET_COLOR = "\x1b[0m";

const int EMPTY = 0;

const int DISPLAY_WIDTH = 3;
const int DISPLAY_HEIGHT = 10;

const int INDENT_X = 5;
const int DISPLAY_Y = 13;
const int PLAYER_INPUT_X = 10;
const int PLAYER_INPUT_Y = 9;

bool enableVirtualTerminal();
void initialize(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH]);
void drawWelcomeMessage();
void drawRow(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int x, int y);
void drawHighScores(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH]);
void getScore();
void getFirstLetter();

int main()
{
    // create a 2D array
    int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH];

    bool gameOver = false;
    if (enableVirtualTerminal() == false)
    {
        std::cout << "The virtual terminal processing mode could not be activated." << std::endl;
        std::cout << "Press 'Enter' to exit." << std::endl;
        std::cin.get();
        return 0;
    }

    initialize(ladder);

    drawWelcomeMessage();

    // output the high-scores
    drawHighScores(ladder);

    while (!gameOver)
    {
        getScore();

        getFirstLetter();
    }

    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program.";
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    return 0;
} 

bool enableVirtualTerminal()
{
    //Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }
    
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}

void initialize(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH])
{
    // fill the arrays with 0
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            ladder[y][x] = EMPTY;
        }
    }
}

void drawWelcomeMessage()
{
    std::cout << TITLE << MAGENTA << "Welcome to the player profile database!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "This database holds high-scores and who owns those high-scores." << std::endl;
    std::cout << INDENT << "It can be used for any game you wish." << std::endl << std::endl;
}

void drawRow(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int x, int y)
{
    // find the console output position
    int outX = INDENT_X + (6 * x) + 1;
    int outY = DISPLAY_Y + y;

    std::cout << CSI << outY << ";" << outX << "H";
    // draw the room
    switch (ladder[y][x])
    {
    case EMPTY:
        std::cout << "[  ]";
    }
}

void drawHighScores(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH])
{
    // reset draw colors
    std::cout << RESET_COLOR;
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        std::cout << INDENT;
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            drawRow(ladder, x, y);
        }
        std::cout << std::endl;
    }
}

void getScore()
{
    int score = 0;
    
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << INDENT << "What is your high-score? " << INDENT << YELLOW;
    std::cin >> score;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail())
    {
        std::cout << INDENT << "You have inputed an invalid score.";
    }
    else
    {
        std::cout << INDENT << "You entered " << score;
    }

    // clear input buffer
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    std::cout << CSI << "1A" << CSI << "2K";
}

void getFirstLetter()
{
    char firstLetterOfName = 0;
    
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> firstLetterOfName;
    std::cout << RESET_COLOR << std::endl;

    if (std::cin.fail() || !isalpha(firstLetterOfName))
    {
        std::cout << INDENT << "You have inputed an invalid letter.";
    }
    else
    {
        std::cout << INDENT << "You entered " << firstLetterOfName;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
    std::cout << CSI << "1A" << CSI << "2K";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
