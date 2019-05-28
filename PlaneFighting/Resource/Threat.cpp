#include "Threat.h"


Threat::Threat(sf::RenderWindow *window)
{
	this->m_window = window;

	this->m_texture.loadFromFile(file_name_plane_threat);
	this->m_texture.setSmooth(true);
	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	this->m_sprite.setPosition(0, 0);

	this->m_texture_bullet.loadFromFile(file_name_sphere_threat);
	this->m_texture.setSmooth(true);

	this->m_bullet = new Bullet(window, this->m_texture_bullet, 0, 0);
	
	

}
void Threat::update()
{
	sf::Vector2f threat_position = this->m_sprite.getPosition();
	if (threat_position.x > 0 && this->m_check_collision == false)
	{
		this->m_sprite.setPosition(threat_position.x - 4, threat_position.y);
		this->m_bullet->MoveRightToLeft(threat_position.x - 4, threat_position.y);
	}
	else
	{	
		float x = rand() % ((SCREEN_WIDTH + 800) - SCREEN_WIDTH + 1) + SCREEN_WIDTH;
		float y = rand() % ((SCREEN_HEIGHT -120) - (THREAT_HEIGHT/2 + 40) + 1) + THREAT_HEIGHT/2 + 40;
		this->m_sprite.setPosition(x, y);
		this->m_bullet->MoveRightToLeft(threat_position.x - 4, threat_position.y);
		this->m_check_collision = false;
	}

}
void Threat::draw()
{
	this->m_window->draw(this->m_sprite);
	this->m_bullet->draw();

}
Threat::~Threat()
{
	delete this->m_bullet;
}

