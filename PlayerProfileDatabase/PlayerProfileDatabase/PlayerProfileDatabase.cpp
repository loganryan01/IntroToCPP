// PlayerProfileDatabase.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    int score = 0;
    char firstLetterOfName = 0;
    int position = 0;

    std::cout << "Welcome to the player profile database!" << std::endl;
    std::cout << "This database holds high-scores and who owns those high-scores." << std::endl;
    std::cout << "It can be used for any game you wish." << std::endl << std::endl;

    std::cout << "First, some questions..." << std::endl;
    std::cout << "What is your high-score? " << std::endl;

    std::cin >> score;
    if (std::cin.fail())
    {
        std::cout << "You have inputed an invalid score." << std::endl;
    }
    else
    {
        std::cout << "You entered " << score << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    std::cout << "What is the first letter of your name? " << std::endl;

    std::cin >> firstLetterOfName;

    if (std::cin.fail() || !isalpha(firstLetterOfName))
    {
        std::cout << "You have inputed an invalid letter." << std::endl;
    }
    else
    {
        std::cout << "You entered " << firstLetterOfName << std::endl;
    }
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());

    if (firstLetterOfName != 0)
    {
        position = (float)score / (firstLetterOfName * 0.02f);
    }
    else
    {
        position = 0;
    }

    std::cout << std::endl << "Using a complex deterministic algorithm, it has been calculated that you are "
        << position << " in the world." << std::endl;

    std::cout << std::endl << "Press 'Enter' to exit the program." << std::endl;
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
