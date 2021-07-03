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

void AudioManager::AddMusic(const std::string& music_name, const std::string& file_path, bool is_loop)
{
	mMusicContainer[music_name] = new Music(file_path, is_loop);
}

void AudioManager::AddSFX(const std::string& sfx_name, const std::string& file_path)
{
	mSFXContainer[sfx_name] = new SFX(file_path);
}


void AudioManager::ToggleMute()
{
	conf::gIsMuted = !conf::gIsMuted;

	//MUSIC VOLUME
	conf::gTempMusicVolume = conf::gIsMuted ? conf::gMusicVolume : conf::gTempMusicVolume;
	conf::gMusicVolume = conf::gIsMuted ? 0.0f : conf::gTempMusicVolume;

	//SFX VOLUME
	conf::gTempSFXVolume = conf::gIsMuted ? conf::gSFXVolume : conf::gTempSFXVolume;
	conf::gSFXVolume = conf::gIsMuted ? 0.0f : conf::gTempSFXVolume;

	//std::cout << conf::musicVolume << " " << conf::temp_musicVolume << std::endl;

	return UpdateVolume(conf::gMusicVolume);
}

void AudioManager::StopAllMusic()
{
	for (auto&[name, music]:mMusicContainer)
	{
		music->Stop();
	}
}

void AudioManager::StopMusic(const std::string & music_name)
{
	mMusicContainer[music_name]->Stop();
}

void AudioManager::SetMusicVolume(const std::string& music_name, float volume)
{
	mMusicContainer[music_name]->SetVolume(volume);
}

sf::Sound::Status AudioManager::GetMuicStatus(const std::string & music_name)
{
	return mMusicContainer[music_name]->GetStatus();
}


void AudioManager::IncreaseVolume()
{
	conf::gMusicVolume++;
	return UpdateVolume();
}

void AudioManager::DecreaseVolume()
{
	conf::gMusicVolume--;
	return UpdateVolume();
}


void AudioManager::UpdateVolume()
{
	return UpdateVolume(conf::gMusicVolume);
}


void AudioManager::UpdateVolume(float new_volume)
{
	for (auto&[name, music] : mMusicContainer)
	{
		music->SetVolume(new_volume);
	}
}

void AudioManager::PlayMusic(const std::string & music_name)
{
#ifdef _DEBUG
	std::cout << "Playing " << music_name << std::endl;
#endif
	mMusicContainer[music_name]->Play();
}

void AudioManager::PlaySFX(const std::string& sfx_name)
{
#ifdef _DEBUG
	std::cout << "Playing SFX " << sfx_name << std::endl;
#endif
	mSFXContainer[sfx_name]->Play();
}

void AudioManager::SetSFXPitch(const std::string& sfx_name, float pitch)
{
	mSFXContainer[sfx_name]->SetPitch(pitch);
}

sf::SoundBuffer* AudioManager::GetSoundBuffer(const std::string& sfx_name)
{
	return &*mSFXContainer[sfx_name]->GetSoundBuffer();
}