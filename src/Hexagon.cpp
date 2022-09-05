#include "Hexagon.h"
#include "ResourcesManager.h"

Hexagon::Hexagon(sf::Vector2f position, sf::Vector2i indexesPosition)
	: m_shape(sf::CircleShape(45.f, 6)), //hexagon shape
	m_isBlocked(false),
	m_indexesPosition(indexesPosition),
	m_distance(MAX_LENGTH_PATH),
	m_visited(false),
	m_parent(nullptr)
{
	m_shape.setTexture(&ResourcesManager::instance().getTexture(Texture::hexagon));
	m_shape.setPosition(position);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
}

void Hexagon::draw(sf::RenderWindow& window) const
{
	window.draw(m_shape);
}

float Hexagon::getWidth() const
{
	return m_shape.getGlobalBounds().width;
}

float Hexagon::getHeight() const
{
	return m_shape.getGlobalBounds().height;
}

sf::Vector2f Hexagon::getPosition() const
{
	return m_shape.getPosition();
}

//position of the hexagon by indexes 
//(indexes x=col,y=row in the 2 dimensional vector of hexagons (in board):
sf::Vector2i Hexagon::getIndexesPosition() const
{
	return m_indexesPosition;
}

//use in bfs:
void Hexagon::setDistance(int distance)
{
	m_distance = distance;
}

int Hexagon::getDistance() const
{
	return m_distance;
}

//in use in bfs:
void Hexagon::setVisited(bool visited)
{
	m_visited = visited;
}

bool Hexagon::isVisited() const
{
	return m_visited;
}

//in use in bfs:
Hexagon* Hexagon::getParent() const
{
	return m_parent;
}

void Hexagon::setParent(Hexagon* parent)
{
	m_parent = parent;
}

//check if hexagon was clicked:
bool Hexagon::checkClick(sf::Vector2f clickPosition, sf::Vector2f catPosition)
{
	
	if (!m_isBlocked && !m_shape.getGlobalBounds().contains(catPosition) &&
		//distance between the clicked position and the cat position:
		std::sqrt(std::pow(clickPosition.y-m_shape.getPosition().y,2)+
				  std::pow(clickPosition.x-m_shape.getPosition().x,2))
		<= m_shape.getRadius()) {
		//the hexagon was clicked:
		this->setBlocked(true);
		return true; 
	}
	return false;
}

bool Hexagon::isBlocked() const
{
	return m_isBlocked;
}

bool Hexagon::isEdge() const
{
	return m_indexesPosition.x == 0 || m_indexesPosition.x == SIZE-1 ||
		m_indexesPosition.y == 0 || m_indexesPosition.y == SIZE-1;
}

void Hexagon::setBlocked(bool blocked)
{
	m_isBlocked = blocked;

	//update the texture of the hexagon:
	if (blocked) {
		m_shape.setTexture(&ResourcesManager::instance().getTexture(Texture::blockedHexagon));
	}
	else {
		m_shape.setTexture(&ResourcesManager::instance().getTexture(Texture::hexagon));
	}
}




