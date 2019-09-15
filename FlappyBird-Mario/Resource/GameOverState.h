#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"


class GameOverState : public State
{
private:
	GameDataRef m_Data;

	sf::Sprite m_Background;
	sf::Sprite m_GameOverTitle;
	sf::Sprite m_GameOverBody;
	sf::Sprite m_RetryButton;
	sf::Sprite m_Medal;

	sf::Text m_ScoreText;
	sf::Text m_HighScoreText;

	int m_Score;
	int m_HighScore;
public:
	GameOverState(GameDataRef data, int score);
	~GameOverState();
public:
	void LoadHighScore();
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
};

