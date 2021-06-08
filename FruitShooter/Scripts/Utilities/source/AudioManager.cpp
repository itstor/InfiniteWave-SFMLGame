#include "AudioManager.h"

#include <iostream>

#include "Music.h"
#include "Config.h"

AudioManager::AudioManager()
{
#ifdef _DEBUG
	std::cout << "Audio Manager Created\n";
#endif
}

void AudioManager::addMusic(const std::string& musicName, const std::string& file_path, bool isLoop)
{
	musicContainer[musicName] = new Music(file_path, isLoop);
}


void AudioManager::toggleMute()
{
	conf::isMuted = !conf::isMuted;

	//MUSIC VOLUME
	conf::temp_musicVolume = conf::isMuted ? conf::musicVolume : conf::temp_musicVolume;
	conf::musicVolume = conf::isMuted ? 0.0f : conf::temp_musicVolume;

	//SFX VOLUME
	conf::temp_sfxVolume = conf::isMuted ? conf::sfxVolume : conf::temp_sfxVolume;
	conf::sfxVolume = conf::isMuted ? 0.0f : conf::temp_sfxVolume;

	//std::cout << conf::musicVolume << " " << conf::temp_musicVolume << std::endl;

	return updateVolume(conf::musicVolume);
}

void AudioManager::increase_volume()
{
	conf::musicVolume++;
	return updateVolume();
}

void AudioManager::decrease_volume()
{
	conf::musicVolume--;
	return updateVolume();
}


void AudioManager::updateVolume()
{
	return updateVolume(conf::musicVolume);
}


void AudioManager::updateVolume(float& newVolume)
{
	for (auto&[name, music] : musicContainer)
	{
		music->setVolume(newVolume);
	}
}

void AudioManager::play(const std::string & music_name)
{
	//std::cout << "Playing " << music_name << std::endl;
	musicContainer[music_name]->play();
}
