#pragma once

#include <memory>
#include "Window.h"

class SceneManager;

namespace sf
{
	class RenderWindow;
}

class BaseScene
{
public:
	BaseScene(SceneManager& manager, Window& window, bool replace);
	virtual ~BaseScene() = default;

	BaseScene(const BaseScene&) = delete;
	BaseScene& operator=(const BaseScene&) = delete;

	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	std::unique_ptr<BaseScene> Next();

	bool isReplacing() const;

protected:
	SceneManager& mManager;
	Window& mWindow;

	bool mReplace;

	std::unique_ptr<BaseScene> mNext;
};

