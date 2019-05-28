#ifndef _PLAYER_H_
#define _PLAYER_H_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<vector>
#include"Bullet.h"
#include"Data.h"
#include"TimeGame.h"
#include<iostream>
class Player : public TimeGame
{
private:
	sf::RenderWindow       *m_window;
	
	sf::Texture             m_texture;
	sf::Sprite              m_sprite;

	sf::Texture				m_texture_fire;
	sf::Sprite              m_sprite_fire;
	bool                    fire = false;

	std::vector<Bullet*>	m_bullet;

	sf::Texture             m_texture_bullet_sphere;
	sf::Texture             m_texture_bullet_laser;
	
	sf::Texture             m_texture_heart;
	sf::Sprite              m_sprite_heart;
	int						m_heart = 5;

	sf::SoundBuffer         sound_buffer_fire;
	sf::Sound               sound_fire;
	bool                    mute = false;


public:
	Player(sf::RenderWindow *window);
	~Player();
	void update();
	void draw();
	void RemoveBullet(int index);
	sf::Vector2f getPosition() { return this->m_sprite.getPosition(); }
	int &getHeart(){ return this->m_heart; }
	std::vector<Bullet*> getBullet(){ return this->m_bullet; }
	void setMute(bool m){ this->mute = m; }

};
#endif
