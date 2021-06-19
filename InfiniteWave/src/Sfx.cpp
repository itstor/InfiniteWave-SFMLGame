#include "Sfx.h"
#include "Config.h"
#include <iostream>

SFX::SFX(const std::string& file_path)
{
	this->file_path = file_path;

	if (!buffer.loadFromFile(this->file_path))
#ifdef _DEBUG 
		std::cout << "File not found" << file_path << std::endl;
#endif

	sound.setBuffer(buffer);
}


void SFX::play()
{
	sound.setVolume(conf::sfxVolume);
	sound.play();
#ifdef _DEBUG 
	std::cout << "Playing SFX" << file_path << std::endl;
#endif
}

void SFX::setPitch(float pitch)
{
	sound.setPitch(pitch);
}

void SFX::pause()
{
	sound.pause();
}

void SFX::stop()
{
	sound.stop();
}