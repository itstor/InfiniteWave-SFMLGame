#include "Sfx.h"
#include "Config.h"
#include <iostream>

SFX::SFX(const std::string& file_path)
{
	this->mFilePath = file_path;

	if (!mSoundBuffer.loadFromFile(this->mFilePath))
#ifdef _DEBUG 
		std::cout << "File not found" << file_path << std::endl;
#endif

	mSound.setBuffer(mSoundBuffer);
}


void SFX::Play()
{
	mSound.setVolume(conf::gSFXVolume);
	mSound.play();
#ifdef _DEBUG 
	std::cout << "Playing SFX" << mFilePath << std::endl;
#endif
}

void SFX::SetPitch(float new_pitch)
{
	mSound.setPitch(new_pitch);
}

void SFX::Pause()
{
	mSound.pause();
}

void SFX::Stop()
{
	mSound.stop();
}

sf::SoundBuffer* SFX::GetSoundBuffer()
{
	return &mSoundBuffer;
}
