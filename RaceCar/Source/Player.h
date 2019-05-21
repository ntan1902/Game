#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
class Player
{
private:
	sf::RenderWindow	*m_window;
	sf::Texture		     m_texture_car;
	sf::Sprite           m_sprite_car;

	sf::Texture          m_texture_heart;
	sf::Sprite           m_sprite_heart;
	int					 m_count_heart;
public:
	Player(sf::RenderWindow *window);
	void                 update();
	void                 draw();
	int                  &getCountHeart();
	sf::Vector2f         getPosition();
};

