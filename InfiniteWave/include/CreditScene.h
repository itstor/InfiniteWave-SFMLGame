#pragma once
#ifndef CREDIT_H_
#define CREDIT_H_

#include <SFML/Graphics.hpp>
#include "BaseScene.h"
#include "Button.h" //GUI Optional

class SceneManager;

class CreditScene final : public BaseScene
{
public:
	CreditScene(SharedObject& shared_object, bool replace = true);
	~CreditScene() override;

	void Pause() override;
	void Draw() override;
	void Resume() override;
	void Update(float delta_time) override;

private:
	//Define scene component here
	void InitBackground();
	void InitButton();

	sf::Font mHeadlineFont;
	sf::Font mDCCFont;
	sf::Text mCreditText;
	sf::Text mCreatedByText;
	sf::Text mAdditionalText;
	sf::Text mAddCreditText;
	sf::Text mLibraryText;
	sf::Text mLibraryCreditText;
	
	sf::Texture mMenuBgTex;
	sf::Sprite mMenuBgSpi;
	Button mButtonBack;
};

#endif