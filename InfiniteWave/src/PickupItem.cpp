#include "PickupItem.h"

#include <SFML/Graphics/RenderTarget.hpp>

PickupItem::PickupItem(sf::Texture& item_tex, sf::Vector2f position, sf::Vector2f size, float expired_time) : mItemTexture(item_tex)
{
	ColliderBody.setSize(size);
	ColliderBody.setOrigin(size.x * 0.5f, size.y * 0.5f);
	ColliderBody.setPosition(position);
	ColliderBody.setTexture(&mItemTexture);
	mAnimTex.Setup(&item_tex, 1, 4);
	ColliderBody.setTextureRect(*mAnimTex.getTexture());

	mExpiredTime = expired_time;
}

void PickupItem::Update(float deltaTime)
{
	mAnimTex.Update(deltaTime, 0, 0.5f, 0, 3);
	ColliderBody.setTextureRect(*mAnimTex.getTexture());

	mElapsedTime += deltaTime;
	if (mElapsedTime >= mExpiredTime)
	{
		mIsExpired = true;
	}
}

bool PickupItem::isExpired() const
{
	return mIsExpired;
}

void PickupItem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.texture = &mItemTexture;
	target.draw(ColliderBody, states);
}
