#include "BaseScene.h"

#include "SharedObject.h"

BaseScene::BaseScene(SharedObject& obj, bool replace) : mObj(obj), mWindow(*obj.Window), mAudio(*obj.AudioManager), mManager(*obj.SceneManager), mReplace(replace){}

std::unique_ptr<BaseScene> BaseScene::Next()
{
	return std::move(mNext);
}

bool BaseScene::isReplacing() const
{
	return mReplace;
}

