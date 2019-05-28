#ifndef _THREAT_H_
#define _THREAT_H_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include"Bullet.h"
#include"Data.h"
class Threat
{
private:
	sf::RenderWindow	    *m_window;
	sf::Sprite               m_sprite;
	sf::Texture              m_texture;

	Bullet					*m_bullet;
	sf::Texture              m_texture_bullet;

	bool					 m_check_collision = false;


public:
	Threat(sf::RenderWindow *window);
	~Threat();
	void update();
	void draw();

	void setCheckCollision(bool check){ this->m_check_collision = check; }
	bool getCheckCollision(){ return this->m_check_collision; }
	sf::Vector2f getPosition(){ return this->m_sprite.getPosition(); }
	void setPosition(int x, int y){ this->m_sprite.setPosition(x, y); }
	Bullet* getBullet(){ return this->m_bullet; }
	
};
#endif
