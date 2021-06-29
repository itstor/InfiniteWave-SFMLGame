#pragma once

#include <SFML/Graphics.hpp>

#include "AnimationManager.h"
#include "BaseScene.h"
#include "Bullet.h"
#include "Button.h" //GUI Optional
#include "Grid.h"
#include "Map.h"
#include "Player.h"
#include "Obstacle.h"
#include "LightSystem.hpp"
#include "PathFinding.h"
#include "Zombie.h"

class Zombie;
class Bullet;
class SceneManager;
class PickupItem;


class GamePlay final : public BaseScene
{
public:
	GamePlay(SharedObject& obj, bool replace = true);
	~GamePlay() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float deltaTime) override;


private:
	void initObstacles();
	void initButton();
	void initMap();
	void initLight();
	void initGUI();
	bool spawnZombie(float deltaTime);
	void spawn(ZombieType zombieType, const sf::Vector2f& playerPos);
	void calculateTotalZombie();
	
	//Define scene component here
	Grid mPathFindingGrid;
	PathFinding mPathFinding;
	PathRequestManager mRequestManager;
	AnimationManager mAnimManager;
	
	float gunLightDelay = 0.0f;

	//Wave system
	bool nextWave = false;
	float nextWaveDelay = 5.0f;
	float spawnCooldown = 1.0f;
	unsigned int currentWave = 0;
	int killCount = 0;
	int gameScore = 0;
	int currentActiveZombie = 0;
	int totalNormalZombie = 0;
	int totalRedZombie = 0;
	int totalBlueZombie = 0;
	int totalBlackZombie = 0;
	
	Player player;
	Bullet bullet;
	Map gameMap;

	//Zombie Texture
	sf::Texture normalZombieTex;
	sf::Texture redZombieTex;
	sf::Texture blueZombieTex;
	sf::Texture blackZombieTex;

	//Light
	ltbl::LightSystem ls;
	ltbl::LightPointEmission* flashLight;
	ltbl::LightPointEmission* gunLight;
	sf::Texture flashLightTexture;
	sf::Texture pointLightTexture;

	//Container
	std::vector<Obstacle> obstacleContainer;
	std::vector<Bullet> bulletContainer;
	std::vector<sf::RectangleShape> shapes;
	//std::vector<PickupItem> pickupItem;
	std::vector<Zombie*> zombieContainer;

	//GUI
	bool showGUI = true;
	
	sf::View camera;
	sf::View GUICamera;

	sf::Texture healthIconTex;
	sf::Texture killIconTex;
	sf::Texture ammoIconTex;

	sf::RectangleShape healthIconRect;
	sf::RectangleShape killIconRect;
	sf::RectangleShape ammoIconRect;
	sf::RectangleShape healthBar;

	sf::Font pixelFont;
	sf::Text killText;
	sf::Text ammoText;
	sf::Text scoreTitleText;
	sf::Text scoreTotalText;
	sf::Text waveTitleText;
	sf::Text waveCurrentText;
	sf::Text waveCompleteText;
};
