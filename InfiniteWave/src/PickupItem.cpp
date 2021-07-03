#include "PickupItem.h"

#include <SFML/Graphics/RenderTarget.hpp>

PickupItem::PickupItem(sf::Texture& item_tex, sf::Vector2f position, sf::Vector2f size, float expired_time) : mItemTexture(item_tex)
{
	mColliderBody.setSize(size);
	mColliderBody.setOrigin(size.x * 0.5f, size.y * 0.5f);
	mColliderBody.setPosition(position);
	mColliderBody.setTexture(&mItemTexture);
	mAnimTex.Setup(&item_tex, 1, 4);
	mColliderBody.setTextureRect(*mAnimTex.GetTextureRect());

	mExpiredTime = expired_time;
}

void PickupItem::Update(float delta_time)
{
	mAnimTex.Update(delta_time, 0, 0.5f, 0, 3);
	mColliderBody.setTextureRect(*mAnimTex.GetTextureRect());

	mElapsedTime += delta_time;
	if (mElapsedTime >= mExpiredTime)
	{
		mIsExpired = true;
	}
}

bool PickupItem::IsExpired() const
{
	return mIsExpired;
}

void PickupItem::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.texture = &mItemTexture;
	target.draw(mColliderBody, states);
}
