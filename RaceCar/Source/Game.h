#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include"Player.h"
#include"Threat.h"
#include<list>
#include<string>
#include"Animation.h"
class Game
{
private:
	sf::RenderWindow *m_window;
	sf::Texture		  m_texture_threat_2;
	sf::Texture		  m_texture_threat_3;
	sf::Texture		  m_texture_threat_4;
	sf::Texture       m_texture_explosion;
	Player           *m_player;

	sf::Clock         m_clock;
	sf::Time          m_time;
	
	std::list<Threat> m_threat;

	unsigned int	  m_score;
	sf::Font          m_font;
	sf::Text          m_text;

	std::list<Animation>    m_explosion;
public:
	Game(sf::RenderWindow *window);
	~Game();
	bool update();
	void draw();
};

