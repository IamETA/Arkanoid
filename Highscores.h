#pragma once

#include <fstream>
#include <iostream>
#include <string>

class Highscores
{
public:
	explicit Highscores() = default;
	~Highscores() = default;

	std::string read_file();
	void write_file(int score);

private:
	std::ofstream file;
};

