#include "Collision.h"

#include "ConstValue.h"
#include <iostream>

Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::CheckCollision(sf::Sprite bird, sf::Sprite object)
{
	sf::IntRect rect1(bird.getPosition().x - BIRD_WIDTH / 2,
					  bird.getPosition().y - 5.f,
					  BIRD_WIDTH,
		              BIRD_HEIGHT);
	sf::IntRect rect2(object.getPosition().x,
					  object.getPosition().y,
					  object.getGlobalBounds().width,
					  object.getGlobalBounds().height);
	if (rect1.intersects(rect2))
	{
		return true;
	}
	return false;
}

bool Collision::CheckCollision(sf::Sprite bird, sf::Sprite object, float scale1, float scale2)
{
	object.setScale(scale1, scale2);

	sf::IntRect rect1(bird.getPosition().x - BIRD_WIDTH / 2,
					  bird.getPosition().y - BIRD_HEIGHT / 2,
					  BIRD_WIDTH,
					  BIRD_HEIGHT);
	sf::IntRect rect2(object.getPosition().x,
					  object.getPosition().y,
					  object.getGlobalBounds().width,
					  object.getGlobalBounds().height);
	
	if (rect1.intersects(rect2))
	{
	
		return true;
	}
	return false;
}
