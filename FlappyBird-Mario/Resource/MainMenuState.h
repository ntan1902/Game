#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class MainMenuState : public State
{
private:
	GameDataRef m_Data;
	sf::Sprite m_Background;
	sf::Sprite m_Title;
	sf::Sprite m_PlayButton;
public:
	MainMenuState(GameDataRef data);
	~MainMenuState();
public:
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
};

