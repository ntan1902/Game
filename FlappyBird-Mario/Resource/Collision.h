#pragma once
#include <SFML/Graphics.hpp>

class Collision
{

public:
	Collision();
	~Collision();
public:
	bool CheckCollision(sf::Sprite bird, sf::Sprite object);
	bool CheckCollision(sf::Sprite bird, sf::Sprite object, float scale1, float scale2);

};

