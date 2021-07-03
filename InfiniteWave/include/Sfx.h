#pragma once
#ifndef SFX_H_
#define SFX_H_

#include <SFML/Audio.hpp>


class SFX
{	
public:
	SFX(const std::string& file_path);
	~SFX() = default;
	
	void Play();
	void Pause();
	void Stop();
	void SetPitch(float new_pitch);

	sf::SoundBuffer* GetSoundBuffer();

private:
	sf::SoundBuffer mSoundBuffer;
	sf::Sound mSound;
	std::string mFilePath;
};

#endif