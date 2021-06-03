#include "SceneManager.h"

#include <iostream>

SceneManager::SceneManager(): mIsResume(false), mIsRunning(false)
{
#ifdef _DEBUG
	std::cout << "Scene Manager Created" << std::endl;
#endif
}

void SceneManager::run(std::unique_ptr<BaseScene> scene)
{
	mIsRunning = true;
	mScene.push(std::move(scene));
}


void SceneManager::nextScene()
{
	if (mIsResume)
	{
		if (!mScene.empty())
			mScene.pop();

		if(!mScene.empty())
			mScene.top()->Resume();

		mIsResume = false;
	}

	if (!mScene.empty())
	{
		if (auto temp = mScene.top()->Next(); temp!=nullptr)
		{
			if (temp->isReplacing())
				mScene.pop();

			else
				mScene.top()->Pause();

			mScene.push(std::move(temp));
		}
	}
}

void SceneManager::prevScene()
{
	mIsResume = true;
}

void SceneManager::Update()
{
	mScene.top()->Update();
}

void SceneManager::Draw()
{
	mScene.top()->Draw();
}

bool SceneManager::running() const
{
	return mIsRunning;
}

void SceneManager::quit()
{
	mIsRunning = false;
}
