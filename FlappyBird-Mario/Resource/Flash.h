#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ConstValue.h"
class Flash
{
private:
	GameDataRef m_Data;
	sf::RectangleShape m_Shape;
	bool m_bFlashOn;
public:
	Flash(GameDataRef data);
	~Flash();
public:
	void Show(float dt);
	void Draw();
};

