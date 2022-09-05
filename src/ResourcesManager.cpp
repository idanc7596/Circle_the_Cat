#include "ResourcesManager.h"
#include <iostream>

ResourcesManager::ResourcesManager() {
	initTextures();
	initFonts();
	initSounds();
	initMusics();
}

ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance;
	return instance;
}

//get the relevent texture according to the enum value passed:
const sf::Texture& ResourcesManager::getTexture(Texture id) const
{
	return m_textures[int(id)];
}

//get the relevent font according to the enum value passed:
const sf::Font& ResourcesManager::getFont(Font id) const
{
	return m_fonts[int(id)];
}

//play the relevent sound according to the enum value passed:
void ResourcesManager::playSound(Sound id)
{
	m_sounds[int(id)].play();
}

void ResourcesManager::playGameMusic()
{
	m_gameMusic.play();
}

void ResourcesManager::initTextures()
{
	sf::Texture background;
	background.loadFromFile("resources/background.png");
	m_textures.push_back(background);

	sf::Texture cat;
	cat.loadFromFile("resources/cat.png");
	m_textures.push_back(cat);

	sf::Texture hexagon;
	hexagon.loadFromFile("resources/hexagon.png");
	m_textures.push_back(hexagon);

	sf::Texture blockedHexagon;
	blockedHexagon.loadFromFile("resources/blockedHexagon.png");
	m_textures.push_back(blockedHexagon);
	
	sf::Texture gameWin;
	gameWin.loadFromFile("resources/gameWin.png");
	m_textures.push_back(gameWin);

	sf::Texture levelWin;
	levelWin.loadFromFile("resources/levelWin.png");
	m_textures.push_back(levelWin);

	sf::Texture levelLose;
	levelLose.loadFromFile("resources/levelLose.png");
	m_textures.push_back(levelLose);
}

void ResourcesManager::initFonts()
{
	sf::Font sideBarFont;
	sideBarFont.loadFromFile("resources/Austein.ttf");
	m_fonts.push_back(sideBarFont);
}

void ResourcesManager::initSounds()
{
	sf::SoundBuffer win;
	win.loadFromFile("resources/winSound.wav");

	sf::SoundBuffer lose;
	lose.loadFromFile("resources/loseSound.wav");

	sf::SoundBuffer meow;
	meow.loadFromFile("resources/meowSound.wav");

	m_soundBuffers.push_back(win);
	m_soundBuffers.push_back(lose);
	m_soundBuffers.push_back(meow);

	for (int i = 0; i < m_soundBuffers.size(); i++) {
		sf::Sound sound(m_soundBuffers[i]);
		m_sounds.push_back(sound);
	}

	m_sounds[int(Sound::meow)].setVolume(50.f);

}

void ResourcesManager::initMusics()
{
	m_gameMusic.openFromFile("resources/gameMusic.wav");
	m_gameMusic.setLoop(true);
	m_gameMusic.setVolume(50.f);
}

