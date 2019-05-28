#include "Bullet.h"


Bullet::Bullet(sf::RenderWindow *window, sf::Texture &texture, float coord_x, float coord_y)
{
	this->m_window = window;
	
	this->m_sprite.setTexture(texture);
	this->m_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	this->m_sprite.setPosition(coord_x, coord_y);
	
}
void Bullet::update()   //player
{
	this->m_sprite.move(10, 0);
}

void Bullet::MoveRightToLeft(float coord_x, float coord_y )   //plane threat
{
	sf::Vector2f Bullet_position = this->m_sprite.getPosition();
	if (Bullet_position.x > 0 && this->m_check_collision == false)
	{
		this->m_sprite.setPosition(Bullet_position.x - 7, Bullet_position.y);
	}
	else
	{
		this->m_sprite.setPosition(coord_x - 40, coord_y + 15);
		this->m_check_collision = false;
	}
}

void Bullet::MoveBottomRightToTopLeft(float coord_x, float coord_y)  // tank threat
{
	sf::Vector2f Bullet_position = this->m_sprite.getPosition();
	if (Bullet_position.x > 0 && Bullet_position.y > 30 && this->m_check_collision == false)
	{
		this->m_sprite.setPosition(Bullet_position.x - 7, Bullet_position.y - 3);
	}
	else
	{
		this->m_sprite.setPosition(coord_x - 40, coord_y + 15);
		this->m_check_collision = false;
	}
}


void Bullet::MoveFromBoss()
{
	this->m_sprite.move(-10, 0);
}

void Bullet::MoveFromBoss45()
{
	this->m_sprite.move(-7, -3);
}

void Bullet::MoveFromBossMinus45()
{
	this->m_sprite.move(-7, 3);
}

void Bullet::draw()
{
	this->m_window->draw(this->m_sprite);
}

