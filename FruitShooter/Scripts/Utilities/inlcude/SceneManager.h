#pragma once
#include <vector>
#include "SharedObject.h"


enum class SceneName { Loading, MainMenu, Setting, Credit, HowToPlay, GamePlay };
using SceneContainer = std::vector<BaseScene*>;
class SceneManager
{
private:
	
};

