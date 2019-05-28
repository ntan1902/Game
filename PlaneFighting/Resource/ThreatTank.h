#ifndef _THREATTANK_H_
#define _THREATTANK_H_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include"Bullet.h"
#include"Data.h"
class ThreatTank
{
private:
	sf::RenderWindow	    *m_window;
	sf::Sprite               m_sprite;
	sf::Texture              m_texture;

	Bullet					*m_bullet;

	bool					 m_check_collision = false;


public:
	ThreatTank(sf::RenderWindow *window, sf::Texture &texture, sf::Texture &texture_bullet);
	~ThreatTank();
	void update(int type);
	void draw();

	void setCheckCollision(bool check){ this->m_check_collision = check; }
	bool getCheckCollision(){ return this->m_check_collision; }
	sf::Vector2f getPosition(){ return this->m_sprite.getPosition(); }
	void setPosition(int x, int y){ this->m_sprite.setPosition(x, y); }
	Bullet* getBullet(){ return this->m_bullet; }

};
#endif


