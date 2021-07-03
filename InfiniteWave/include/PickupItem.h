#pragma once
#ifndef PICKUP_ITEM_H_
#define PICKUP_ITEM_H_

#include <SFML/Graphics/Texture.hpp>

#include "GameObject.h"
#include "SpriteAnimation.h"


class PickupItem: public GameObject, public sf::Drawable
{
public:
	PickupItem(sf::Texture& item_tex, sf::Vector2f position, sf::Vector2f size, float expired_time);

	void Update(float delta_time);
	bool IsExpired() const;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float mExpiredTime = 0.0f;
	float mElapsedTime = 0.0f;
	bool mIsExpired = false;
	
	sf::Texture* mItemTexture;
	SpriteAnimation mAnimTex;
};

#endif