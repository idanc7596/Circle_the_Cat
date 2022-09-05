#pragma once
#include <SFML/Graphics.hpp>
#include "macros.h"

class Hexagon {
public:
	Hexagon(sf::Vector2f position, sf::Vector2i indexesPosition);
	void draw(sf::RenderWindow& window) const;
	float getWidth() const;
	float getHeight() const;
	sf::Vector2f getPosition() const;
	sf::Vector2i getIndexesPosition() const;
	void setDistance(int distance);
	int getDistance() const;
	void setVisited(bool visited); 
	bool isVisited() const;
	Hexagon* getParent() const;
	void setParent(Hexagon* parent);


	bool checkClick(sf::Vector2f clickPosition, sf::Vector2f catPosition);
	bool isBlocked() const;
	bool isEdge() const;
	void setBlocked(bool blocked);

private:
	sf::CircleShape m_shape;
	bool m_isBlocked;

	//position of the hexagon by indexes 
	//(indexes x=col,y=row in the 2 dimensional vector of hexagons (in board):
	sf::Vector2i m_indexesPosition; 

	//bfs data:
	int m_distance;
	bool m_visited;
	Hexagon* m_parent; 

};