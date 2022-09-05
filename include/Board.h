#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "macros.h"
#include "Hexagon.h"

class Board {
public:
	Board();
	void draw(sf::RenderWindow& window) const;

	bool checkHexagonsClick(sf::Vector2f clickPosition, sf::Vector2f catPosition);
	sf::Vector2f getHexagonPosition(sf::Vector2i position) const;
	sf::Vector2i getNeighbourPosition(sf::Vector2i position, Direction direction);
	sf::Vector2i getLastBlockedPosition() const;
	void freeHexagon(sf::Vector2i position);

	Direction runBFS(sf::Vector2i catPosition, Direction currCatDirection);
	bool isEdgePosition(sf::Vector2i position);
	bool isBlockedPosition(sf::Vector2i position);
	void clearHexagons(); 
	void blockPosition(Location position);

private:
	bool inBounds(sf::Vector2i position);
	sf::Vector2i m_lastBlockedPosition;

	std::vector<std::vector<Hexagon>> m_grid;

};