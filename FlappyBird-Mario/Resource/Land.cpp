#include "Land.h"
#include "ConstValue.h"
#include <iostream>
Land::Land(GameDataRef data) : m_Data(data)
{
	sf::Sprite sprite1(m_Data->assets.GetTexture("Land"));
	sf::Sprite sprite2(m_Data->assets.GetTexture("Land"));

	sprite1.setPosition(0.f, 
						m_Data->window.getSize().y - sprite1.getGlobalBounds().height);
	sprite2.setPosition(m_Data->window.getSize().x, 
						m_Data->window.getSize().y - sprite1.getGlobalBounds().height);

	m_Land.push_back(sprite1);
	m_Land.push_back(sprite2);
}

Land::~Land()
{
}
void Land::MoveLand(float dt)
{
	float movement = PIPE_MOVEMENT_SPEED * dt;
	for (int i = 0; i < m_Land.size(); i++)
	{
		m_Land[i].move(-movement, 0);
		if (m_Land[i].getPosition().x < 0 - m_Land[i].getGlobalBounds().width)
		{
			sf::Vector2f position(m_Data->window.getSize().x, m_Land[i].getPosition().y);
			m_Land[i].setPosition(position);
		}
	}
}
void Land::DrawLand()
{
	for (int i = 0; i < m_Land.size(); i++)
	{
		m_Data->window.draw(m_Land[i]);
	}
}
