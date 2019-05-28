#include "ThreatTank.h"


ThreatTank::ThreatTank(sf::RenderWindow *window, sf::Texture &texture, sf::Texture &texture_bullet)
{
	this->m_window = window;

	this->m_sprite.setTexture(texture);
	this->m_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	this->m_sprite.setPosition(0, 0);

	this->m_bullet = new Bullet(window, texture_bullet, 0, 0);



}
void ThreatTank::update(int type)
{
	sf::Vector2f ThreatTank_position = this->m_sprite.getPosition();
	if (ThreatTank_position.x > 0 && this->m_check_collision == false)
	{
		this->m_sprite.setPosition(ThreatTank_position.x - 4, ThreatTank_position.y);
		if (type == 1)
		{
			this->m_bullet->MoveRightToLeft(ThreatTank_position.x - 12, ThreatTank_position.y - 14);
		}
		else
			this->m_bullet->MoveBottomRightToTopLeft(ThreatTank_position.x - 10, ThreatTank_position.y - 30);
	}
	else
	{
		float x = rand() % ((SCREEN_WIDTH + 800) - SCREEN_WIDTH + 1) + SCREEN_WIDTH;
		float y = SCREEN_HEIGHT / 2 + 210;
		this->m_sprite.setPosition(x, y);
		this->m_check_collision = false;
		if (type == 1)
		{
			this->m_bullet->MoveRightToLeft(ThreatTank_position.x - 12, ThreatTank_position.y - 14);
		}
		else
			this->m_bullet->MoveBottomRightToTopLeft(ThreatTank_position.x - 10, ThreatTank_position.y - 30);
	}

}
void ThreatTank::draw()
{
	this->m_window->draw(this->m_sprite);
	this->m_bullet->draw();

}
ThreatTank::~ThreatTank()
{
	delete this->m_bullet;
}

