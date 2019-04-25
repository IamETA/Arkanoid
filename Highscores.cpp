#include "Highscores.h"

std::string Highscores::read_file(){
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

	return score;

}


void Highscores::write_file(int score) {
	file.open("highscore.txt");

	if (file.is_open()) {
		file << score;
		file.close();
	}
}