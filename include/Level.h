#pragma once
#include "Board.h"

class Level {
public:
	Level(Board& board);
	void generate();
	int getLevelNum() const;
	void setLevelNum(int levelNum);

private:
	int m_levelNum;
	Board& m_board;

};