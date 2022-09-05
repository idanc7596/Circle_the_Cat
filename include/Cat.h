#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "macros.h"


class Cat {
public:
	Cat(Board& board);
	void draw(sf::RenderWindow &window) const;
	sf::Vector2f getPosition() const;
	sf::Vector2i getNextPosition() const;
	void setPosition(sf::Vector2i position);

	void move();
	void setDirection();
	void reset();

	void needToMove(bool needToMove);
	bool isNeedToMove() const; 
	bool isFree() const;
	bool isBlocked() const;


private:
	Board& m_board;
	sf::Sprite m_sprite;
	sf::Vector2i m_position; //row and col of hexagon that the cat on it
	sf::Vector2i m_nextPosition; //the intended location by row and col
	Direction m_direction; 
	sf::Vector2i m_offset; //in use in the animation of the cat
	bool m_needToMove;
	bool m_free; //Did the cat run away
};