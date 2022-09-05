#include "SideBar.h"
#include "ResourcesManager.h"

SideBar::SideBar()
{
	//initializing texts and buttons:
	m_levelText.setFont(ResourcesManager::instance().getFont(Font::sideBarFont));
	m_levelText.setCharacterSize(55);
	m_levelText.setFillColor(sf::Color::Black);
	m_levelText.setPosition(100.f, 100.f);
	m_levelText.setString("Level: 1");

	m_stepsText.setFont(ResourcesManager::instance().getFont(Font::sideBarFont));
	m_stepsText.setCharacterSize(55);
	m_stepsText.setFillColor(sf::Color::Black);
	m_stepsText.setPosition(100.f, 200.f);
	m_stepsText.setString("Steps: 0");

	m_undo.setFont(ResourcesManager::instance().getFont(Font::sideBarFont));
	m_undo.setCharacterSize(40);
	m_undo.setFillColor(sf::Color::Black);
	m_undo.setPosition(75.f, 310.f);
	m_undo.setString("Undo");

	m_reset.setFont(ResourcesManager::instance().getFont(Font::sideBarFont));
	m_reset.setCharacterSize(40);
	m_reset.setFillColor(sf::Color::Black);
	m_reset.setPosition(205.f, 310.f);
	m_reset.setString("Reset");

}

void SideBar::draw(sf::RenderWindow& window) const
{
	window.draw(m_levelText);
	window.draw(m_stepsText);
	window.draw(m_undo);
	window.draw(m_reset);
}

void SideBar::setLevel(int level)
{
	m_levelText.setString("Level: " + std::to_string(level));
}

void SideBar::setSteps(int steps)
{
	m_stepsText.setString("Steps: " + std::to_string(steps));
}

//check whether the undo button was clicked: 
bool SideBar::checkUndoClick(sf::Vector2f clickPosition) const
{
	return m_undo.getGlobalBounds().contains(clickPosition);
}

//check whether the reset button was clicked:
bool SideBar::checkResetClick(sf::Vector2f clickPosition) const
{
	return m_reset.getGlobalBounds().contains(clickPosition);
}
