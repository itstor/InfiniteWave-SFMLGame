#include "GamePlay.h"

//Related Scene

//Required Library
#include <fstream>
#include <iostream>

#include "Window.h"
#include "AudioManager.h"

#include "BlackZombie.h"
#include "BlueZombie.h"
#include "GameoverScene.h"
#include "NormalZombie.h"
#include "RedZombie.h"
#include "SceneManager.h"
#include "Config.h"


GamePlay::GamePlay(SharedObject& obj, bool replace) : BaseScene(obj, replace),
                                                      mPathFindingGrid(obstacleContainer),
                                                      mPathFinding(mPathFindingGrid), mRequestManager(mPathFinding), ls(false)
{
#ifdef _DEBUG
	std::cout << "GamePlay Created" << std::endl;
#endif
	//stop main menu music
	mAudio.stopAll();

	//reset game score
	conf::gameScore = 0;
	
	//init view
	camera.reset(sf::FloatRect(0, 0, 3840, 2160));
	GUICamera.reset(sf::FloatRect(8118, 0, 1920, 1080));

	//init path finding grid
	mPathFindingGrid.Setup(sf::Vector2f(8019, 6547), sf::Vector2f(136, 136));
	
	player.setPosition(sf::Vector2f(3602.19f, 4756.3f));

	initTexture();
	initLight();
	initMap();
	initObstacles();
	initGUI();
	mPathFindingGrid.CreateGrid();
}

GamePlay::~GamePlay()
{
	std::cout << "GamePlay Deleted" << std::endl;
	mWindow.GetRenderWindow()->setView(mWindow.GetRenderWindow()->getDefaultView());
}

void GamePlay::initMap()
{
	int map[2832];
	int i = 0;

	std::ifstream file;
	
	file.open("data/map.txt");
	
	while (!file.eof())
	{
		file >> map[i];
		i++;
	}

	file.close();

	gameMap.load("data/Texture/Sprites/Map/jawbreaker.png", sf::Vector2u(8, 8), map, 59, 48);
	gameMap.setScale(17, 17);
}

void GamePlay::initObstacles()
{
	//ROCKS
	obstacleContainer.emplace_back(sf::Vector2f(5331, 4921), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(3154, 4236), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(2470.75f, 3011.46f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(836.35f, 2876.25f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(7645.07f, 4238.22f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(7236.48f, 699.15f), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(2603.79f, 423.11f), sf::Vector2f(94, 100));
	
	//WALLS
	/*left top room*/
	obstacleContainer.emplace_back(sf::Vector2f(291, 1091), sf::Vector2f(126, 126)); //left
	obstacleContainer.emplace_back(sf::Vector2f(1501, 1091), sf::Vector2f(126, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 2045, 2588 ), sf::Vector2f( 126, 126)); //right


	obstacleContainer.emplace_back(sf::Vector2f(0, 684), sf::Vector2f(2175, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(0, 1501), sf::Vector2f(1764, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(2042, 812), sf::Vector2f(126, 968)); //right
	obstacleContainer.emplace_back(sf::Vector2f(0, 1630), sf::Vector2f(675.68f, 960.7f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(0, 2591), sf::Vector2f(1764, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 1498, 1623 ), sf::Vector2f( 126, 273 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 1498, 2187 ), sf::Vector2f( 126, 404.5f )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 2044, 2042 ), sf::Vector2f( 126, 270 )); //right


	/*center room*/
	obstacleContainer.emplace_back(sf::Vector2f(3134, 2588), sf::Vector2f(126, 544));
	obstacleContainer.emplace_back(sf::Vector2f(3815, 2721), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3815, 2034), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3135, 2034), sf::Vector2f(126, 281)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3135, 1908), sf::Vector2f(811.5f, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(3265.61f, 3006.43f), sf::Vector2f(126, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 3689.61f, 3006.43f ), sf::Vector2f( 126, 126 )); //right
	
	
	/*right room*/
	obstacleContainer.emplace_back(sf::Vector2f( 6133, 2725 ), sf::Vector2f( 126, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 6133, 3408 ), sf::Vector2f( 126, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 6133, 4089 ), sf::Vector2f( 126, 126 )); //right

	
	obstacleContainer.emplace_back(sf::Vector2f(4220, 4500), sf::Vector2f(2721, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f(4900, 2183), sf::Vector2f(407, 126)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 5580.16f, 2183 ), sf::Vector2f( 1361, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f(4220, 4088), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(4220, 3397), sf::Vector2f(126, 411.5f)); //right
	obstacleContainer.emplace_back(sf::Vector2f(6808, 3132), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f(6808, 2309), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f(6808, 3962), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f(4901, 2730), sf::Vector2f(126, 537)); //right
	obstacleContainer.emplace_back(sf::Vector2f( 4899.45f, 2309.25f ), sf::Vector2f( 126, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 5032, 2863 ), sf::Vector2f( 408, 126 )); //right
	obstacleContainer.emplace_back(sf::Vector2f( 5032, 3267.5f ), sf::Vector2f( 408, 126 )); //right




	/*left bottom room*/
	obstacleContainer.emplace_back(sf::Vector2f(1653.48f, 4236), sf::Vector2f(94, 100));
	obstacleContainer.emplace_back(sf::Vector2f(1653.48f, 3829.75f), sf::Vector2f(94, 100));
	
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 4638.04f), sf::Vector2f(2175, 126.25f)); //bottom wall
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 3408), sf::Vector2f(2175, 126.25f)); //top wall
	obstacleContainer.emplace_back(sf::Vector2f(2043.0f, 4226.48f), sf::Vector2f(131, 411.56f)); //left bottom wall
	obstacleContainer.emplace_back(sf::Vector2f( 2043.0f, 3534.0 ), sf::Vector2f( 131, 411.56f )); //left top wall

	//Add light obstacle
	for (auto &obs:obstacleContainer)
	{
		ls.createLightShape(*obs.getCollider())->setRenderLightOver(false);
	}
	
	//MAP BOUNDARIES
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(-1.0f, 6536.0f));
	obstacleContainer.emplace_back(sf::Vector2f(8018.0f, 0.0f), sf::Vector2f(1.0f, 6536.0f));
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 6536.0f), sf::Vector2f(8018.0f, 1.0f));
	obstacleContainer.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(8018.0f, -1.0f));
	
	//STAIRS
	obstacleContainer.emplace_back(sf::Vector2f(269, 3538), sf::Vector2f(822.28f, 272)); //left bottom room
	obstacleContainer.emplace_back(sf::Vector2f(4494, 3394), sf::Vector2f(948, 272)); //right room, top
	obstacleContainer.emplace_back(sf::Vector2f(4494, 4227), sf::Vector2f(948, 272)); //right room, bottom

	//OUTDOOR LADDER
	obstacleContainer.emplace_back(sf::Vector2f(2700, 4479), sf::Vector2f(182.81f, 176.56f)); //right room, bottom


}

void GamePlay::initButton()
{
	//Initialize button here
}

void GamePlay::initLight()
{
	//init light system
	ls.create({ 100.0f,100.0f,200.0f,200.0f }, mWindow.GetWindowSize());

	//load light texture
	flashLightTexture.loadFromFile("data/Texture/Sprites/Map/flashlight.png");
	flashLightTexture.setSmooth(true);

	pointLightTexture.loadFromFile("data/Texture/Sprites/Map/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	flashLight = ls.createLightPointEmission();
	flashLight->setOrigin(sf::Vector2f(static_cast<float>(flashLightTexture.getSize().x), static_cast<float>(flashLightTexture.getSize().y) * 0.5f));
	flashLight->setTexture(flashLightTexture);
	flashLight->setScale(-5.f, 5.f);
	flashLight->setColor(sf::Color::White);

	gunLight = ls.createLightPointEmission();
	gunLight->setOrigin(sf::Vector2f(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f));
	gunLight->setTexture(pointLightTexture);
	gunLight->setScale(15.f, 15.f);
	gunLight->setColor(sf::Color::Yellow);
	gunLight->setTurnedOn(false);

	ls.setAmbientColor({ 30,30,30 });
}

void GamePlay::initGUI()
{
	pixelFont.loadFromFile("data/Font/Minecraft.ttf");
	ammoText.setFont(pixelFont);
	killText.setFont(pixelFont);
	scoreTitleText.setFont(pixelFont);
	scoreTotalText.setFont(pixelFont);
	waveTitleText.setFont(pixelFont);
	waveCurrentText.setFont(pixelFont);
	waveCompleteText.setFont(pixelFont);

	ammoText.setString("18/18");
	killText.setString("0");
	scoreTitleText.setString("Score:");
	scoreTotalText.setString("0");
	waveTitleText.setString("Wave:");
	waveCurrentText.setString("1/~");
	waveCompleteText.setString("Wave Complete");

	healthIconTex.loadFromFile("data/Texture/GUI/health.png");
	killIconTex.loadFromFile("data/Texture/GUI/kill.png");
	ammoIconTex.loadFromFile("data/Texture/GUI/ammo.png");
	
	healthIconRect.setTexture(&healthIconTex);
	killIconRect.setTexture(&killIconTex);
	ammoIconRect.setTexture(&ammoIconTex);
	healthBar.setFillColor(sf::Color::Red);
	ammoText.setFillColor(sf::Color(204, 153, 37));
	killText.setFillColor(sf::Color::White);
	scoreTitleText.setFillColor(sf::Color::White);
	scoreTotalText.setFillColor(sf::Color::White);
	waveTitleText.setFillColor(sf::Color::White);
	waveCurrentText.setFillColor(sf::Color::White);
	waveCompleteText.setFillColor(sf::Color::White);
	dyingOverlay.setFillColor(sf::Color(255, 0, 0, 0));
	fadeToBlack.setFillColor(sf::Color(0, 0, 0, 0));
	
	healthIconRect.setSize(static_cast<const sf::Vector2f>(healthIconTex.getSize()));
	killIconRect.setSize(static_cast<const sf::Vector2f>(killIconTex.getSize()));
	ammoIconRect.setSize(static_cast<const sf::Vector2f>(ammoIconTex.getSize()));
	healthBar.setSize({ 318, 28.65f });
	ammoText.setScale(1.2f, 1.2f);
	killText.setScale(1.2f, 1.2f);
	scoreTitleText.setScale(0.8f, 0.8f);
	scoreTotalText.setScale(1.5f, 1.5f);
	waveTitleText.setScale(1, 1);
	waveCurrentText.setScale(1.8f, 1.8f);
	waveCompleteText.setScale(0.0f, 0.0f);
	dyingOverlay.setSize({ 1920.0f,1080.0f });
	fadeToBlack.setSize({ 1920.0f,1080.0f });

	healthIconRect.setPosition(9581.59f, 38.3f);
	killIconRect.setPosition(9631.25f, 118.71f);
	ammoIconRect.setPosition(9786.53f, 118.71f);
	healthBar.setPosition(9642.53f, 51.45f);
	ammoText.setPosition(9850.2f, 127.2f);
	killText.setPosition(9693.63f, 127.7f);
	scoreTitleText.setPosition(8155.36f, 956.08f);
	scoreTotalText.setPosition(8155.36f, 978.27f);
	waveTitleText.setPosition(9889.69f, 926.52f);
	waveCurrentText.setPosition(9889.69f, 970.61f);
	waveCompleteText.setOrigin(waveCompleteText.getLocalBounds().left + waveCompleteText.getLocalBounds().width * 0.5f,
	                           waveCompleteText.getLocalBounds().top + waveCompleteText.getLocalBounds().height * 0.5f);
	waveCompleteText.setPosition(9078.31f, 540.0f);
	dyingOverlay.setPosition(8118.0f, 0.0f);
	fadeToBlack.setPosition(8118.0f, 0.0f);
}

void GamePlay::initTexture()
{
	//Load zombie Texture
	normalZombieTex.loadFromFile("data/Texture/Sprites/Zombie/normal-zombie-sprites.png");
	normalZombieTex.setSmooth(true);

	redZombieTex.loadFromFile("data/Texture/Sprites/Zombie/red-zombie-sprites.png");
	redZombieTex.setSmooth(true);

	blueZombieTex.loadFromFile("data/Texture/Sprites/Zombie/blue-zombie-sprites.png");
	blueZombieTex.setSmooth(true);

	blackZombieTex.loadFromFile("data/Texture/Sprites/Zombie/black-zombie-sprites.png");
	blackZombieTex.setSmooth(true);

	pickupHealthTex.loadFromFile("data/Texture/Sprites/Pickup/health.png");
	pickupHealthTex.setSmooth(true);

	bloodSplash.loadFromFile("data/Texture/Sprites/Zombie/blood-splash.png");
	bloodSplash.setSmooth(true);
}

void GamePlay::Pause()
{
	std::cout << "GamePlay Paused" << std::endl;
}

void GamePlay::Resume()
{
	std::cout << "GamePlay Resume" << std::endl;
}

void GamePlay::calculateTotalZombie()
{
	const auto n = static_cast<float>(currentWave);
	
	totalNormalZombie = static_cast<int>(floor((powf(n, 2) + 15) / 4.0f));
	totalRedZombie = static_cast<int>(floor((powf(n, 2) - 3) / 4.0f));
	totalBlueZombie = static_cast<int>(floor((powf(n, 2) - 7) / 6.0f));
	totalBlackZombie = static_cast<int>(floor((powf(n, 2) - 10) / 10.0f));

	totalNormalZombie = totalNormalZombie > 0 ? totalNormalZombie : 0;
	totalRedZombie = totalRedZombie > 0 ? totalRedZombie : 0;
	totalBlueZombie = totalBlueZombie > 0 ? totalBlueZombie : 0;
	totalBlackZombie = totalBlackZombie > 0 ? totalBlackZombie : 0;

	//std::cout << totalNormalZombie << totalRedZombie << totalBrownZombie << totalBlackZombie;
	currentActiveZombie = totalNormalZombie + totalRedZombie + totalBlueZombie + totalBlackZombie;
}

bool GamePlay::spawnZombie(float deltaTime)
{
	spawnCooldown -= deltaTime;
	if (spawnCooldown <= 0.0f)
	{
		if (totalNormalZombie > 0)
		{
			totalNormalZombie--;
			spawn(ZombieType::NORMAL_ZOMBIE, player.getPosition());
		}
		else if (totalRedZombie > 0)
		{
			totalRedZombie--;
			spawn(ZombieType::RED_ZOMBIE, player.getPosition());
		}
		else if (totalBlueZombie > 0)
		{
			totalBlueZombie--;
			spawn(ZombieType::BLUE_ZOMBIE, player.getPosition());
		}
		else if (totalBlackZombie > 0)
		{
			totalBlackZombie--;
			spawn(ZombieType::BLACK_ZOMBIE, player.getPosition());
		}
		else
		{
			return true; //return true if all have been spawned
		}
		spawnCooldown = 1.0f;
	}
	return false;
}

void GamePlay::spawn(ZombieType zombieType, const sf::Vector2f & playerPos)
{
	float yPos = 1091.0f; //Obstacle
	float xPos = 291.0f; //Obstacle
	float distanceFromPlayer = 0.0f;
	while (mPathFindingGrid.GetNodeType(mPathFindingGrid.GetGridIndexFromPosition({xPos, yPos})) !=
		NodeType::WALKABLE_NODE || distanceFromPlayer <= 965.0f)
	{
		xPos = static_cast<float>(rand() % 8019);
		yPos = static_cast<float>(rand() % 6547);
		distanceFromPlayer = sqrt(pow(playerPos.x - xPos, 2) + pow(playerPos.y - yPos, 2));
	}
	switch (zombieType)
	{
	case ZombieType::NORMAL_ZOMBIE: zombieContainer.push_back(
			new NormalZombie({xPos, yPos}, normalZombieTex, bloodSplash, mRequestManager, *mAudio.getSoundBuffer("zombie_1")));
		break;
	case ZombieType::RED_ZOMBIE: zombieContainer.push_back(
			new RedZombie({xPos, yPos}, redZombieTex,bloodSplash, mRequestManager, *mAudio.getSoundBuffer("zombie_1")));
		break;
	case ZombieType::BLUE_ZOMBIE: zombieContainer.push_back(
			new BlueZombie({xPos, yPos}, blueZombieTex,bloodSplash, mRequestManager, *mAudio.getSoundBuffer("zombie_1")));
		break;
	case ZombieType::BLACK_ZOMBIE: zombieContainer.push_back(
			new BlackZombie({xPos, yPos}, blackZombieTex,bloodSplash,mRequestManager, *mAudio.getSoundBuffer("zombie_1")));
		break;
	default: break;
	}
}

void GamePlay::Update(float deltaTime)
{
	for (auto event = sf::Event{}; mWindow.GetRenderWindow()->pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed: mWindow.Destroy(); break;
		case sf::Event::KeyPressed:
		{
			switch (event.key.code)
			{
				/*Only for non-simultaneous key
				Use if statement for simultaneous key*/
			case sf::Keyboard::R: 
			{
				mAudio.playSFX("pistol_reload");
				player.Reload();
				ammoText.setString(std::string(std::to_string(player.getAmmo())).append("/18"));
			} break;
			case sf::Keyboard::F1: showGUI = !showGUI; break;
			case sf::Keyboard::F11: mWindow.ToggleFullScreen(); break;
			case sf::Keyboard::Space: mNext = SceneManager::build<GameoverScene>(mObj, true); break;
			default: break;
			}
			break;
		}
		case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					{
						if (player.Shoot())
						{
							mAudio.playSFX("pistol_shoot");
							
							bullet.setStartPos(sf::Vector2f(player.getPosition().x + 20, player.getPosition().y + 20));
							bullet.setDir(*player.getDirVect());

							gunLight->setTurnedOn(true);
							gunLightDelay = 0.0f;

							ammoText.setString(std::string(std::to_string(player.getAmmo())).append("/18"));

							bulletContainer.emplace_back(bullet);
						}
						else if (player.getAmmo() <= 0)
						{
							mAudio.playSFX("pistol_click");
						}
				} break;
				default: break;
				}
		} break;
		default: break;
		}
	}

	if (!player.isDead()) {
		if (gunLight->isTurnedOn()) {
			gunLightDelay += deltaTime;

			if (gunLightDelay >= 0.1f)
				gunLight->setTurnedOn(false);
		}

		/*UPDATE CAMERA CENTER*/
		if ((player.getPosition().x - camera.getSize().x / 2 < 0 ||
			player.getPosition().x + camera.getSize().x / 2 > 8018) &&
			(player.getPosition().y - camera.getSize().y / 2 < 0 ||
				player.getPosition().y + camera.getSize().y / 2 > 6536))
		{
			camera.setCenter(camera.getCenter().x, camera.getCenter().y);
		}
		else if (player.getPosition().x - camera.getSize().x / 2 < 0 ||
			player.getPosition().x + camera.getSize().x / 2 > 8018)
		{
			camera.setCenter(camera.getCenter().x, player.getPosition().y);
		}
		else if (player.getPosition().y - camera.getSize().y / 2 < 0 ||
			player.getPosition().y + camera.getSize().y / 2 > 6536)
		{
			camera.setCenter(player.getPosition().x, camera.getCenter().y);
		}
		else
		{
			camera.setCenter(player.getPosition());
		}

		//Update player face dir and light dir
		const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
		const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);
		player.lookAt(worldMousePos);

		flashLight->setPosition(player.getPosition());
		gunLight->setPosition(player.getPosition());
		flashLight->setRotation(player.getAngle());

		//Player keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			player.MoveDirection(MoveDir::UP, deltaTime);
			//camera.move(0*deltaTime, -400.f*deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.MoveDirection(MoveDir::LEFT, deltaTime);
			//camera.move(-400.0f*deltaTime, 0*deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			player.MoveDirection(MoveDir::DOWN, deltaTime);
			//camera.move(0*deltaTime, 400.f*deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.MoveDirection(MoveDir::RIGHT, deltaTime);
			//camera.move(400.0f*deltaTime, 0*deltaTime);
		}

		//Update zombie and player
		player.Update(deltaTime);
		for (auto &zombie : zombieContainer) {
			zombie->Update(deltaTime, player.getPosition());
		}

		//All object collision check here
		//On Collision with obstacle or wall
		for (auto &obs : obstacleContainer)
		{
			player.CheckCollision(obs);
			for (size_t i = 0; i < bulletContainer.size(); i++)
			{
				//Check if bullet collided with obstacle or out of distance, delete
				if (bulletContainer[i].onCollision(obs) || sqrt(
					pow(bulletContainer[i].getPosition().x - bulletContainer[i].startPosition.x, 2) + pow(
						bulletContainer[i].getPosition().y - bulletContainer[i].startPosition.y, 2)) > 1920)
				{
					bulletContainer.erase(bulletContainer.begin() + i);
				}
			}
		}


		for (size_t j = 0; j < zombieContainer.size(); j++) {
			//Check player attack
			if (player.onCollision(*zombieContainer[j]) && zombieContainer[j]->isAllowAttack())
			{
				const float damage = rand() % 10 + 5;
				zombieContainer[j]->Attack();
				player.getHit(damage);
			}
			//Update path finding?
			for (size_t i = 0; i < bulletContainer.size(); i++)
			{
				//Check if collided with zombie delete
				if (bulletContainer[i].onCollision(*zombieContainer[j]))
				{
					zombieContainer[j]->getHit();
					bulletContainer.erase(bulletContainer.begin() + i);
					//Check if zombie dead?
					if (zombieContainer[j]->isDead())
					{
						killCount++;
						currentActiveZombie--;
						killText.setString(std::to_string(killCount));
						scoreTotalText.setString(std::to_string(conf::gameScore));

						int score = 0;

						switch (zombieContainer[j]->getZombieType())
						{
						case ZombieType::NORMAL_ZOMBIE: score = 500; break;
						case ZombieType::RED_ZOMBIE: score = 1000; break;
						case ZombieType::BLUE_ZOMBIE: score = 1500; break;
						case ZombieType::BLACK_ZOMBIE: score = 2000; break;
						default: break;
						}

						conf::gameScore += score;

						if (const int randomNum = rand() % 100; randomNum % 5 == 0) { //20% rate
							pickupHealthContainer.emplace_back(new PickupItem(
								pickupHealthTex,
								sf::Vector2f(zombieContainer[j]->getPosition().x, zombieContainer[j]->getPosition().y),
								sf::Vector2f(100.0f, 100.0f), 15.0f));
						}

						delete zombieContainer[j];
						zombieContainer.erase(zombieContainer.begin() + j);
					}
				}
			}
		}

		for (size_t i = 0; i < pickupHealthContainer.size(); i++)
		{
			pickupHealthContainer[i]->Update(deltaTime);
			if (player.onCollision(*pickupHealthContainer[i]))
			{
				player.increaseHealth(15);
				mAudio.playSFX("health_pickup");
				pickupHealthContainer.erase(pickupHealthContainer.begin() + i);
			}
			else if (pickupHealthContainer[i]->isExpired())
			{
				pickupHealthContainer.erase(pickupHealthContainer.begin() + i);
			}
		}

		//Move everything here
		player.PlayerMove(); // Move Player
		for (auto &bul : bulletContainer) //move bullet
		{
			bul.Move(deltaTime);
		}
		for (auto &zombie : zombieContainer)
		{
			zombie->Move(deltaTime);
		}

		//Update Wave
		if (currentActiveZombie <= 0)
		{
			nextWave = true;
			currentWave++;
			waveCurrentText.setString(std::to_string(currentWave).append("/~"));
			calculateTotalZombie();
			//Play next wave animation
			if (currentWave > 1) mAnimManager.playAnimation(AnimType::ZOOM, TransitionType::EASE_IN_OUT_CUBIC, { 0.0f, 0.0f },
				{ 2.8f, 0.0f }, 1.0f, waveCompleteText, true, 2.0f);
		}
		if (nextWave)
		{
			nextWaveDelay -= deltaTime;
			if (nextWaveDelay <= 0.0f)
			{
				if (const bool spawnedAll = spawnZombie(deltaTime); spawnedAll) {
					nextWaveDelay = 5.0f;
					nextWave = false;
				}
			}
		}

		//Update Dying Overlay
		if (player.getHealth() <= 75)
		{
			if (!isHeartBeatPlayed) {
				mAudio.play("HeartBeat");
				isHeartBeatPlayed = true;
			}
			const float progressOverlay = (75 - player.getHealth()) / 75;
			const float progressMusic = (75 - player.getHealth()) / 75;
			const sf::Uint8 a = 40 * progressOverlay;
			mAudio.setMusicVolume("HeartBeat", 100 * progressMusic);
			dyingOverlay.setFillColor(sf::Color(255, 0, 0, a));
		}
		else if (isHeartBeatPlayed)
		{
			mAudio.stopMusic("HeartBeat");
		}

		//Update Health bar
		const float xHealthBar = (player.getHealth() / 200.0f) * 318;
		healthBar.setSize({ xHealthBar, healthBar.getSize().y });

		//update player position on grid
		mPathFindingGrid.UpdatePlayerNode(player.getPosition());

		//UPdate Animation
		mAnimManager.Update(deltaTime);
	}
	else
	{
		mAudio.stopAll();
		static float elapsedFadeTime = 0.0f;
		elapsedFadeTime += deltaTime;
		const sf::Uint8 progress = elapsedFadeTime / 4.0f * 255;
		fadeToBlack.setFillColor(sf::Color(0, 0, 0, progress));
		if (elapsedFadeTime >= 4.0f)
		{
			mNext = SceneManager::build<GameoverScene>(mObj, true);
		}
	}
}

void GamePlay::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.GetRenderWindow()->setView(camera);
	
	mWindow.Draw(gameMap);
	/*for (auto &bul:bulletContainer)
	{
		mWindow.Draw(*bul.getDraw());
	}*/

	for (auto health:pickupHealthContainer)
	{
		mWindow.Draw(*health);
	}
	
	mWindow.Draw(*player.getFeetDraw());
	mWindow.Draw(*player.getDraw());

	for (auto zombie : zombieContainer) {
		mWindow.Draw(*zombie->getDraw());
		mWindow.Draw(*zombie->getBloodDraw());
	}

	ls.render(*mWindow.GetRenderWindow());
	//mPathFindingGrid.Draw(mWindow.GetRenderWindow());

	//GUI Here
	mWindow.GetRenderWindow()->setView(GUICamera);
	mWindow.Draw(dyingOverlay);
	if (showGUI) {
		mWindow.Draw(healthIconRect);
		mWindow.Draw(killIconRect);
		mWindow.Draw(ammoIconRect);
		mWindow.Draw(healthBar);
		mWindow.Draw(ammoText);
		mWindow.Draw(killText);
		mWindow.Draw(scoreTitleText);
		mWindow.Draw(scoreTotalText);
		mWindow.Draw(waveTitleText);
		mWindow.Draw(waveCurrentText);
		mWindow.Draw(waveCompleteText);
		if (player.isDead()) {
			mWindow.Draw(fadeToBlack);
		}
		//Reset view back
	}
	mWindow.GetRenderWindow()->setView(camera);

	
	mWindow.EndDraw();
}

