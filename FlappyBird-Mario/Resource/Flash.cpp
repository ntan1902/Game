#include "Flash.h"

Flash::Flash(GameDataRef data) : m_Data(data)
{
	m_Shape = sf::RectangleShape(sf::Vector2f(m_Data->window.getSize()));
	m_Shape.setFillColor(sf::Color(255, 255, 255, 0));
	m_bFlashOn = true;
}

Flash::~Flash()
{
}

void Flash::Show(float dt)
{
	if (m_bFlashOn)
	{
		float alpha = (int)m_Shape.getFillColor().a + (FLASH_SPEED * dt);
		if (alpha >= 255)
		{
			alpha = 255;
			m_bFlashOn = false;
		}
		m_Shape.setFillColor(sf::Color(255, 255, 255, alpha));

	}
	else 
	{ 
		float alpha = (int)m_Shape.getFillColor().a - (FLASH_SPEED * dt);
		if (alpha <= 0)
		{
			alpha = 0;
		}
		m_Shape.setFillColor(sf::Color(255, 255, 255, alpha));
	}
}

void Flash::Draw()
{
	m_Data->window.draw(m_Shape);
}
