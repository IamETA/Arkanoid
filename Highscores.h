#pragma once

#include <fstream>
#include <iostream>
#include <string>

class Highscores
{
public:
	explicit Highscores() = default;
	~Highscores() = default;

	std::string readFile();
	void writeFile(int score);

private:
	std::ofstream file;
};

