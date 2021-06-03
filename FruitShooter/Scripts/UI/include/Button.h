#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum btn_state { IDLE = 0, HOVER = 1, ACTIVE = 3 };

class Button
{
public:
	Button();

	void Setup(std::string idlePath, std::string hoverPath, std::string activePath, float sizeFact, sf::Vector2f pos);

	sf::RectangleShape* getDraw();
	void Update(sf::Vector2f mousePos);

	bool isPressed() const;
	
private:
	sf::SoundBuffer btnSfxBuff;
	sf::Sound btnSfx;
	
	sf::Texture btnIdleTex;
	sf::Texture btnHoverTex;
	sf::Texture btnActiveTex;

	sf::RectangleShape btn;

	unsigned char btnState;
	
};

