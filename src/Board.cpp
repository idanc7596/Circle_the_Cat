#include "Board.h"
#include <queue>

Board::Board()
{
	//initializing the grid of hexagons:
	sf::Vector2f currPosition(420.f, 80.f);
	Hexagon exampleHexagon(currPosition, sf::Vector2i(0, 0)); //to know width and height
	float margin = 5.f; 

	for (int row = 0; row < SIZE; row++) {
		//indent every second row:
		currPosition.x = (row % 2 == 0) ? 420.f : 420.f + 0.5f* exampleHexagon.getWidth() + 0.5f* margin;
		//creating a row:
		m_grid.push_back(std::vector<Hexagon>());
		for (int col = 0; col < SIZE; col++) {
			Hexagon hexagon(currPosition, sf::Vector2i(col, row));
			m_grid[row].push_back(hexagon);
			currPosition.x += hexagon.getWidth() + margin;
		}
		currPosition.y += 0.8f*exampleHexagon.getHeight();
	}
}

void Board::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			m_grid[i][j].draw(window);
		}
	}
}

//check whether a hexagon in the given position was clicked:
bool Board::checkHexagonsClick(sf::Vector2f clickPosition, sf::Vector2f catPosition)
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (m_grid[i][j].checkClick(clickPosition, catPosition)) {
				m_lastBlockedPosition = sf::Vector2i(j, i);
				return true;
			}
		}
	}
	return false;
}

//returns the pixel-coordinates position of the hexagon in a given row-col position:
sf::Vector2f Board::getHexagonPosition(sf::Vector2i position) const
{
	return m_grid[position.y][position.x].getPosition(); 
}


//The main algorithm that helps us calculate the minimal path from the cat
//to one of the grid edges. Implementation of BFS algorithm that finds the minimal distances
//from the source (cat) to one of the edges.The first edge hexagon that discovered
//during the search of BFS is the closest to the cat, so we want the cat to go towards it.
//we assign each hexagon in the way a parent that discovered him, so we can restore the path
//backwards so the cat will know in which direction to go in order to reach the closest edge.
Direction Board::runBFS(sf::Vector2i catPosition, Direction currCatDirection) //x=col,y=row
{
	//the hexagon that the cat sits on:
	Hexagon* catHexagon = &m_grid[catPosition.y][catPosition.x];

	//initialization:
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			m_grid[row][col].setDistance(MAX_LENGTH_PATH);//set all tdistances to maximum
			m_grid[row][col].setParent(nullptr);
			if (m_grid[row][col].isBlocked()) { //blocked hexagons aren't relevant
				m_grid[row][col].setVisited(true);
			}
			else {
				m_grid[row][col].setVisited(false);
			}
		}
	}
	//the distance from the cat (source) to itself is 0:
	catHexagon->setDistance(0); 

	//initializing BFS queue:
	std::queue<Hexagon*> q;
	q.push(catHexagon);
	catHexagon->setVisited(true);

	Hexagon* curr = nullptr;
	while (!q.empty()) {
		//pop the first element from the queue:
		curr = q.front();
		q.pop();

		//if we reached an edge hexagon, we know for sure that it is the closest to
		//the cat so we found the destination and break:
		if (curr->isEdge()) {
			break;
		}

		//for the hexagon that was popped from queue, discover all its neighbours:
		for (int i = 0; i < NUM_OF_DIRECTIONS; i++) {
			sf::Vector2i neighbourPosition = getNeighbourPosition(curr->getIndexesPosition(), Direction(i));
			//only if the neighbour exists in the grid's bounds:
			if (neighbourPosition != ILLEGAL_POSITION) {
				Hexagon* neighbour = &m_grid[neighbourPosition.y][neighbourPosition.x];
				//if we still didn't discover him, insert him to the queue:
				if (!neighbour->isVisited()) {
					q.push(neighbour);
					neighbour->setVisited(true);
					//his distance is one more from the distance of who discovered him:
					neighbour->setDistance(curr->getDistance() + 1);
					neighbour->setParent(curr);
				}
			}
		}
	}

	//restore path backwards:
	Hexagon* tmp = curr;
	while (tmp && tmp->getParent() && tmp->getParent() != catHexagon) {
		tmp = tmp->getParent();
	} 
	//now tmp is the direct neighbour of the cat:
	Hexagon* nextStep = tmp;
	
	//check in which direction relatively to cat the next step is:
	for (int i = 0; i < NUM_OF_DIRECTIONS; i++) {
		sf::Vector2i neighbourPosition = getNeighbourPosition(catPosition, Direction(i));
		if (neighbourPosition != ILLEGAL_POSITION) {
			Hexagon* neighbour = &m_grid[neighbourPosition.y][neighbourPosition.x];
			if (neighbour == nextStep) {
				return Direction(i);
			}
		}
	}

	//the direction the cat should go through in order to get to the grid edges
	//as quickly as possible:
	return currCatDirection;

}

//check if the given position is in the board edges:
bool Board::isEdgePosition(sf::Vector2i position)
{
	return m_grid[position.y][position.x].isEdge();
}

//check wether this position is blocked from all of its sides on the board:
bool Board::isBlockedPosition(sf::Vector2i position)
{
	for (int i = 0; i < NUM_OF_DIRECTIONS; i++) {
		sf::Vector2i neighbourPosition = getNeighbourPosition(position, Direction(i));
		if (neighbourPosition != ILLEGAL_POSITION) {
			Hexagon* neighbour = &m_grid[neighbourPosition.y][neighbourPosition.x];
			if (!neighbour->isBlocked()) {
				return false;
			}
		}
	}
	return true;
}

//reset all blocked hexagons in the bord to free:
void Board::clearHexagons()
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			m_grid[i][j].setBlocked(false);
		}
	}
}

void Board::blockPosition(Location position)
{
	m_grid[position.y][position.x].setBlocked(true);
}

//get the row-col position of the neighbour of the given position in this direction.
//needed because we have 6 neighbours to each hexagon, and the calculations are different 
//according to row parity.
sf::Vector2i Board::getNeighbourPosition(sf::Vector2i position, Direction direction) 
{
	sf::Vector2i neighbourIndexesPosition;
	switch (direction) {
	case Direction::bottomLeft:
		neighbourIndexesPosition = (position.y % 2 == 0) ?
			position + sf::Vector2i(-1, 1) :
			position + sf::Vector2i(0, 1);
		break;
	case Direction::left:
		neighbourIndexesPosition = position + sf::Vector2i(-1, 0);
		break;
	case Direction::bottomRight:
		neighbourIndexesPosition = (position.y % 2 == 0) ?
			position + sf::Vector2i(0, 1) :
			position + sf::Vector2i(1, 1);
		break;
	case Direction::right:
		neighbourIndexesPosition = position + sf::Vector2i(1, 0);
		break;
	case Direction::topLeft:
		neighbourIndexesPosition = (position.y % 2 == 0) ?
			position + sf::Vector2i(-1, -1) :
			position + sf::Vector2i(0, -1);
		break;
	case Direction::topRight:
		neighbourIndexesPosition = (position.y % 2 == 0) ?
			position + sf::Vector2i(0, -1) :
			position + sf::Vector2i(1, -1);
		break;
	default:
		break;
	}

	if (inBounds(neighbourIndexesPosition)) {
		return neighbourIndexesPosition;
	}
	return ILLEGAL_POSITION;
}

sf::Vector2i Board::getLastBlockedPosition() const
{
	return m_lastBlockedPosition;
}

void Board::freeHexagon(sf::Vector2i position)
{
	m_grid[position.y][position.x].setBlocked(false);
}

bool Board::inBounds(sf::Vector2i position)
{
	return position.x >= 0 && position.x <= SIZE - 1 &&
		position.y >= 0 && position.y <= SIZE - 1;

}


