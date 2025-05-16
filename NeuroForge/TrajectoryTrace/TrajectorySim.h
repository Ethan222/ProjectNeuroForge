#pragma once
#include <thread>
#include <chrono>
#include "GameMap.h"
#include "Ball.h"
#include "Point.h"

class TrajectorySim {
public:
	static Point simulate(const GameMap&, Ball*);
private:
	static constexpr int WAIT_TIME = 400;
};

Point TrajectorySim::simulate(const GameMap& map, Ball* ball)
{
	while (ball->move(map)) {
		system("cls");
		map.display(false, ball->getX(), ball->getY());
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_TIME));
	}
	system("cls");
	return Point(ball->getX(), ball->getY());
}
