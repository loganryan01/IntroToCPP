#include "File.h"

using namespace std;

/*
	* This function takes input from user about Player Details
	* The input taken by this function is stored in the File using writeFile() function
*/
void File::input()
{
	// Taking input of Player Name as First Name and Second Name
	string strFname = "", strLname = "";
	cout << "\nEnter the First Name of Player: ";
	cin >> strFname;
	cout << "\nEnter the Last Name of Player: ";
	cin >> strLname;
	playerName = strFname + " " + strLname; // Stores the player as Fname_Lname ex. Aastha_Anand

	cout << "\nEnter Player Highscore: ";
	cin >> playerScore;
}

/*
	* This function outputs the player details
*/
void File::output()
{
	cout << "\nPlayer Details: \n";
	cout << "player name==>" << playerName << endl;
	cout << "player score==>" << playerScore << endl;
}