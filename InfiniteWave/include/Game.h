#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/System/Clock.hpp>

#include "SharedObject.h"

class Game
{
public:
	Game(SharedObject& obj);
	~Game();

	void RestartClock(); //Reset Clock
	void run(); //Run Game loop

private:
	SharedObject& obj;
	sf::Clock mClock;
	float mDeltaTime = 0;

	void initSFX();
	void initMusic();
};

#endif