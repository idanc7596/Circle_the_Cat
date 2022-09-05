#include "Cat.h"
#include "ResourcesManager.h"
#include <iostream>

Cat::Cat(Board& board)
	: m_board(board),
	m_position(SIZE / 2, SIZE / 2), //the middle of the grid
	m_direction(Direction::right), //dummy
	m_needToMove(false),
	m_free(false)
{
	//initialize the sprite of the cat:
	m_sprite.setTexture(ResourcesManager::instance().getTexture(Texture::cat));
	m_sprite.setTextureRect(sf::IntRect(5 * SPRITE_DIMENSION,
			3 * SPRITE_DIMENSION, SPRITE_DIMENSION, SPRITE_DIMENSION));
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
		m_sprite.getTextureRect().height / 2.f);
	m_sprite.setPosition(m_board.getHexagonPosition(m_position));

}

void Cat::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::Vector2f Cat::getPosition() const
{
	return m_sprite.getPosition();
}

//the intended location by row and col:
sf::Vector2i Cat::getNextPosition() const
{
	return m_nextPosition;
}

void Cat::setPosition(sf::Vector2i position)
{
	m_position = position;
	m_sprite.setPosition(m_board.getHexagonPosition(m_position));
}

void Cat::move()
{
	if (m_needToMove) {
		//for animation:
		m_sprite.setTextureRect(sf::IntRect(m_offset.x * SPRITE_DIMENSION,
			m_offset.y * SPRITE_DIMENSION, SPRITE_DIMENSION, SPRITE_DIMENSION));
		m_sprite.setOrigin(m_sprite.getTextureRect().width / 2.f,
			m_sprite.getTextureRect().height / 2.f);
		//curent cat position:
		sf::Vector2f position = m_board.getHexagonPosition(m_position);
		//next cat position:
		sf::Vector2f nextPosition = m_board.getHexagonPosition(m_nextPosition);
		//move one frame in the sprite sheet:
		float deltaX = nextPosition.x - position.x; 
		float deltaY = nextPosition.y - position.y;
		m_sprite.move(deltaX / NUM_OF_FRAMES, deltaY / NUM_OF_FRAMES);
		
		m_offset.x++; //change frame

		//animation end:
		if (m_offset.x == NUM_OF_FRAMES) {
			m_needToMove = false;
			m_position = m_nextPosition;
			if (m_board.isEdgePosition(m_position)) {
				m_free = true; //cat was able to run away
			}
		}
	}
}

void Cat::setDirection() 
{
	m_offset.x = 0; //first frame

	//find direction and next position by finding the shortest path to edge using BFS:
	m_direction = m_board.runBFS(m_position, m_direction);
	m_nextPosition = m_board.getNeighbourPosition(m_position, m_direction);
	//to know the appropriate line in the sprite sheet:
	m_offset.y = int(m_direction); 
}

void Cat::reset()
{
	m_needToMove = false;
	m_free = false;
	//sprite sheet initialization:
	m_sprite.setTextureRect(sf::IntRect(5 * SPRITE_DIMENSION,
		3 * SPRITE_DIMENSION, SPRITE_DIMENSION, SPRITE_DIMENSION));
}


void Cat::needToMove(bool needToMove)
{
	m_needToMove = needToMove;
}

bool Cat::isNeedToMove() const
{
	return m_needToMove;
}

bool Cat::isFree() const
{
	return m_free;
}

//is cat surrounded:
bool Cat::isBlocked() const
{
	return m_board.isBlockedPosition(m_position);
}


