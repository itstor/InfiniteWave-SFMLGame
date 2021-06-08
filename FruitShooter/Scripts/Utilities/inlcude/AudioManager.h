#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <unordered_map>

class Music;

class AudioManager
{
private:
	std::unordered_map<std::string, Music*> musicContainer;
public:
	AudioManager();

	void addMusic(const std::string& musicName, const std::string& file_path, bool isLoop);
	void updateVolume();
	void updateVolume(float& newVolume);
	void decrease_volume();
	void increase_volume();
	void play(const std::string& music_name);
	void toggleMute();
};

#endif
