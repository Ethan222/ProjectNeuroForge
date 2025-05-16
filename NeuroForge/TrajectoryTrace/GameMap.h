#pragma once
#include <iostream>
#include <cstdlib> // For srand() and rand()
#include <ctime>   // For time()
#include <cassert>
#include <stdexcept>

class GameMap {
public:
    static constexpr char WALL = '#', EMPTY = '.', BALL = '*', GUESS = 'X';

    GameMap(int width = 7, int height = 7);
    ~GameMap();

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    char at(int x, int y) const;
    void display(bool empty = false, int ballX = -1, int ballY = -1) const;

    void generateRandomLayout();
    void setGuess(int x, int y);

private:
    static constexpr int MIRROR_PROB = 30;  // % chance for a mirror (either direction)

    int width, height;
    char* grid;

    void set(int x, int y, char value);
};

GameMap::GameMap(int width, int height) : width(width), height(height)
{
    assert(width > 0 && height > 0);
    grid = new char[width * height];

    // walls
    for (int x = 0; x < width; ++x) {
        set(x, 0, WALL);            // top
        set(x, height - 1, WALL);   // bottom
    }
    for (int y = 1; y < height - 1; ++y) {
        set(0, y, WALL);            // left
        set(width - 1, y, WALL);    // right
    }
}

inline GameMap::~GameMap() {
    delete[] grid;
}

void GameMap::generateRandomLayout()
{
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(0)));
        seeded = true;
    }

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int randomNum = rand() % 100;
            if (randomNum < MIRROR_PROB / 2) set(x, y, '/');
            else if (randomNum < MIRROR_PROB) set(x, y, '\\');
            else set(x, y, EMPTY);
        }
    }
}

inline void GameMap::setGuess(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || at(x, y) != '#')
        throw std::invalid_argument("Invalid guess");
    set(x, y, GUESS);
}

inline char GameMap::at(int x, int y) const
{
    assert(x >= 0 && x < width && y >= 0 && y < height);
    return grid[y * width + x];
}

void GameMap::display(bool empty, int ballX, int ballY) const
{
    std::cout << "  ";
    for (int x = 0; x < width; ++x) {
        std::cout << x;
    }
    std::cout << '\n';
    for (int y = 0; y < height; ++y) {
        std::cout << y << ' ';
        for (int x = 0; x < width; ++x) {
            if (x == ballX && y == ballY) std::cout << BALL;
            else {
                char tile = at(x, y);
                if (empty && tile != '#') std::cout << EMPTY;
                else std::cout << tile;
            }
        }
        std::cout << '\n';
    }
}

inline void GameMap::set(int x, int y, char value)
{
    assert(x >= 0 && x < width && y >= 0 && y < height);
    grid[y * width + x] = value;
}
