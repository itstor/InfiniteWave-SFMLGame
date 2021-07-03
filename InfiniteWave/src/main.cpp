#include "Game.h"
#include "Config.h"
#include "Window.h"
#include "AudioManager.h"
#include "SharedObject.h"
#include "SceneManager.h"


int WinMain()
{
	sf::Image icon;
	
	const std::string kWindowTitle = "Infinite Wave";
	const sf::Vector2u kWindowSize(conf::gWindowWidth, conf::gWindowHeight);

	if (!icon.loadFromFile("data/Texture/Icon/icon.png"))
	{
		return EXIT_FAILURE;
	}

	//init shared object
	SharedObject Obj;
	Obj.Window = new Window(kWindowTitle, kWindowSize, icon);
	Obj.AudioManager = new AudioManager;
	Obj.SceneManager = new SceneManager;

	Game game(Obj);

	game.Run();

	
	return EXIT_SUCCESS;
}
