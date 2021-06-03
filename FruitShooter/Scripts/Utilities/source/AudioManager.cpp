//#include "AudioManager.h"
//#include "Config.h"
//
//AudioManager::AudioManager() = default;
//
//void AudioManager::addMusic(const std::string& musicName, Music& music)
//{
//	musicContainer[1]
//}
//
//
//void AudioManager::toggleMute()
//{
//	conf::isMuted = !conf::isMuted;
//
//	conf::temp_musicVolume = conf::isMuted ? conf::musicVolume : conf::temp_musicVolume;
//	conf::musicVolume = conf::isMuted ? 0.0f : conf::temp_musicVolume;
//
//	for (auto& [name, music] : musicContainer)
//	{
//		music.setVolume(conf::musicVolume);
//	}
//}