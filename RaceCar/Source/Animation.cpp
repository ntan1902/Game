#include "Animation.h"


Animation::Animation(sf::RenderWindow *window, sf::Texture &t, int column, int line, int width, int height, float speed, int count, sf::Vector2f position )
{
	this->m_window = window;
	this->m_speed = speed;
	this->Frame = 0;

	for (int i = 0; i < count; i++)
	{
		this->Frames.push_back(sf::IntRect(column + width*i, line, width, height));
	}
	this->m_sprite.setTexture(t);
	this->m_sprite.setOrigin(width / 2, height / 2);
	this->m_sprite.setPosition(position.x, position.y);
	this->m_sprite.setTextureRect(Frames[0]);
}
void Animation::update()
{
	this->Frame += this->m_speed;
	int n = this->Frames.size();
	if (this->Frame > n)
		this->Frame -= n;
	this->m_sprite.setTextureRect(this->Frames[(int)this->Frame]);
}
void Animation::draw()
{
	this->m_window->draw(this->m_sprite);
}

bool Animation::checkEnd()
{
	return this->Frame + this->m_speed >= this->Frames.size();
}





