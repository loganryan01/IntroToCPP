#pragma once

#include <string>
#include <iostream>

using namespace std;

class File
{
	private:
		string playerName;
		int playerScore;

	public:
		void input();
		void output();
		string retPlayerName();
		int retPlayerScore();
};

