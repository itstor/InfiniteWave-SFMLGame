#pragma once
#include <string>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Button.h"

class ToggleButton: public Button
{
public:
	ToggleButton() = default;

	void Setup(const std::string& firstStatePath, const std::string& secondStatePath, float sizeFact, sf::Vector2f pos, unsigned short
	           currentState = FIRST_STATE);

	void Update(sf::Vector2f mousePos);
	bool isHover() const;
	int toggleState();

private:
	bool misHover;
	
	sf::Texture firstStateTex;
	sf::Texture secondStateTex;
};

