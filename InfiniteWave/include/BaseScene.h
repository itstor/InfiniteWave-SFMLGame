#pragma once

#include <memory>
#include "SharedObject.h"


namespace sf
{
	class RenderWindow;
}

class BaseScene
{
public:
	BaseScene(SharedObject& obj, bool replace);
	virtual ~BaseScene() = default;

	BaseScene(const BaseScene&) = delete;
	BaseScene& operator=(const BaseScene&) = delete;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	std::unique_ptr<BaseScene> Next();

	[[nodiscard]] bool isReplacing() const;

protected:
	SharedObject& mObj;
	Window& mWindow;
	AudioManager& mAudio;
	SceneManager& mManager;

	bool mReplace;

	std::unique_ptr<BaseScene> mNext;
};

