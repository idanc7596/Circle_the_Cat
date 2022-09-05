#include "Controller.h"
#include "Hexagon.h"
#include "ResourcesManager.h"
#include <iostream>

Controller::Controller()
	:m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Circle the Cat", sf::Style::Close),
	m_board(),
	m_sideBar(),
	m_cat(m_board),
	m_steps(0),
	m_level(m_board)
{
	//set icon for the game:
	sf::Image icon;
	icon.loadFromFile("resources/catIcon.png");
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	//set background for the game:
	m_background.setTexture(ResourcesManager::instance().getTexture(Texture::background));
}

//the main loop of the game:
void Controller::run()
{
	ResourcesManager::instance().playGameMusic();

	m_window.setFramerateLimit(FPS);
	while (m_window.isOpen()) {

		handleEvents();
		
		m_cat.move();

		draw();

		//cat was able to run away, player failed:
		if (m_cat.isFree()) { 
			ResourcesManager::instance().playSound(Sound::lose);
			showTransitionScreen(TransitionScreen::levelLose);
			reset();
		}
		//cat is surrounded, player won the level:
		else if (m_cat.isBlocked()) {
			ResourcesManager::instance().playSound(Sound::win);
			//player didn't finish all the levels yet:
			if (m_level.getLevelNum() != NUM_OF_LEVELS) {
				showTransitionScreen(TransitionScreen::levelWin);
			}
			initLevel();
		}


	}

}

void Controller::initLevel()
{
	//last level finished, player won the game:
	if (m_level.getLevelNum() == NUM_OF_LEVELS) { 
		showTransitionScreen(TransitionScreen::gameWin);
		m_level.setLevelNum(0);
	}
	reset();
	//generate new level:
	m_level.generate(); 
	m_sideBar.setLevel(m_level.getLevelNum());
}

void Controller::handleEvents()
{
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		switch (ev.type) {
			case sf::Event::Closed:
				m_window.close();
				exit(EXIT_SUCCESS);
				break;
			case sf::Event::MouseButtonReleased:
				auto click = ev.mouseButton;

				//hexagon was clicked:
				if(!m_cat.isNeedToMove() && m_board.checkHexagonsClick(m_window.mapPixelToCoords({click.x, click.y}),
											m_cat.getPosition())) {
					if (m_steps%3 == 0) {
						ResourcesManager::instance().playSound(Sound::meow); 
					}
					m_steps++;
					m_sideBar.setSteps(m_steps);
					m_cat.setDirection();
					m_cat.needToMove(true);
					//insert the current step into the history stack:
					//the information about the step includes cat intended location, 
					//and last blocked hexagon location
					Step currStep(m_cat.getNextPosition(), m_board.getLastBlockedPosition());
					m_history.push(currStep);
				}
				if (m_sideBar.checkUndoClick(m_window.mapPixelToCoords({ click.x, click.y }))) {
					if (!m_history.empty()) {
						undo();
					}
				}
				if (m_sideBar.checkResetClick(m_window.mapPixelToCoords({ click.x, click.y }))) {
					reset();
				}
				break;
			default:
				break;

		}
	}
}

//Implementat undo using a stack of hisory steps,
//the information about a step includes cat location, 
//and last blocked hexagon location
void Controller::undo()
{
	m_steps--;
	m_sideBar.setSteps(m_steps);
	Step lastStep = m_history.top();
	m_history.pop();
	//free the last blocked hexagon:
	m_board.freeHexagon(lastStep.blockedHexagonPosition); 
	//if stack is empty return the cat to the initial position:
	if (m_history.empty()) {
		m_cat.setPosition(sf::Vector2i(SIZE / 2, SIZE / 2));
	}
	//return the cat to the last position:
	else {
		m_cat.setPosition(m_history.top().catPosition);
	}
}

//rest the level using 'undo':
void Controller::reset() {
	while (!m_history.empty()) {
		undo();
	}
	m_cat.reset();
}

void Controller::draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);

	m_sideBar.draw(m_window);
	m_board.draw(m_window);
	m_cat.draw(m_window);
	
	m_window.display();
}

void Controller::showTransitionScreen(TransitionScreen type)
{
	sf::Sprite transitionScreen;

	//update the transition screen textrue:
	switch (type) {
	case TransitionScreen::gameWin:
		transitionScreen.setTexture(ResourcesManager::instance().getTexture(Texture::gameWin));
		break;
	case TransitionScreen::levelWin:
		transitionScreen.setTexture(ResourcesManager::instance().getTexture(Texture::levelWin));
		break;
	case TransitionScreen::levelLose:
		transitionScreen.setTexture(ResourcesManager::instance().getTexture(Texture::levelLose));
		break;
	default:
		break;
	}

	//display the transition screen for TRANSITION_SCREEN_TIME seconds:
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() < TRANSITION_SCREEN_TIME) {
		m_window.clear();
		m_window.draw(transitionScreen);
		m_window.display();
	}
}
