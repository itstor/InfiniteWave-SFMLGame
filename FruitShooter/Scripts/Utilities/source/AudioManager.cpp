#include "AudioManager.h"
#include "Config.h"

AudioManager::AudioManager() = default;

void AudioManager::addMusic(const std::string& musicName, const std::string& file_path, bool isLoop)
{
	musicContainer[musicName] = new Music(file_path, isLoop);
}


void AudioManager::toggleMute()
{
	conf::isMuted = !conf::isMuted;

	conf::temp_musicVolume = conf::isMuted ? conf::musicVolume : conf::temp_musicVolume;
	conf::musicVolume = conf::isMuted ? 0.0f : conf::temp_musicVolume;

	updateVolume(conf::musicVolume);
}

void AudioManager::updateVolume(float& newVolume)
{
	for (auto&[name, music] : musicContainer)
	{
		music->setVolume(newVolume);
	}
}

void AudioManager::play(const std::string & music_name)
{
	musicContainer[music_name]->play();
}
