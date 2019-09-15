#pragma once
#include <SFML/Graphics.hpp>
#include "ConstValue.h"
#include "Game.h"
class Bird
{
private:
	GameDataRef m_Data;

	std::vector<sf::Texture> m_AnimateFrames;
	int m_IndexAnimate;

	sf::Clock m_Clock;
	sf::Clock m_MovementClock;


	int m_BirdState;
	float m_Rotation;
	float m_Gravity;

	sf::Sprite m_Bird;

public:
	Bird(GameDataRef data);
	~Bird();
public:
	void DrawBird();
	void Animate(float dt);
	void Update(float dt);
	void MoveUpDown(float dt, float DeltaY);
	void Tap();
	void Die(float dt);
	sf::Sprite GetSprite() const { return m_Bird; }


};

