#pragma once

#include <SFML/Audio.hpp>


class SFX
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	std::string file_path;
	
public:
	SFX(const std::string& file_path);
	~SFX();
	void play();
	void pause();
	void stop();
};