#include "BaseScene.h"

void BaseScene::ToggleScene()
{
	mIsActive = !mIsActive;
}

SceneManager* BaseScene::GetSceneManager()
{
	return mManager;
}
