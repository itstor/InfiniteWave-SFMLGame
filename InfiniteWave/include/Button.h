#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

enum btn_state { IDLE_BTN = 0, HOVER_BTN = 1, ACTIVE_BTN = 2, FIRST_STATE = 3, SECOND_STATE = 4};

class Button
{
public:
	Button() = default;
	
	void Setup(const std::string& idlePath, const std::string& hoverPath, const std::string& activePath, float sizeFact, sf::Vector2f
	           pos);

	sf::RectangleShape* getDraw();
	void Update(sf::Vector2f mousePos);
	void Click();

	bool isPressed() const;
	bool isHover() const;
	
private:
	sf::Texture btnIdleTex;
	sf::Texture btnHoverTex;
	sf::Texture btnActiveTex;

protected:
	sf::RectangleShape btn;
	unsigned short int btnState;
	
};

