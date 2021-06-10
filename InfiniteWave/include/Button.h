#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

enum btn_state { IDLE = 0, HOVER = 1, ACTIVE = 2 };

class Button
{
public:
	Button() = default;
	
	void Setup(const std::string& idlePath, const std::string& hoverPath, const std::string& activePath, float sizeFact, sf::Vector2f
	           pos);

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

	unsigned char btnState{};
	
};

