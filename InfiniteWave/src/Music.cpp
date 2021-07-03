#include "Music.h"

Music::Music(const std::string& file_path, bool is_loop)
{	
	this->mFilePath = file_path;

	mMusic.openFromFile(this->mFilePath);

	mMusic.setLoop(is_loop);
}

void Music::Play()
{
	//music.setVolume(conf::musicVolume);
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



