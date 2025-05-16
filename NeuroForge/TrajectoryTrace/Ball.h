#pragma once
#include "GameMap.h"

class Ball {
public:
	Ball(int startX, int startY, int dx, int dy);

	int getX() const { return x; }
	int getY() const { return y; }

	bool move(const GameMap& map);	// returns false when it hits a wall

private:
	int x, y;
	int dx, dy;

	void reflect(char mirror);
};

Ball::Ball(int startX, int startY, int dx, int dy)
	: x(startX), y(startY), dx(dx), dy(dy) {}

bool Ball::move(const GameMap& map) {
	x += dx;
	y += dy;

	char tile = map.at(x, y);
	if (tile == '/' || tile == '\\') {
		reflect(tile);
	}
	else if (tile == GameMap::WALL) {
		return false;
	}
	return true;
}

void Ball::reflect(char mirror) {
	int oldDx = dx, oldDy = dy;
	if (mirror == '/') {
		dx = -oldDy;
		dy = -oldDx;
	}
	else if (mirror == '\\') {
		dx = oldDy;
		dy = oldDx;
	}
}
