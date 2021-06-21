#include "ToggleButton.h"

#include <iostream>

void ToggleButton::Setup(const std::string & firstStatePath, const std::string & secondStatePath, float sizeFact, sf::Vector2f pos, unsigned short int setState)
{
	firstStateTex.loadFromFile(firstStatePath);
	secondStateTex.loadFromFile(secondStatePath);

	btn.setSize(sf::Vector2f(static_cast<float>(firstStateTex.getSize().x), static_cast<float>(firstStateTex.getSize().y)));
	btn.setScale(sizeFact, sizeFact);
	btn.setOrigin(btn.getSize().x / 2, btn.getSize().y / 2);
	btn.setPosition(pos);

	btnState = setState;
}

void ToggleButton::Update(sf::Vector2f mousePos)
{
	misHover = false;
	
	if(btn.getGlobalBounds().contains(mousePos))
	{
		misHover = true;
	}

	
	if (btnState == FIRST_STATE)
	{
		btn.setTexture(&firstStateTex);
	}
	else if (btnState == SECOND_STATE)
	{
		btn.setTexture(&secondStateTex);
	}
}

bool ToggleButton::isHover() const
{
	return misHover;
}

int ToggleButton::toggleState()
{
	btnState = btnState == FIRST_STATE ? SECOND_STATE : FIRST_STATE;

	std::cout << btnState << std::endl;

	return btnState;
}

