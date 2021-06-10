#pragma once

#include <SFML/Audio.hpp>

class Music
{
private:
	sf::Music music;
	std::string file_path;

public:
	Music(const std::string& file_path, const bool& isLoop);
	~Music() = default;
	
	void play();
	void pause();
	void stop();
	void setVolume(float& newVolume);
	sf::SoundSource::Status getStatus() const;
};


