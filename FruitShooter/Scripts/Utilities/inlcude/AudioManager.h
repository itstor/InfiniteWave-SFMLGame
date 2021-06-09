#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <unordered_map>

class SFX;
class Music;

class AudioManager
{
private:
	std::unordered_map<std::string, Music*> musicContainer;
	std::unordered_map<std::string, SFX*> SFXContainer;
public:
	AudioManager();
	~AudioManager();

	void addMusic(const std::string& musicName, const std::string& file_path, bool isLoop);
	void addSFX(const std::string& sfxName, const std::string& file_path);
	void updateVolume();
	void updateVolume(float& newVolume);
	void decrease_volume();
	void increase_volume();
	void play(const std::string& music_name);
	void playSFX(const std::string& sfx_name);
	void toggleMute();
	void stopAll();
};

#endif
