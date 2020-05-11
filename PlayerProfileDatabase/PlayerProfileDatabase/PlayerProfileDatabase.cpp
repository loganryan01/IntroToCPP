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
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";

int main()
{
   // Set output mode to handle virtual terminal sequences
    DWORD dwMode = 0;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    int score = 0;
    char firstLetterOfName = 0;
    int position = 0;

    std::cout << TITLE << MAGENTA << "Welcome to the player profile database!" << RESET_COLOR << std::endl;
    std::cout << INDENT << "This database holds high-scores and who owns those high-scores." << std::endl;
    std::cout << INDENT << "It can be used for any game you wish." << std::endl << std::endl;

    std::cout << INDENT << "First, some questions..." << std::endl;

    // save cursor position
    std::cout << SAVE_CURSOR_POS;
    std::cout << INDENT << "What is your high-score? " << INDENT << YELLOW;

    std::cin >> score;
    std::cout << RESET_COLOR << std::endl;
    if (std::cin.fail())
    {
        std::cout << INDENT << "You have inputed an invalid score." << std::endl;
    }
    else
    {
        std::cout << INDENT << "You entered " << score << std::endl;
    }

    // clear input buffer
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();

    // move the cursor to the start of the 1st question
    std::cout << RESTORE_CURSOR_POS;
    // delete the next 4 lines of text
    std::cout << CSI << "0J";

    std::cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;

    std::cin >> firstLetterOfName;
    std::cout << RESET_COLOR << std::endl;

    if (std::cin.fail() || !isalpha(firstLetterOfName))
    {
        std::cout << INDENT << "You have inputed an invalid letter." << std::endl;
    }
    else
    {
        std::cout << INDENT << "You entered " << firstLetterOfName << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();

    // move the cursor to the start of the 1st question
    std::cout << RESTORE_CURSOR_POS;
    std::cout << CSI << "A";  // cursor up 1
    std::cout << CSI << "0J"; // delete the next 4 lines of text

    if (firstLetterOfName != 0)
    {
        position = (float)score / (firstLetterOfName * 0.02f);
    }
    else
    {
        position = 0;
    }

    std::cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you are "
        << position << " in the world." << std::endl;

    std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
    std::cin.get();
    return 0;
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
