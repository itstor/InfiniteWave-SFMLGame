#include "Sfx.h"
#include "Config.h"

SFX::SFX(const std::string& file_path)
{
	this->mFilePath = file_path;

	mSoundBuffer.loadFromFile(this->mFilePath);

	mSound.setBuffer(mSoundBuffer);
}


void SFX::Play()
{
	mSound.setVolume(conf::gSFXVolume);
	mSound.play();
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
