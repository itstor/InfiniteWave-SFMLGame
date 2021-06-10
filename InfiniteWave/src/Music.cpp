#include "Music.h"
#include <iostream>

Music::Music(const std::string& file_path, const bool& isLoop)
{
#ifdef _DEBUG
	std::cout << "Music Created " << file_path << std::endl;
#endif
	
	this->file_path = file_path;

	if (!music.openFromFile(this->file_path))
		std::cout << "File not found" << std::endl;

	music.setLoop(isLoop);
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



