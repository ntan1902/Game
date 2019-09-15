#pragma once
#include <SFML/Graphics.hpp>
#include "ConstValue.h"
#include "Game.h"
class HUD
{
private:
	GameDataRef m_Data;
	sf::Text m_ScoreText;
public:
	HUD(GameDataRef data);
	~HUD();
public:
	void Draw();
	void UpdateScore(int score);
};

