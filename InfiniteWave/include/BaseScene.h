#pragma once
#ifndef BASE_SCENE_H_
#define BASE_SCENE_H_

#include <memory>

#include "SharedObject.h"

namespace sf
{
	class RenderWindow;
}


class BaseScene
{
public:
	BaseScene(SharedObject& shared_object, bool replace);
	virtual ~BaseScene() = default;

	BaseScene(const BaseScene&) = delete;
	BaseScene& operator=(const BaseScene&) = delete;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(float delta_time) = 0;
	virtual void Draw() = 0;

	std::unique_ptr<BaseScene> Next();

	[[nodiscard]] bool IsReplacing() const;

protected:
	bool mReplace;
	
	SharedObject& mSharedObject;
	Window& mWindow;
	AudioManager& mAudio;
	SceneManager& mScene;

	std::unique_ptr<BaseScene> mNextScene;
};

#endif