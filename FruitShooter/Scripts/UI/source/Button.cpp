#include "Button.h"


void Button::Setup(const std::string& idlePath, const std::string& hoverPath, const std::string& activePath, float sizeFact, sf::Vector2f pos)
{
	btnIdleTex.loadFromFile(idlePath);
	btnHoverTex.loadFromFile(hoverPath);
	btnActiveTex.loadFromFile(activePath);

	btn.setSize(sf::Vector2f(static_cast<float>(btnIdleTex.getSize().x), static_cast<float>(btnIdleTex.getSize().y)));
	btn.setScale(sizeFact, sizeFact);
	btn.setOrigin(btn.getSize().x/2, btn.getSize().y/2);
	btn.setPosition(pos.x, pos.y);

	btnSfxBuff.loadFromFile("Assets/Audio/SFX/Button_9.wav");
	btnSfx.setBuffer(btnSfxBuff);

	btnState = IDLE;
}

sf::RectangleShape* Button::getDraw()
{
	return &btn;
}

void Button::Update(sf::Vector2f mousePos)
{
	btnState = IDLE;
	if(btn.getGlobalBounds().contains(mousePos))
	{
		btnState = HOVER;
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && btnState != ACTIVE)
		{
			btnState = ACTIVE;
			if (btnSfx.getStatus() != sf::SoundSource::Playing)
				btnSfx.play();
		}
	}

	switch (btnState)
	{
	case IDLE:
		{
		btn.setTexture(&btnIdleTex);
	} break;
	case HOVER:
		{
		btn.setTexture(&btnHoverTex);
	} break;
	case ACTIVE:
		{
		btn.setTexture(&btnActiveTex);
	} break;
	default: break;
	}
}

bool Button::isPressed() const
{
	return btnState == ACTIVE ? true : false;
}
