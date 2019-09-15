#pragma once
#include<SFML/Graphics.hpp>
#include "Game.h"
class Bullet
{
private: 
	GameDataRef m_Data;

	std::vector<sf::Texture> m_AnimateFrames;
	int m_IndexAnimate;

	sf::Clock m_Clock;

	sf::Sprite m_Bullet;

	int m_Random;

public:
	Bullet(GameDataRef data, sf::Vector2f position);
	~Bullet();
public:
	void Animate(float dt);
	void Draw();
	void Fire(float dt);
	sf::Sprite GetSprite() { return m_Bullet; }
};

