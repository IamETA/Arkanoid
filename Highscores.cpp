#include "Highscores.h"

int Highscores::readFile() const {
	std::string line;
	std::string score;

	std::ifstream file("highscore.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			score = line;
		}
		file.close();
	}
	else {
		std::cout << "Failed to open" << std::endl;
	}

	int converted_score = atoi(score.c_str());
	return converted_score;
}


void Highscores::writeFile(int score) {
	file.open("highscore.txt");

	if (file.is_open()) {
		file << score;
		file.close();
	}
}