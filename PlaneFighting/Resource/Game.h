#ifndef _GAME_H_
#define _GAME_H_

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include"Player.h"
#include"Bullet.h"
#include"Threat.h"
#include"Animation.h"
#include<iostream>
#include"Data.h"
#include"TimeGame.h"
#include"ThreatTank.h"
#include"Boss.h"
class Game : public TimeGame
{
private:
	sf::RenderWindow             *m_window;
	Player                       *m_player;
	
	std::vector<Threat*>		  m_threat;
	std::vector<ThreatTank*>      m_threat_tank;
	Boss                         *m_boss;


	std::vector<Animation*>       m_list_animation;
	sf::Texture                   m_texture_animation_1;
	sf::Texture                   m_texture_animation_2;
	sf::Texture                   m_texture_threat_tank_1;

	sf::Texture                   m_texture_threat_tank_2;
	sf::Texture                   m_texture_bullet_sphere;    //bullet of tank 2
	sf::Texture                   m_texture_bullet_laser;     //bullet of tank 1

	sf::Texture                   m_texture_background;
	sf::Sprite                    m_sprite_background;
								  
	sf::Texture                   m_texture_background_2;
	sf::Sprite                    m_sprite_background_2;
								  
	sf::Texture                   m_texture_sound;
	sf::Sprite                    m_sprite_sound;
	sf::Texture                   m_texture_sound_mute;
	sf::Sprite                    m_sprite_sound_mute;
	int                           m_count_mute_sound = 0;
								  
	sf::SoundBuffer               m_sound_buffer_explosion;
	sf::Sound                     m_sound_explosion;

	unsigned int	              m_mark = 0;
	sf::Font                      m_font;
	sf::Text                      m_text;

	bool                          m_final = false;
	int                           m_threatOffScreen = 0;

public:
	Game(sf::RenderWindow *window);
	~Game();
	int update(int x_offset);
	int update_final();

	bool checkCollision(sf::Vector2f object_1, sf::Vector2f object_2, const int object_1_width, const int object_1_height, const int object_2_width, const int object_2_height, int &x, int &y, int &x_explosion, int &y_explosion);
	void handleCollision();
	void draw();
	int &getCountMute(){ return this->m_count_mute_sound; }
	void setFinal(bool fi){ this->m_final = fi; }
	unsigned int getMark(){ return this->m_mark; }
	int getThreatOffScreen(){ return this->m_threatOffScreen; }
};


#endif
