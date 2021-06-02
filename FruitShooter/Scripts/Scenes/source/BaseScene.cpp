#include "BaseScene.h"

BaseScene::BaseScene(SceneManager & manager, sf::RenderWindow & window, bool replace): mManager(manager), mWindow(window), mReplace(replace)
{
}

std::unique_ptr<BaseScene> BaseScene::Next()
{
	return std::move(mNext);
}

bool BaseScene::isReplacing() const
{
	return mReplace;
}

