#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Board.h"
#include "SideBar.h"
#include "Cat.h"
#include "Level.h"
#include "macros.h"

class Controller {
public:
	Controller();
	void run();
	

private:
	void draw();

	void handleEvents();
	void undo();
	void reset();
	void initLevel();
	void showTransitionScreen(TransitionScreen type);

	sf::RenderWindow m_window;
	sf::Sprite m_background;
	Board m_board;
	SideBar m_sideBar;
	Cat m_cat;

	Level m_level;
	int m_steps;

	struct Step {
		sf::Vector2i catPosition;
		sf::Vector2i blockedHexagonPosition;
	};
	std::stack<Step> m_history; //in use in implementation of 'undo'

};