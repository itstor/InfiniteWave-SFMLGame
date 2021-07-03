#pragma once
#ifndef AUDIO_MANAGER_H_
#define AUDIO_MANAGER_H_

#include <unordered_map>
#include <SFML/Audio/Sound.hpp>

class SFX;
class Music;


class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void AddMusic(const std::string& music_name, const std::string& file_path, bool is_loop);
	void AddSFX(const std::string& sfx_name, const std::string& file_path);
	void PlayMusic(const std::string& music_name);
	void PlaySFX(const std::string& sfx_name);
	void UpdateVolume();
	void UpdateVolume(float new_volume);
	void DecreaseVolume();
	void IncreaseVolume();
	void ToggleMute();
	void StopAllMusic();
	void StopMusic(const std::string& music_name);
	
	void SetSFXPitch(const std::string& sfx_name, float pitch);
	void SetMusicVolume(const std::string& music_name, float volume);

	sf::SoundBuffer* GetSoundBuffer(const std::string& sfx_name);
	sf::Sound::Status GetMuicStatus(const std::string& music_name);

private:
	std::unordered_map<std::string, Music*> mMusicContainer;
	std::unordered_map<std::string, SFX*> mSFXContainer;
};

#endif
