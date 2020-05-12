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
const int POSITION = 1;
const int SCORE = 2;
const int FIRSTLETTER = 3;
const int LASTLETTER = 4;

const int DISPLAY_WIDTH = 4;
const int DISPLAY_HEIGHT = 10;

const int INDENT_X = 5;
const int DISPLAY_Y = 14;
const int PLAYER_INPUT_X = 10;
const int PLAYER_INPUT_Y = 9;

bool enableVirtualTerminal();
void initialize(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH]);
void drawWelcomeMessage();
void drawRow(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int x, int y);
void drawHighScores(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH]);
bool isRowEmpty(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice);
void input(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH]);
void fillScoreSlot(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice);
void fillFirstNameSlot(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice);
void fillLastNameSlot(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice);

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
        input(ladder);
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
            if (x == 0)
            {
                ladder[y][0] = POSITION;
            }
            if (x == 1)
            {
                ladder[y][1] = EMPTY;
            }
            if (x == 2)
            {
                ladder[y][2] = EMPTY;
            }
            if (x == 3)
            {
                ladder[y][3] = EMPTY;
            }
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
    int outX = INDENT_X + (12 * x) + 1;
    int outY = DISPLAY_Y + y;

    std::cout << CSI << outY << ";" << outX << "H";
    // draw the room
    switch (ladder[y][x])
    {
    case EMPTY:
        std::cout << "          |";
        break;
    case POSITION:
        if (y == 9)
        {
            std::cout << "   " << y + 1 << ".   |";
            break;
        }
        std::cout << "    " << y + 1 << ".   |";
        break;
    }
}

void drawHighScores(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH])
{
    // reset draw colors
    std::cout << RESET_COLOR;
    std::cout << CSI << "13;6H";
    std::cout << "Position |" << std::endl;
    std::cout << CSI << "13;17H";
    std::cout << "High-Score |" << std::endl;
    std::cout << CSI << "13;30H";
    std::cout << "FirstName |" << std::endl;
    std::cout << CSI << "13;42H";
    std::cout << "Last Name |" << std::endl;
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

bool isRowEmpty(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice)
{
    if (ladder[choice - 1][1] == EMPTY && ladder[choice - 1][2] == EMPTY && ladder[choice - 1][3] == EMPTY)
    {
        return true;
    }
    return false;
}

void input(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH])
{
    int choice = 0;

    std::cout << CSI << PLAYER_INPUT_Y + 2 << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << INDENT << "Choose a position: " << INDENT << YELLOW;
    std::cin >> choice;
    std::cout << RESET_COLOR;

    if (isRowEmpty(ladder, choice))
    {
        fillScoreSlot(ladder, choice);
        fillFirstNameSlot(ladder, choice);
        fillLastNameSlot(ladder, choice);
    }
    else if (choice > DISPLAY_HEIGHT)
    {
        std::cout << INDENT << "Invalid choice." << std::endl;
        std::cout << INDENT << "Press 'Enter' to continue" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        std::cout << CSI << PLAYER_INPUT_Y + 1 << ";" << 0 << "H";
        std::cout << CSI << "2K";
    }
    else
    {
        std::cout << INDENT << "That row is full. Try picking another one." << std::endl;
        std::cout << INDENT << "Press 'Enter' to continue" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
        std::cout << CSI << PLAYER_INPUT_Y + 1 << ";" << 0 << "H";
        std::cout << CSI << "2K";
    }
}

void fillScoreSlot(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice)
{
    int score = 0;

    std::cout << CSI << PLAYER_INPUT_Y + 2 << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << INDENT << "Enter High-Score: " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> score;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail())
    {
        std::cout << INDENT << "You have inputed an invalid score.";
    }
    else
    {
        ladder[choice - 1][1] = SCORE;

        // find the console output position
        int outX = INDENT_X + (11 * 1) + 1;
        int outY = DISPLAY_Y + (choice - 1);

        std::cout << CSI << outY << ";" << outX << "H";

        // draw the room
        switch (ladder[choice - 1][1])
        {
        case SCORE:
            std::cout << score;
            break;
        }
    }
}

void fillFirstNameSlot(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice)
{
    char firstLetterOfName = 0;

    std::cout << CSI << PLAYER_INPUT_Y + 2 << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << INDENT << "Enter first letter of your first name: " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> firstLetterOfName;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail())
    {
        std::cout << INDENT << "You have inputed an invalid letter.";
    }
    else
    {
        ladder[choice - 1][2] = FIRSTLETTER;

        // find the console output position
        int outX = INDENT_X + (12 * 2) + 1;
        int outY = DISPLAY_Y + (choice - 1);

        std::cout << CSI << outY << ";" << outX << "H";

        // draw the room
        switch (ladder[choice - 1][2])
        {
        case FIRSTLETTER:
            std::cout << firstLetterOfName;
            break;
        }
    }
}

void fillLastNameSlot(int ladder[DISPLAY_HEIGHT][DISPLAY_WIDTH], int choice)
{
    char lastLetterOfName = 0;

    std::cout << CSI << PLAYER_INPUT_Y + 2 << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
    std::cout << CSI << "2K";
    std::cout << INDENT << "Enter first letter of your last name: " << INDENT << YELLOW;
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cin >> lastLetterOfName;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail() || !isalpha(lastLetterOfName))
    {
        std::cout << INDENT << "You have inputed an invalid letter.";
    }
    else
    {
        ladder[choice - 1][3] = LASTLETTER;

        // find the console output position
        int outX = INDENT_X + (12 * 3) + 1;
        int outY = DISPLAY_Y + (choice - 1);

        std::cout << CSI << outY << ";" << outX << "H";

        // draw the room
        switch (ladder[choice - 1][3])
        {
        case LASTLETTER:
            std::cout << lastLetterOfName;
            break;
        }
    }
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
