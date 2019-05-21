#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<cstdlib>
#include<time.h>
class Threat
{
private:
	sf::RenderWindow    *m_window;
	sf::Texture		     m_texture;
	sf::Sprite           m_sprite;

public:
	Threat(sf::RenderWindow *window, sf::Texture& texture);
	void update();
	void draw();
	sf::Vector2f getPosition();
};

