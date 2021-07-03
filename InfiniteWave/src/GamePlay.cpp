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


GamePlay::GamePlay(SharedObject& shared_object, bool replace) : BaseScene(shared_object, replace),
                                                      mPathFindingGrid(mObstaclesContainer),
                                                      mPathFinding(mPathFindingGrid), mRequestManager(mPathFinding), mLighSystem(false)
{
#ifdef _DEBUG
	std::cout << "GamePlay Created" << std::endl;
#endif
	//stop main menu music
	mAudio.StopAllMusic();

	//reset game score
	conf::gGameScore = 0;
	
	//init view
	mMainCamera.reset(sf::FloatRect(0, 0, 3840, 2160));
	mGUICamera.reset(sf::FloatRect(8118, 0, 1920, 1080));

	//init path finding grid
	mPathFindingGrid.Setup(sf::Vector2f(8019, 6547), sf::Vector2f(136, 136));
	
	mPlayer.SetPosition(sf::Vector2f(3602.19f, 4756.3f));

	InitTextures();
	InitLight();
	InitMap();
	InitObstacles();
	InitGUI();
	mPathFindingGrid.CreateGrid();
}

GamePlay::~GamePlay()
{
	std::cout << "GamePlay Deleted" << std::endl;
	mWindow.GetRenderWindow()->setView(mWindow.GetRenderWindow()->getDefaultView());
}

void GamePlay::InitMap()
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

	mGameMap.Load("data/Texture/Sprites/Map/jawbreaker.png", sf::Vector2u(8, 8), map, 59, 48);
	mGameMap.setScale(17, 17);
}

void GamePlay::InitObstacles()
{
	//ROCKS
	mObstaclesContainer.emplace_back(sf::Vector2f(5331, 4921), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(3154, 4236), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(2470.75f, 3011.46f), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(836.35f, 2876.25f), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(7645.07f, 4238.22f), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(7236.48f, 699.15f), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(2603.79f, 423.11f), sf::Vector2f(94, 100));
	
	//WALLS
	/*left top room*/
	mObstaclesContainer.emplace_back(sf::Vector2f(291, 1091), sf::Vector2f(126, 126)); //left
	mObstaclesContainer.emplace_back(sf::Vector2f(1501, 1091), sf::Vector2f(126, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 2045, 2588 ), sf::Vector2f( 126, 126)); //right


	mObstaclesContainer.emplace_back(sf::Vector2f(0, 684), sf::Vector2f(2175, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(0, 1501), sf::Vector2f(1764, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(2042, 812), sf::Vector2f(126, 968)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(0, 1630), sf::Vector2f(675.68f, 960.7f)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(0, 2591), sf::Vector2f(1764, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 1498, 1623 ), sf::Vector2f( 126, 273 )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 1498, 2187 ), sf::Vector2f( 126, 404.5f )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 2044, 2042 ), sf::Vector2f( 126, 270 )); //right


	/*center room*/
	mObstaclesContainer.emplace_back(sf::Vector2f(3134, 2588), sf::Vector2f(126, 544));
	mObstaclesContainer.emplace_back(sf::Vector2f(3815, 2721), sf::Vector2f(126, 411.5f)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(3815, 2034), sf::Vector2f(126, 411.5f)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(3135, 2034), sf::Vector2f(126, 281)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(3135, 1908), sf::Vector2f(811.5f, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(3265.61f, 3006.43f), sf::Vector2f(126, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 3689.61f, 3006.43f ), sf::Vector2f( 126, 126 )); //right
	
	
	/*right room*/
	mObstaclesContainer.emplace_back(sf::Vector2f( 6133, 2725 ), sf::Vector2f( 126, 126 )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 6133, 3408 ), sf::Vector2f( 126, 126 )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 6133, 4089 ), sf::Vector2f( 126, 126 )); //right

	
	mObstaclesContainer.emplace_back(sf::Vector2f(4220, 4500), sf::Vector2f(2721, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(4900, 2183), sf::Vector2f(407, 126)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 5580.16f, 2183 ), sf::Vector2f( 1361, 126 )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(4220, 4088), sf::Vector2f(126, 411.5f)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(4220, 3397), sf::Vector2f(126, 411.5f)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(6808, 3132), sf::Vector2f(126, 537)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(6808, 2309), sf::Vector2f(126, 537)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(6808, 3962), sf::Vector2f(126, 537)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f(4901, 2730), sf::Vector2f(126, 537)); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 4899.45f, 2309.25f ), sf::Vector2f( 126, 126 )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 5032, 2863 ), sf::Vector2f( 408, 126 )); //right
	mObstaclesContainer.emplace_back(sf::Vector2f( 5032, 3267.5f ), sf::Vector2f( 408, 126 )); //right




	/*left bottom room*/
	mObstaclesContainer.emplace_back(sf::Vector2f(1653.48f, 4236), sf::Vector2f(94, 100));
	mObstaclesContainer.emplace_back(sf::Vector2f(1653.48f, 3829.75f), sf::Vector2f(94, 100));
	
	mObstaclesContainer.emplace_back(sf::Vector2f(0.0f, 4638.04f), sf::Vector2f(2175, 126.25f)); //bottom wall
	mObstaclesContainer.emplace_back(sf::Vector2f(0.0f, 3408), sf::Vector2f(2175, 126.25f)); //top wall
	mObstaclesContainer.emplace_back(sf::Vector2f(2043.0f, 4226.48f), sf::Vector2f(131, 411.56f)); //left bottom wall
	mObstaclesContainer.emplace_back(sf::Vector2f( 2043.0f, 3534.0 ), sf::Vector2f( 131, 411.56f )); //left top wall

	//Add light obstacle
	for (auto &obs:mObstaclesContainer)
	{
		mLighSystem.createLightShape(*obs.GetCollider())->setRenderLightOver(false);
	}
	
	//MAP BOUNDARIES
	mObstaclesContainer.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(-1.0f, 6536.0f));
	mObstaclesContainer.emplace_back(sf::Vector2f(8018.0f, 0.0f), sf::Vector2f(1.0f, 6536.0f));
	mObstaclesContainer.emplace_back(sf::Vector2f(0.0f, 6536.0f), sf::Vector2f(8018.0f, 1.0f));
	mObstaclesContainer.emplace_back(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(8018.0f, -1.0f));
	
	//STAIRS
	mObstaclesContainer.emplace_back(sf::Vector2f(269, 3538), sf::Vector2f(822.28f, 272)); //left bottom room
	mObstaclesContainer.emplace_back(sf::Vector2f(4494, 3394), sf::Vector2f(948, 272)); //right room, top
	mObstaclesContainer.emplace_back(sf::Vector2f(4494, 4227), sf::Vector2f(948, 272)); //right room, bottom

	//OUTDOOR LADDER
	mObstaclesContainer.emplace_back(sf::Vector2f(2700, 4479), sf::Vector2f(182.81f, 176.56f)); //right room, bottom


}

void GamePlay::InitButtons()
{
	//Initialize button here
}

void GamePlay::InitLight()
{
	//init light system
	mLighSystem.create({ 100.0f,100.0f,200.0f,200.0f }, mWindow.GetWindowSize());

	//load light texture
	mFlashLightTex.loadFromFile("data/Texture/Sprites/Map/flashlight.png");
	mFlashLightTex.setSmooth(true);

	mGunLightTex.loadFromFile("data/Texture/Sprites/Map/mGunLightTex.png");
	mGunLightTex.setSmooth(true);

	mFlashLight = mLighSystem.createLightPointEmission();
	mFlashLight->setOrigin(sf::Vector2f(static_cast<float>(mFlashLightTex.getSize().x), static_cast<float>(mFlashLightTex.getSize().y) * 0.5f));
	mFlashLight->setTexture(mFlashLightTex);
	mFlashLight->setScale(-5.f, 5.f);
	mFlashLight->setColor(sf::Color::White);

	mGunLight = mLighSystem.createLightPointEmission();
	mGunLight->setOrigin(sf::Vector2f(mGunLightTex.getSize().x * 0.5f, mGunLightTex.getSize().y * 0.5f));
	mGunLight->setTexture(mGunLightTex);
	mGunLight->setScale(15.f, 15.f);
	mGunLight->setColor(sf::Color::Yellow);
	mGunLight->setTurnedOn(false);

	mLighSystem.setAmbientColor({ 30,30,30 });
}

void GamePlay::InitGUI()
{
	mPixelFont.loadFromFile("data/Font/Minecraft.ttf");
	mAmmoText.setFont(mPixelFont);
	mKillText.setFont(mPixelFont);
	mScoreTitleText.setFont(mPixelFont);
	mTotalScoreText.setFont(mPixelFont);
	mWaveTitleText.setFont(mPixelFont);
	mCurrentWaveText.setFont(mPixelFont);
	mWaveCompleteText.setFont(mPixelFont);

	mAmmoText.setString("18/18");
	mKillText.setString("0");
	mScoreTitleText.setString("Score:");
	mTotalScoreText.setString("0");
	mWaveTitleText.setString("Wave:");
	mCurrentWaveText.setString("1/~");
	mWaveCompleteText.setString("Wave Complete");

	mHealthIconTex.loadFromFile("data/Texture/GUI/health.png");
	mKillIconTex.loadFromFile("data/Texture/GUI/kill.png");
	mAmmoIconTex.loadFromFile("data/Texture/GUI/ammo.png");
	
	mHealthIconRect.setTexture(&mHealthIconTex);
	mKillIconRect.setTexture(&mKillIconTex);
	mAmmoIconRect.setTexture(&mAmmoIconTex);
	mHealthBarRect.setFillColor(sf::Color::Red);
	mAmmoText.setFillColor(sf::Color(204, 153, 37));
	mKillText.setFillColor(sf::Color::White);
	mScoreTitleText.setFillColor(sf::Color::White);
	mTotalScoreText.setFillColor(sf::Color::White);
	mWaveTitleText.setFillColor(sf::Color::White);
	mCurrentWaveText.setFillColor(sf::Color::White);
	mWaveCompleteText.setFillColor(sf::Color::White);
	mDyingOverlay.setFillColor(sf::Color(255, 0, 0, 0));
	mFadeToBlackOverlay.setFillColor(sf::Color(0, 0, 0, 0));
	
	mHealthIconRect.setSize(static_cast<const sf::Vector2f>(mHealthIconTex.getSize()));
	mKillIconRect.setSize(static_cast<const sf::Vector2f>(mKillIconTex.getSize()));
	mAmmoIconRect.setSize(static_cast<const sf::Vector2f>(mAmmoIconTex.getSize()));
	mHealthBarRect.setSize({ 318, 28.65f });
	mAmmoText.setScale(1.2f, 1.2f);
	mKillText.setScale(1.2f, 1.2f);
	mScoreTitleText.setScale(0.8f, 0.8f);
	mTotalScoreText.setScale(1.5f, 1.5f);
	mWaveTitleText.setScale(1, 1);
	mCurrentWaveText.setScale(1.8f, 1.8f);
	mWaveCompleteText.setScale(0.0f, 0.0f);
	mDyingOverlay.setSize({ 1920.0f,1080.0f });
	mFadeToBlackOverlay.setSize({ 1920.0f,1080.0f });

	mHealthIconRect.setPosition(9581.59f, 38.3f);
	mKillIconRect.setPosition(9631.25f, 118.71f);
	mAmmoIconRect.setPosition(9786.53f, 118.71f);
	mHealthBarRect.setPosition(9642.53f, 51.45f);
	mAmmoText.setPosition(9850.2f, 127.2f);
	mKillText.setPosition(9693.63f, 127.7f);
	mScoreTitleText.setPosition(8155.36f, 956.08f);
	mTotalScoreText.setPosition(8155.36f, 978.27f);
	mWaveTitleText.setPosition(9889.69f, 926.52f);
	mCurrentWaveText.setPosition(9889.69f, 970.61f);
	mWaveCompleteText.setOrigin(mWaveCompleteText.getLocalBounds().left + mWaveCompleteText.getLocalBounds().width * 0.5f,
	                           mWaveCompleteText.getLocalBounds().top + mWaveCompleteText.getLocalBounds().height * 0.5f);
	mWaveCompleteText.setPosition(9078.31f, 540.0f);
	mDyingOverlay.setPosition(8118.0f, 0.0f);
	mFadeToBlackOverlay.setPosition(8118.0f, 0.0f);
}

void GamePlay::InitTextures()
{
	//Load zombie Texture
	mNormalZombieTex.loadFromFile("data/Texture/Sprites/Zombie/normal-zombie-sprites.png");
	mNormalZombieTex.setSmooth(true);

	mRedZombieTex.loadFromFile("data/Texture/Sprites/Zombie/red-zombie-sprites.png");
	mRedZombieTex.setSmooth(true);

	mBlueZombieTex.loadFromFile("data/Texture/Sprites/Zombie/blue-zombie-sprites.png");
	mBlueZombieTex.setSmooth(true);

	mBlackZombieTex.loadFromFile("data/Texture/Sprites/Zombie/black-zombie-sprites.png");
	mBlackZombieTex.setSmooth(true);

	mHealthPickupTex.loadFromFile("data/Texture/Sprites/Pickup/health.png");
	mHealthPickupTex.setSmooth(true);

	mBloodSplashTex.loadFromFile("data/Texture/Sprites/Zombie/blood-splash.png");
	mBloodSplashTex.setSmooth(true);
}

void GamePlay::Pause()
{
	std::cout << "GamePlay Paused" << std::endl;
}

void GamePlay::Resume()
{
	std::cout << "GamePlay Resume" << std::endl;
}

void GamePlay::CalculateTotalZombie()
{
	const auto n = static_cast<float>(mCurrentWave);
	
	mTotalNormalZombie = static_cast<int>(floor((powf(n, 2) + 15) / 4.0f));
	mTotalRedZombie = static_cast<int>(floor((powf(n, 2) - 3) / 4.0f));
	mTotalBlueZombie = static_cast<int>(floor((powf(n, 2) - 7) / 6.0f));
	mTotalBlackZombie = static_cast<int>(floor((powf(n, 2) - 10) / 10.0f));

	mTotalNormalZombie = mTotalNormalZombie > 0 ? mTotalNormalZombie : 0;
	mTotalRedZombie = mTotalRedZombie > 0 ? mTotalRedZombie : 0;
	mTotalBlueZombie = mTotalBlueZombie > 0 ? mTotalBlueZombie : 0;
	mTotalBlackZombie = mTotalBlackZombie > 0 ? mTotalBlackZombie : 0;

	//std::cout << mTotalNormalZombie << mTotalRedZombie << totalBrownZombie << mTotalBlackZombie;
	mCurrentActiveZombie = mTotalNormalZombie + mTotalRedZombie + mTotalBlueZombie + mTotalBlackZombie;
}

bool GamePlay::SpawnZombie(float delta_time)
{
	mSpawnCooldown -= delta_time;
	if (mSpawnCooldown <= 0.0f)
	{
		if (mTotalNormalZombie > 0)
		{
			mTotalNormalZombie--;
			Spawn(ZombieType::NORMAL_ZOMBIE, mPlayer.GetPosition());
		}
		else if (mTotalRedZombie > 0)
		{
			mTotalRedZombie--;
			Spawn(ZombieType::RED_ZOMBIE, mPlayer.GetPosition());
		}
		else if (mTotalBlueZombie > 0)
		{
			mTotalBlueZombie--;
			Spawn(ZombieType::BLUE_ZOMBIE, mPlayer.GetPosition());
		}
		else if (mTotalBlackZombie > 0)
		{
			mTotalBlackZombie--;
			Spawn(ZombieType::BLACK_ZOMBIE, mPlayer.GetPosition());
		}
		else
		{
			return true; //return true if all have been spawned
		}
		mSpawnCooldown = 1.0f;
	}
	return false;
}

void GamePlay::Spawn(ZombieType zombie_type, const sf::Vector2f & player_pos)
{
	float yPos = 1091.0f; //Obstacle
	float xPos = 291.0f; //Obstacle
	float distanceFromPlayer = 0.0f;
	while (mPathFindingGrid.GetNodeType(mPathFindingGrid.GetGridIndexFromPosition({xPos, yPos})) !=
		NodeType::WALKABLE_NODE || distanceFromPlayer <= 965.0f)
	{
		xPos = static_cast<float>(rand() % 8019);
		yPos = static_cast<float>(rand() % 6547);
		distanceFromPlayer = sqrt(pow(player_pos.x - xPos, 2) + pow(player_pos.y - yPos, 2));
	}
	switch (zombie_type)
	{
	case ZombieType::NORMAL_ZOMBIE: mZombieContainer.push_back(
			new NormalZombie({xPos, yPos}, mNormalZombieTex, mBloodSplashTex, mRequestManager, *mAudio.GetSoundBuffer("zombie_1")));
		break;
	case ZombieType::RED_ZOMBIE: mZombieContainer.push_back(
			new RedZombie({xPos, yPos}, mRedZombieTex,mBloodSplashTex, mRequestManager, *mAudio.GetSoundBuffer("zombie_1")));
		break;
	case ZombieType::BLUE_ZOMBIE: mZombieContainer.push_back(
			new BlueZombie({xPos, yPos}, mBlueZombieTex,mBloodSplashTex, mRequestManager, *mAudio.GetSoundBuffer("zombie_1")));
		break;
	case ZombieType::BLACK_ZOMBIE: mZombieContainer.push_back(
			new BlackZombie({xPos, yPos}, mBlackZombieTex,mBloodSplashTex,mRequestManager, *mAudio.GetSoundBuffer("zombie_1")));
		break;
	default: break;
	}
}

void GamePlay::Update(float delta_time)
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
				mAudio.PlaySFX("pistol_reload");
				mPlayer.Reload();
				mAmmoText.setString(std::string(std::to_string(mPlayer.GetAmmo())).append("/18"));
			} break;
			case sf::Keyboard::F1: mIsShowGUI = !mIsShowGUI; break;
			case sf::Keyboard::F11: mWindow.ToggleFullScreen(); break;
			case sf::Keyboard::Space: mNextScene = SceneManager::Build<GameoverScene>(mSharedObject, true); break;
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
						if (mPlayer.Shoot())
						{
							mAudio.PlaySFX("pistol_shoot");
							
							mBullet.SetStartPos(sf::Vector2f(mPlayer.GetPosition().x + 20, mPlayer.GetPosition().y + 20));
							mBullet.SetDirection(*mPlayer.GetDirVect());

							mGunLight->setTurnedOn(true);
							mGunLightDelay = 0.0f;

							mAmmoText.setString(std::string(std::to_string(mPlayer.GetAmmo())).append("/18"));

							mBulletContainer.emplace_back(mBullet);
						}
						else if (mPlayer.GetAmmo() <= 0)
						{
							mAudio.PlaySFX("pistol_click");
						}
				} break;
				default: break;
				}
		} break;
		default: break;
		}
	}

	if (!mPlayer.IsDead()) {
		if (mGunLight->isTurnedOn()) {
			mGunLightDelay += delta_time;

			if (mGunLightDelay >= 0.1f)
				mGunLight->setTurnedOn(false);
		}

		/*UPDATE CAMERA CENTER*/
		if ((mPlayer.GetPosition().x - mMainCamera.getSize().x / 2 < 0 ||
			mPlayer.GetPosition().x + mMainCamera.getSize().x / 2 > 8018) &&
			(mPlayer.GetPosition().y - mMainCamera.getSize().y / 2 < 0 ||
				mPlayer.GetPosition().y + mMainCamera.getSize().y / 2 > 6536))
		{
			mMainCamera.setCenter(mMainCamera.getCenter().x, mMainCamera.getCenter().y);
		}
		else if (mPlayer.GetPosition().x - mMainCamera.getSize().x / 2 < 0 ||
			mPlayer.GetPosition().x + mMainCamera.getSize().x / 2 > 8018)
		{
			mMainCamera.setCenter(mMainCamera.getCenter().x, mPlayer.GetPosition().y);
		}
		else if (mPlayer.GetPosition().y - mMainCamera.getSize().y / 2 < 0 ||
			mPlayer.GetPosition().y + mMainCamera.getSize().y / 2 > 6536)
		{
			mMainCamera.setCenter(mPlayer.GetPosition().x, mMainCamera.getCenter().y);
		}
		else
		{
			mMainCamera.setCenter(mPlayer.GetPosition());
		}

		//Update mPlayer face dir and light dir
		const sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow.GetRenderWindow());
		const sf::Vector2f worldMousePos = mWindow.GetRenderWindow()->mapPixelToCoords(mousePos);
		mPlayer.LookAt(worldMousePos);

		mFlashLight->setPosition(mPlayer.GetPosition());
		mGunLight->setPosition(mPlayer.GetPosition());
		mFlashLight->setRotation(mPlayer.GetAngle());

		//Player keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			mPlayer.MoveDirection(MoveDir::UP, delta_time);
			//mMainCamera.move(0*deltaTime, -400.f*deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			mPlayer.MoveDirection(MoveDir::LEFT, delta_time);
			//mMainCamera.move(-400.0f*deltaTime, 0*deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			mPlayer.MoveDirection(MoveDir::DOWN, delta_time);
			//mMainCamera.move(0*deltaTime, 400.f*deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			mPlayer.MoveDirection(MoveDir::RIGHT, delta_time);
			//mMainCamera.move(400.0f*deltaTime, 0*deltaTime);
		}

		//Update zombie and mPlayer
		mPlayer.Update(delta_time);
		for (auto &zombie : mZombieContainer) {
			zombie->Update(delta_time, mPlayer.GetPosition());
		}

		//All object collision check here
		//On Collision with obstacle or wall
		for (auto &obs : mObstaclesContainer)
		{
			mPlayer.CheckCollision(obs);
			for (size_t i = 0; i < mBulletContainer.size(); i++)
			{
				//Check if mBullet collided with obstacle or out of distance, delete
				if (mBulletContainer[i].OnCollision(obs) || sqrt(
					pow(mBulletContainer[i].GetPosition().x - mBulletContainer[i].mStartPosition.x, 2) + pow(
						mBulletContainer[i].GetPosition().y - mBulletContainer[i].mStartPosition.y, 2)) > 1920)
				{
					mBulletContainer.erase(mBulletContainer.begin() + i);
				}
			}
		}


		for (size_t j = 0; j < mZombieContainer.size(); j++) {
			//Check mPlayer attack
			if (mPlayer.OnCollision(*mZombieContainer[j]) && mZombieContainer[j]->IsAllowAttack())
			{
				const float damage = rand() % 10 + 5;
				mZombieContainer[j]->Attack();
				mPlayer.GetHit(damage);
			}
			//Update path finding?
			for (size_t i = 0; i < mBulletContainer.size(); i++)
			{
				//Check if collided with zombie delete
				if (mBulletContainer[i].OnCollision(*mZombieContainer[j]))
				{
					mZombieContainer[j]->GetHit();
					mBulletContainer.erase(mBulletContainer.begin() + i);
					//Check if zombie dead?
					if (mZombieContainer[j]->IsDead())
					{
						mKillCount++;
						mCurrentActiveZombie--;
						mKillText.setString(std::to_string(mKillCount));
						mTotalScoreText.setString(std::to_string(conf::gGameScore));

						int score = 0;

						switch (mZombieContainer[j]->GetZombieType())
						{
						case ZombieType::NORMAL_ZOMBIE: score = 500; break;
						case ZombieType::RED_ZOMBIE: score = 1000; break;
						case ZombieType::BLUE_ZOMBIE: score = 1500; break;
						case ZombieType::BLACK_ZOMBIE: score = 2000; break;
						default: break;
						}

						conf::gGameScore += score;

						if (const int randomNum = rand() % 100; randomNum % 5 == 0) { //20% rate
							mHealthPickupContainer.emplace_back(new PickupItem(
								mHealthPickupTex,
								sf::Vector2f(mZombieContainer[j]->GetPosition().x, mZombieContainer[j]->GetPosition().y),
								sf::Vector2f(100.0f, 100.0f), 15.0f));
						}

						delete mZombieContainer[j];
						mZombieContainer.erase(mZombieContainer.begin() + j);
					}
				}
			}
		}

		for (size_t i = 0; i < mHealthPickupContainer.size(); i++)
		{
			mHealthPickupContainer[i]->Update(delta_time);
			if (mPlayer.OnCollision(*mHealthPickupContainer[i]))
			{
				mPlayer.IncreaseHealth(15);
				mAudio.PlaySFX("health_pickup");
				mHealthPickupContainer.erase(mHealthPickupContainer.begin() + i);
			}
			else if (mHealthPickupContainer[i]->IsExpired())
			{
				mHealthPickupContainer.erase(mHealthPickupContainer.begin() + i);
			}
		}

		//Move everything here
		mPlayer.PlayerMove(); // Move Player
		for (auto &bul : mBulletContainer) //move mBullet
		{
			bul.Move(delta_time);
		}
		for (auto &zombie : mZombieContainer)
		{
			zombie->Move(delta_time);
		}

		//Update Wave
		if (mCurrentActiveZombie <= 0)
		{
			mIsNextWave = true;
			mCurrentWave++;
			mCurrentWaveText.setString(std::to_string(mCurrentWave).append("/~"));
			CalculateTotalZombie();
			//Play next wave animation
			if (mCurrentWave > 1) mAnimManager.PlayAnimation(AnimType::ZOOM, TransitionType::EASE_IN_OUT_CUBIC, { 0.0f, 0.0f },
				{ 2.8f, 0.0f }, 1.0f, mWaveCompleteText, true, 2.0f);
		}
		if (mIsNextWave)
		{
			mNextWaveDelay -= delta_time;
			if (mNextWaveDelay <= 0.0f)
			{
				if (const bool spawnedAll = SpawnZombie(delta_time); spawnedAll) {
					mNextWaveDelay = 5.0f;
					mIsNextWave = false;
				}
			}
		}

		//Update Dying Overlay
		if (mPlayer.GetHealth() <= 75)
		{
			if (!mIsHeartBeatPlayed) {
				mAudio.PlayMusic("HeartBeat");
				mIsHeartBeatPlayed = true;
			}
			const float progressOverlay = (75 - mPlayer.GetHealth()) / 75;
			const float progressMusic = (75 - mPlayer.GetHealth()) / 75;
			const sf::Uint8 a = 40 * progressOverlay;
			mAudio.SetMusicVolume("HeartBeat", 100 * progressMusic);
			mDyingOverlay.setFillColor(sf::Color(255, 0, 0, a));
		}
		else if (mIsHeartBeatPlayed)
		{
			mAudio.StopMusic("HeartBeat");
		}

		//Update Health bar
		const float xHealthBar = (mPlayer.GetHealth() / 200.0f) * 318;
		mHealthBarRect.setSize({ xHealthBar, mHealthBarRect.getSize().y });

		//update mPlayer position on grid
		mPathFindingGrid.UpdatePlayerNode(mPlayer.GetPosition());

		//UPdate Animation
		mAnimManager.Update(delta_time);
	}
	else
	{
		mAudio.StopAllMusic();
		static float elapsedFadeTime = 0.0f;
		elapsedFadeTime += delta_time;
		const sf::Uint8 progress = elapsedFadeTime / 4.0f * 255;
		mFadeToBlackOverlay.setFillColor(sf::Color(0, 0, 0, progress));
		if (elapsedFadeTime >= 4.0f)
		{
			mNextScene = SceneManager::Build<GameoverScene>(mSharedObject, true);
		}
	}
}

void GamePlay::Draw()
{
	mWindow.BeginDraw();

	/*Draw everything here*/
	mWindow.GetRenderWindow()->setView(mMainCamera);
	
	mWindow.Draw(mGameMap);
	/*for (auto &bul:mBulletContainer)
	{
		mWindow.Draw(*bul.getDraw());
	}*/

	for (auto health:mHealthPickupContainer)
	{
		mWindow.Draw(*health);
	}
	
	mWindow.Draw(*mPlayer.GetFeetDraw());
	mWindow.Draw(*mPlayer.GetDraw());

	for (auto zombie : mZombieContainer) {
		mWindow.Draw(*zombie->GetDraw());
		mWindow.Draw(*zombie->GetBloodDraw());
	}

	mLighSystem.render(*mWindow.GetRenderWindow());
	//mPathFindingGrid.Draw(mWindow.GetRenderWindow());

	//GUI Here
	mWindow.GetRenderWindow()->setView(mGUICamera);
	mWindow.Draw(mDyingOverlay);
	if (mIsShowGUI) {
		mWindow.Draw(mHealthIconRect);
		mWindow.Draw(mKillIconRect);
		mWindow.Draw(mAmmoIconRect);
		mWindow.Draw(mHealthBarRect);
		mWindow.Draw(mAmmoText);
		mWindow.Draw(mKillText);
		mWindow.Draw(mScoreTitleText);
		mWindow.Draw(mTotalScoreText);
		mWindow.Draw(mWaveTitleText);
		mWindow.Draw(mCurrentWaveText);
		mWindow.Draw(mWaveCompleteText);
		if (mPlayer.IsDead()) {
			mWindow.Draw(mFadeToBlackOverlay);
		}
		//Reset view back
	}
	mWindow.GetRenderWindow()->setView(mMainCamera);

	
	mWindow.EndDraw();
}

