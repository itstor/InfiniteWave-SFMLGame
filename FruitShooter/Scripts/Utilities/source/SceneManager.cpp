#include "SceneManager.h"

#include <iostream>

SceneManager::SceneManager(): mIsResume(false)
{
#ifdef _DEBUG
	std::cout << "Scene Manager Created" << std::endl;
#endif
}

void SceneManager::run(std::unique_ptr<BaseScene> scene)
{
#ifdef _DEBUG
	std::cout << "Scene Manager Running" << std::endl;
#endif
	//move scene to the stack of scene container
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