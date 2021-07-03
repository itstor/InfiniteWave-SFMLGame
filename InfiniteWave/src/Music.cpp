#include "Music.h"
#include <iostream>

Music::Music(const std::string& file_path, bool is_loop)
{
#ifdef _DEBUG
	std::cout << "Music Created " << file_path << std::endl;
#endif
	
	this->mFilePath = file_path;

	if (!mMusic.openFromFile(this->mFilePath))
		std::cout << "File not found" << std::endl;

	mMusic.setLoop(is_loop);
}

void Music::Play()
{
	//music.setVolume(conf::musicVolume);
	std::cout << "Music Played\n";
	mMusic.play();
}

void Music::Pause()
{
	mMusic.pause();
}

void Music::Stop()
{
	mMusic.stop();
}

void Music::SetVolume(float new_volume)
{
	mMusic.setVolume(new_volume);
}

sf::SoundSource::Status Music::GetStatus() const
{
	return mMusic.getStatus();
}



