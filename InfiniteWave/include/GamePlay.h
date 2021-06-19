#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Bullet.h"
#include "Button.h" //GUI Optional
#include "Map.h"
#include "Player.h"
#include "Obstacle.h"
#include "LightSystem.hpp"

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
	void initBg();
	void initButton();
	void initMap();
	void initLight();

	
	//Define scene component here
	Player player;
	Bullet bullet;
	Map gameMap;

	ltbl::LightSystem ls;
	ltbl::LightPointEmission* flashLight;
	ltbl::LightPointEmission* gunLight;

	sf::Texture flashLightTexture;
	sf::Texture pointLightTexture;
	sf::RectangleShape nightOverlay;
	sf::RectangleShape mist;
	sf::Texture mistTex;
	sf::View camera;
	sf::View GUICamera;
	std::vector<Obstacle*> obstacleContainer;
	std::vector<Bullet> bulletContainer;
	std::vector<sf::RectangleShape> shapes;
	/*std::vector<PickupItem> pickupItem;
	std::vector<Zombie> zombie;*/
};
