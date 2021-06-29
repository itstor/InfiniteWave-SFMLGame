#pragma once
#include <functional>
#include <SFML/System/Vector2.hpp>

enum class AnimType { ZOOM, MOVE };

namespace sf {
	class Transformable;
}

class Animation
{
public:
	Animation(AnimType anim_type, const sf::Vector2f& start, const sf::Vector2f& end, float time, sf::Transformable & object, bool back, float back_delay);
	~Animation() = default;

	void Update(float deltaTime);

	[[nodiscard]] bool isFinished() const;

private:
	[[nodiscard]] float easeInOutCubic(float x) const;
	
	bool misFinished = false;
	bool mBack = false;
	float res = 0.0;
	float elapsedTime = 0.0f;
	float progress = 0.0f;
	float timePerFrame;
	float mBackDelay = 0.0f;

	AnimType mAnimType;
	sf::Vector2f mEnd;
	sf::Vector2f mStart;
	sf::Vector2f totalFrame;
	sf::Transformable* mObject;
};

