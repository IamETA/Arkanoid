#include "Highscores.h"

std::string Highscores::read_file()
{
	std::string line;
	std::string score;

	std::ifstream file("highscore.txt");
	if (file.is_open()) 
	{
		while (getline(file, line)) 
		{
			score += line + "\n";
		}
		file.close();
	}
	else 
	{
		std::cout << "Failed to open" << std::endl;
	}

	return score;
}


void Highscores::write_file(int score) 
{
	file.open("highscore.txt", std::ios::out | std::ios::app);

	if (file.is_open()) 
	{
		file << score << std::endl;
		file.close();
	}
}