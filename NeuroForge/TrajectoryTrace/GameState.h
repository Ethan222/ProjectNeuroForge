#pragma once
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()
#include <thread>
#include <chrono>
#include <stdexcept>
#include "GameMap.h"
#include "Ball.h"
#include "TrajectorySim.h"
#include "Point.h"

class GameState {
public:
	GameState();
	~GameState();

	void run();
private:
	GameMap map;
	Ball* ball;
};

GameState::GameState() {
	srand(static_cast<unsigned>(time(0)));
	int x, y, dx, dy;
	switch (rand() % 4) {	// starting wall
	case 0:	// top wall
		dx = 0;
		dy = 1;
		x = rand() % (map.getWidth() - 2) + 1;
		y = 0;
		break;
	case 1:	// left wall
		dx = 1;
		dy = 0;
		x = 0;
		y = rand() % (map.getHeight() - 2) + 1;
		break;
	case 2:	// right wall
		dx = -1;
		dy = 0;
		x = map.getWidth() - 1;
		y = rand() % (map.getHeight() - 2) + 1;
		break;
	default:	// bottom wall
		dx = 0;
		dy = -1;
		x = rand() % (map.getWidth() - 2) + 1;
		y = map.getHeight() - 1;
	}
	ball = new Ball(x, y, dx, dy);
}

inline GameState::~GameState() {
	delete ball;
}

void GameState::run() {
	map.generateRandomLayout();
	map.display();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	system("cls");

	map.display(true, ball->getX(), ball->getY());
	Point prediction;
	bool valid{ false };
	do {
		try {
			std::cout << "Prediction: ";
			std::cin >> prediction;
			map.setGuess(prediction.x, prediction.y);
			valid = true;
		}
		catch (const std::invalid_argument& e) {
			std::cout << e.what() << '\n';
		}
	} while (!valid);

	Point actual = TrajectorySim::simulate(map, ball);
	map.display(false, ball->getX(), ball->getY());
	std::cout << "\nPrediction: " << prediction << '\n'
				<< "    Actual: " << actual << "\n\n"
		<< (prediction == actual ? "Correct!" : "Incorrect") << "\n\n";
}
