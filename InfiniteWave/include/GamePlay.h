#pragma once

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h" //GUI Optional
#include "Player.h"
#include "Obstacle.h"

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

	void initBg();
	void initButton();

private:
	//Define scene component here
	Player player;
	Obstacle wall;
	Obstacle wall2;
	sf::Vector2i mousePos;
	sf::Vector2f worldMousePos;
	std::vector<Obstacle> obstacle;
	/*std::vector<PickupItem> pickupItem;
	std::vector<Bullet> bullet;
	std::vector<Zombie> zombie;*/
};
