#pragma once
#ifndef MUSIC_H_
#define MUSIC_H_

#include <SFML/Audio.hpp>


class Music
{
public:
	Music(const std::string& file_path, bool is_loop);
	~Music() = default;
	
	void Play();
	void Pause();
	void Stop();
	void SetVolume(float new_volume);
	
	sf::SoundSource::Status GetStatus() const;

private:
	sf::Music mMusic;
	std::string mFilePath;

};

#endif
