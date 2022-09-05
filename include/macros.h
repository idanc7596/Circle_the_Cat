#pragma once
#include <SFML/Graphics.hpp>

const int SIZE = 11, //board height and width
NUM_OF_DIRECTIONS = 6,
NUM_OF_FRAMES = 7, //in the cat spritesheet
SPRITE_DIMENSION = 75, //in the cat spritesheet
WINDOW_HEIGHT = 900,
WINDOW_WIDTH = 1400,
FPS = 10,
MAX_LENGTH_PATH = SIZE * SIZE,
//num of blocked hexagon in each level:
EASY_BLOCKED = 14,
MEDIUM_BLOCKED = 9,
HARD_BLOCKED = 5,
NUM_OF_LEVELS = 3,
TRANSITION_SCREEN_TIME = 2;

const sf::Vector2i ILLEGAL_POSITION(-1, -1);

enum class Direction {
	bottomLeft,
	left,
	bottomRight,
	right,
	topLeft,
	topRight
};

enum class TransitionScreen {
	gameWin,
	levelWin, 
	levelLose
};

struct Location {
	int x, y;
	bool operator <(const Location& loc) const {
		return (x < loc.x) || ((!(loc.x < x)) && (y < loc.y));
	}
	bool operator ==(const Location& loc) const {
		return x == loc.x && y == loc.y;
	}
	bool operator !=(const Location& loc) const {
		return !(*this==loc);
	}
};

