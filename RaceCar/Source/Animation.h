#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<vector>
class Animation
{
private:
	sf::RenderWindow       *m_window;
	sf::Sprite              m_sprite;
	sf::Texture             m_texture;
	float                   m_speed;
	float                   Frame;
	std::vector<sf::IntRect>     Frames;
public:
	Animation(sf::RenderWindow *window, sf::Texture &t, int column, int line, int width, int height, float speed, int count, sf::Vector2f position);
	void update();
	void draw();
	bool checkEnd();

};

