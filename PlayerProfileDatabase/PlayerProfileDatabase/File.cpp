#include "File.h"

using namespace std;

struct Player
{
	char first[25];
	char last[25];
	int score;
};

void File::addPlayer()
{
	Player player;

	cout << "Enter your first name: ";
	cin >> player.first;
	cout << "Enter your last name:";
	cin >> player.last;
	cout << "Enter your high-score: ";
	cin >> player.score;

	fstream file;
	file.open("data.dat", ios::out | ios::binary | ios::app);
	file.seekp(4, ios::beg);
	file.write((char*)&player, sizeof(player));
	file.close();
}

void File::showAllPlayers()
{
	fstream file;
	file.open("data.dat", ios_base::in | ios_base::binary);
	if (file.is_open())
	{
		while (!file.eof() && file.peek() != EOF)
		{
			Player player;
			file.read((char*)&player, sizeof(Player));
			cout << player.first << " " << player.last << " " << player.score << endl;
		}
		file.close();
	}
}