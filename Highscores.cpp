#include "Highscores.h"

std::string Highscores::readFile(){
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

	/*
		int converted_score = atoi(score.c_str());
	return converted_score;
	
	*/

	return score;

}


void Highscores::writeFile(int score) {
	file.open("highscore.txt");

	if (file.is_open()) {
		file << score;
		file.close();
	}
}