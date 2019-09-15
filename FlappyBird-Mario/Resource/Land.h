#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
class Land
{
private:
	GameDataRef m_Data;
	std::vector<sf::Sprite> m_Land;
public:
	Land(GameDataRef data);
	~Land();
public:
	void MoveLand(float dt);
	void DrawLand();
	std::vector<sf::Sprite> GetSprites() const { return m_Land; }
};

