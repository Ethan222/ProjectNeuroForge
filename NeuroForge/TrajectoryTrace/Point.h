#pragma once
#include <iostream>

struct Point {
	int x, y;
	Point(int x = 0, int y = 0) : x(x), y(y) {}
	friend std::istream& operator>>(std::istream&, Point&);
	friend std::ostream& operator<<(std::ostream&, const Point&);
	bool operator==(const Point& other);
};

inline std::istream& operator>>(std::istream& in, Point& p)
{
	in >> p.x >> p.y;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
	out << '(' << p.x << ", " << p.y << ')';
	return out;
}

bool Point::operator==(const Point& other)
{
	return x == other.x && y == other.y;
}
