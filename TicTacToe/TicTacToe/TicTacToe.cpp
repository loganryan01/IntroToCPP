// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

using namespace std;

const char* INDENT = "\t";

int main()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    
    char player1Name[50];
    char player2Name[50];
    
    // Print title of game
    SetConsoleTextAttribute(h, 13 | FOREGROUND_INTENSITY);
    cout << INDENT << INDENT << "Welcome to Tic-Tac-Toe" << endl;

    // Print game description
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "Tic-Tac-Toe is a game for two players who take turns marking the spaces in a 3x3 grid." << endl;
    cout << INDENT << "The player wins the game by placing 3 of their marks diagonally, vertically or horizontally." << endl << endl;
    
    // Set player 1 name
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "Player 1, What is your name? " << INDENT;
    SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
    cin >> player1Name;
    cout << endl;

    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    if (cin.fail())
    {
        cout << INDENT << "You cannot use that name." << endl;
    }
    else
    {
        cout << INDENT << "Welcome " << player1Name << ", You will be 'O'." << endl;
    }
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();

    // Set player 2 name
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "Player 2, What is your name? " << INDENT;
    SetConsoleTextAttribute(h, 14 | FOREGROUND_INTENSITY);
    cin >> player2Name;
    cout << endl;

    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    if (cin.fail())
    {
        cout << INDENT << "You cannot use that name." << endl;
    }
    else
    {
        cout << INDENT << "Welcome " << player2Name << ", You will be 'X'." << endl;
    }
    cin.clear();
    cin.ignore(cin.rdbuf()->in_avail());
    cin.get();

    // Print player names
    SetConsoleTextAttribute(h, 15 | FOREGROUND_INTENSITY);
    cout << INDENT << "So we have " << player1Name << " vs. " << player2Name << endl;
    cout << INDENT << "Let the game begin" << endl;

    cout << endl << INDENT << "Press 'Enter' to begin the game." << endl;
    cin.get();

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
