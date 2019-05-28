#ifndef _BOSS_H_
#define _BOSS_H_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<cstdlib>
#include<ctime>
#include"Bullet.h"
#include"Data.h"
#include"Animation.h"
#include"TimeGame.h"
#include<iostream>
class Boss : TimeGame
{
private:
	sf::RenderWindow	    *m_window;


	std::vector<Bullet*>	 m_bullet;
	sf::Texture              m_texture_bullet;
	sf::Texture              m_texture_bullet_45;
	sf::Texture              m_texture_bullet_minus_45;

	sf::Texture              m_texture_animation;
	

	Animation               *m_animation_boss;

	sf::Texture              m_texture_heart;
	sf::Sprite               m_sprite_heart;
	int                      m_heart = 20;
public:
	Boss(sf::RenderWindow *window);
	~Boss();
	void update();
	void draw();
	

	void RemoveBullet(int index);
	std::vector<Bullet*> getBullet(){ return this->m_bullet; }
	Animation *getAnimationBoss(){ return this->m_animation_boss; }
	int& getHeart(){ return this->m_heart; }


};
#endif
