#include "Music.h"
#include <iostream>

Music::Music(const std::string& file_path, const bool& isLoop)
{
	this->file_path = file_path;

	if (!music.openFromFile(this->file_path))
		std::cout << "File not found" << std::endl;
}

void Music::play()
{
	//music.setVolume(conf::musicVolume);
	std::cout << "Music Played\n";
	music.play();
}

void Music::pause()
{
	music.pause();
}

void Music::stop()
{
	music.stop();
}

void Music::setVolume(float& newVolume)
{
	music.setVolume(newVolume);
}

sf::SoundSource::Status Music::getStatus() const
{
	return music.getStatus();
}



