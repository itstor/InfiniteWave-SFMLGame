#include "BaseScene.h"

#include "SharedObject.h"

BaseScene::BaseScene(SharedObject& shared_object, bool replace) : mSharedObject(shared_object), mWindow(*shared_object.Window), mAudio(*shared_object.AudioManager), mScene(*shared_object.SceneManager), mReplace(replace){}

std::unique_ptr<BaseScene> BaseScene::Next()
{
	return std::move(mNextScene);
}

bool BaseScene::IsReplacing() const
{
	return mReplace;
}

