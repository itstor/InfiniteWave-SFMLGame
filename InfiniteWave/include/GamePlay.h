#pragma once
#ifndef GAME_PLAY_H_
#define GAME_PLAY_H_

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Grid.h"
#include "Bullet.h"
#include "Button.h"
#include "Player.h"
#include "Zombie.h"
#include "Obstacle.h"
#include "BaseScene.h"
#include "PickupItem.h"
#include "PathFinding.h"
#include "LightSystem.hpp"
#include "AnimationManager.h"

class SceneManager;


class GamePlay final : public BaseScene
{
public:
	GamePlay(SharedObject& shared_object, bool replace = true);
	~GamePlay() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	void InitObstacles();
	void InitButtons();
	void InitMap();
	void InitLight();
	void InitGUI();
	void InitTextures();
	bool SpawnZombie(float delta_time);
	void Spawn(ZombieType zombie_type, const sf::Vector2f& player_pos);
	void CalculateTotalZombie();
	
	//Define scene component here
	Grid mPathFindingGrid;
	PathFinding mPathFinding;
	PathRequestManager mRequestManager;
	AnimationManager mAnimManager;
	
	float mGunLightDelay = 0.0f;
	bool mIsHeartBeatPlayed = false;

	//Wave system
	bool mIsNextWave = false;
	float mNextWaveDelay = 5.0f;
	float mSpawnCooldown = 1.0f;
	unsigned int mCurrentWave = 0;
	int mKillCount = 0;
	int mCurrentActiveZombie = 0;
	int mTotalNormalZombie = 0;
	int mTotalRedZombie = 0;
	int mTotalBlueZombie = 0;
	int mTotalBlackZombie = 0;

	Player mPlayer;
	Bullet mBullet;
	Map mGameMap;

	//Zombie Texture
	sf::Texture mNormalZombieTex;
	sf::Texture mRedZombieTex;
	sf::Texture mBlueZombieTex;
	sf::Texture mBlackZombieTex;
	sf::Texture mBloodSplashTex;

	//Light
	ltbl::LightSystem mLighSystem;
	ltbl::LightPointEmission* mFlashLight{};
	ltbl::LightPointEmission* mGunLight{};
	sf::Texture mFlashLightTex;
	sf::Texture mGunLightTex;

	//Container
	std::vector<Obstacle> mObstaclesContainer;
	std::vector<Bullet> mBulletContainer;
	std::vector<sf::RectangleShape> mLightObstaclesContainer;
	std::vector<PickupItem*> mHealthPickupContainer;
	std::vector<Zombie*> mZombieContainer;

	//GUI
	bool mIsShowGUI = true;
	
	sf::View mMainCamera;
	sf::View mGUICamera;

	sf::Texture mHealthIconTex;
	sf::Texture mKillIconTex;
	sf::Texture mAmmoIconTex;
	sf::Texture mHealthPickupTex;

	sf::RectangleShape mHealthIconRect;
	sf::RectangleShape mKillIconRect;
	sf::RectangleShape mAmmoIconRect;
	sf::RectangleShape mHealthBarRect;
	sf::RectangleShape mDyingOverlay;
	sf::RectangleShape mFadeToBlackOverlay;
	sf::RectangleShape mPauseOverlay;

	sf::Font mPixelFont;
	sf::Text mKillText;
	sf::Text mAmmoText;
	sf::Text mScoreTitleText;
	sf::Text mTotalScoreText;
	sf::Text mWaveTitleText;
	sf::Text mCurrentWaveText;
	sf::Text mWaveCompleteText;

	Button mResumeButton;
	Button mBackMainMenuButton;
};

#endif