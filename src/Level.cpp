#include "Level.h"
#include "macros.h"
#include <set>
#include <iostream>

Level::Level(Board& board)
	: m_board(board), m_levelNum(0)
{
	generate(); 
}

void Level::generate()
{
	m_levelNum++;
	m_board.clearHexagons();
	
	//update the number of hexagons should be blocked according to the level number:
	int numOfBlocked = EASY_BLOCKED;
	switch (m_levelNum) {
	case 1:
		numOfBlocked = EASY_BLOCKED;
		break;
	case 2:
		numOfBlocked = MEDIUM_BLOCKED;
		break;
	case 3:
		numOfBlocked = HARD_BLOCKED;
		break;
	default:
		numOfBlocked = EASY_BLOCKED;
		break;
	}

	//generate random locations where the hexagons will be blocked
	std::set<Location> toBlock;
	for (int i = 0; i < numOfBlocked; i++) {
		std::pair<std::set<Location>::const_iterator, bool> p;
		do {
			Location location(rand() % SIZE, rand() % SIZE);
			if (location == Location(SIZE / 2, SIZE / 2)) {
				p.second = false;
				continue;
			}
			p = toBlock.insert(location);
		} while (!p.second);
	}

	//block the hexagons:
	for (auto &location : toBlock) {
		m_board.blockPosition(location);
	}
	
	
}

int Level::getLevelNum() const
{
	return m_levelNum;
}

void Level::setLevelNum(int levelNum)
{
	m_levelNum = levelNum;
}
