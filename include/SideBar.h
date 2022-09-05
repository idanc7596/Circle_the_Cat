#pragma once
#include <SFML/Graphics.hpp>


class SideBar {
public:
	SideBar();
	void draw(sf::RenderWindow& window) const;
	void setLevel(int level);
	void setSteps(int steps);
	bool checkUndoClick(sf::Vector2f clickPosition) const;
	bool checkResetClick(sf::Vector2f clickPosition) const;


private:
	sf::Text m_levelText;
	sf::Text m_stepsText;
	sf::Text m_undo; //undo button
	sf::Text m_reset; //reset button
};