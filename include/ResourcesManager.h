#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class Sound {
	win,
	lose,
	meow
};

enum class Font {
	sideBarFont
};

enum class Texture {
	background,
	cat,
	hexagon,
	blockedHexagon,
	gameWin,
	levelWin,
	levelLose
};

//a singleton class for storing game resources - textures, fonts, sounds and musics:
class ResourcesManager {
public:
	~ResourcesManager() = default;
	static ResourcesManager& instance();

	const sf::Texture& getTexture(Texture id) const;
	const sf::Font& getFont(Font id) const;
	void playSound(Sound id);
	void playGameMusic();

	

private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = default;
	ResourcesManager& operator=(const ResourcesManager&) = default;

	void initTextures();
	void initFonts();
	void initSounds();
	void initMusics();

	std::vector<sf::Texture> m_textures;
	std::vector<sf::Font> m_fonts;
	std::vector<sf::SoundBuffer> m_soundBuffers;
	std::vector<sf::Sound> m_sounds;
	sf::Music m_gameMusic;

};