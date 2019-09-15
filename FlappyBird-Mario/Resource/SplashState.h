#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
class SplashState : public State
{
private:
	GameDataRef m_Data;
	sf::Clock m_Clock;
	sf::Sprite m_Background;
public:
	SplashState(GameDataRef data);
	~SplashState();
public:
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
};

