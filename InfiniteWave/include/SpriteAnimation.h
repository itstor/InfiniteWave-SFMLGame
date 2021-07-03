#pragma once
#ifndef SPRITE_ANIMATION_H_
#define SPRITE_ANIMATION_H_

#include <SFML/Graphics/Texture.hpp>


class SpriteAnimation
{
public:
	SpriteAnimation();

	void Setup(sf::Texture* anim_tex, unsigned row, unsigned max_image_count);
	void Update(float delta_time, int row, float switch_time, unsigned start_frame, unsigned end_frame);
	void Hide();

	[[nodiscard]] bool IsFinish() const;
	sf::IntRect* GetTextureRect();
	
private:
	unsigned int mCurrentImage = 0;
	unsigned int mMaxImage = 0;
	int mPrevRow = -1;
	bool mFinish = false;
	float mTotalTime = 0.0f;

	sf::IntRect mUVRect;
};

#endif
