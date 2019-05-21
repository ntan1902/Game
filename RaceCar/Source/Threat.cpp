#include "Threat.h"


Threat::Threat(sf::RenderWindow *window, sf::Texture& texture)
{
	this->m_window = window;
	this->m_sprite.setTexture(texture);
	this->m_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	this->m_sprite.setRotation(180);

	//Xuất hiện ngẫu nhiên xe trong tọa độ x[25,275]
	float x = std::rand() % (275 - 25 + 1) + 25;
	this->m_sprite.setPosition(x, 0);
}

void Threat::update()
{
	this->m_sprite.move(0,0.5);
}
void Threat::draw()
{
	this->m_window->draw(this->m_sprite);
}
sf::Vector2f Threat::getPosition()
{
	return this->m_sprite.getPosition();
}