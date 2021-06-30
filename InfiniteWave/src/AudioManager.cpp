#include "AudioManager.h"

#include <iostream>

#include "Music.h"
#include "Config.h"
#include "Sfx.h"

AudioManager::AudioManager()
{
#ifdef _DEBUG
	std::cout << "Audio Manager Created\n";
#endif
}

AudioManager::~AudioManager()
{
#ifdef _DEBUG
	std::cout << "Audio Manager Destroyed\n";
#endif
}

void AudioManager::addMusic(const std::string& musicName, const std::string& file_path, bool isLoop)
{
	musicContainer[musicName] = new Music(file_path, isLoop);
}

void AudioManager::addSFX(const std::string& sfxName, const std::string& file_path)
{
	SFXContainer[sfxName] = new SFX(file_path);
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

void AudioManager::stopAll()
{
	for (auto&[name, music]:musicContainer)
	{
		music->stop();
	}
}

void AudioManager::stopMusic(const std::string & music_name)
{
	musicContainer[music_name]->stop();
}

void AudioManager::setMusicVolume(const std::string& music_name, float volume)
{
	musicContainer[music_name]->setVolume(volume);
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


void AudioManager::updateVolume(float newVolume)
{
	for (auto&[name, music] : musicContainer)
	{
		music->setVolume(newVolume);
	}
}

void AudioManager::play(const std::string & music_name)
{
#ifdef _DEBUG
	std::cout << "Playing " << music_name << std::endl;
#endif
	musicContainer[music_name]->play();
}

void AudioManager::playSFX(const std::string& sfx_name)
{
#ifdef _DEBUG
	std::cout << "Playing SFX " << sfx_name << std::endl;
#endif
	SFXContainer[sfx_name]->play();
}

void AudioManager::changeSFXPitch(const std::string& sfx_name, float pitch)
{
	SFXContainer[sfx_name]->setPitch(pitch);
}

sf::SoundBuffer* AudioManager::getSoundBuffer(const std::string& sfx_name)
{
	return &*SFXContainer[sfx_name]->getSoundBuffer();
}