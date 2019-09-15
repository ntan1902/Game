#include "GameOverState.h"
#include "ConstValue.h"
#include "GameState.h"
#include <fstream>
#include <iostream>

GameOverState::GameOverState(GameDataRef data, int score) : m_Data(data)
{
	m_Score = score;
	m_HighScore = score;
}


GameOverState::~GameOverState()
{
}

void GameOverState::LoadHighScore()
{
	std::ifstream fi;
	fi.open(HIGH_SCORE_FILEPATH);
	if (fi.is_open())
	{
		fi >> m_HighScore;
	}
	fi.close();
	if (m_Score > m_HighScore)
	{
		m_HighScore = m_Score;
		std::ofstream fo;
		fo.open(HIGH_SCORE_FILEPATH);
		if (fo.is_open())
		{
			fo << m_HighScore;
		}
		fo.close();
	}
}

void GameOverState::Init()
{
	LoadHighScore();
	m_Data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);
	m_Data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
	m_Data->assets.LoadTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
	m_Data->assets.LoadTexture("Bronze Medal", BRONZE_MEDAL_FILEPATH);
	m_Data->assets.LoadTexture("Silver Medal", SILVER_MEDAL_FILEPATH);
	m_Data->assets.LoadTexture("Gold Medal", GOLD_MEDAL_FILEPATH);
	m_Data->assets.LoadTexture("Platinum Medal", PLATINUM_MEDAL_FILEPATH);

	m_Background.setTexture(m_Data->assets.GetTexture("Game Over Background"));
	m_GameOverTitle.setTexture(m_Data->assets.GetTexture("Game Over Title"));
	m_GameOverBody.setTexture(m_Data->assets.GetTexture("Game Over Body"));
	m_RetryButton.setTexture(m_Data->assets.GetTexture("Play Button"));

	m_GameOverBody.setPosition(m_Data->window.getSize().x / 2 - m_GameOverBody.getGlobalBounds().width / 2,
							   m_Data->window.getSize().y / 2 - m_GameOverBody.getGlobalBounds().height / 1.5);
	m_GameOverTitle.setPosition(m_Data->window.getSize().x / 2 - m_GameOverTitle.getGlobalBounds().width / 2,
							    m_GameOverBody.getPosition().y - m_GameOverTitle.getGlobalBounds().height * 1.2f);
	m_RetryButton.setPosition(m_Data->window.getSize().x / 2 - m_RetryButton.getGlobalBounds().width / 2,
							  m_GameOverBody.getPosition().y + m_GameOverBody.getGlobalBounds().height + 
							  m_RetryButton.getGlobalBounds().height * 0.5);

	m_ScoreText.setFont(m_Data->assets.GetFont("Flappy Font"));
	m_ScoreText.setString(std::to_string(m_Score));
	m_ScoreText.setCharacterSize(30);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setOrigin(m_ScoreText.getGlobalBounds().width / 2,
						  m_ScoreText.getGlobalBounds().height / 2);
	m_ScoreText.setPosition(m_Data->window.getSize().x / 10 * 7.25f,
							m_Data->window.getSize().y / 2 - 50.0f); 

	m_HighScoreText.setFont(m_Data->assets.GetFont("Flappy Font"));
	m_HighScoreText.setString(std::to_string(m_HighScore));
	m_HighScoreText.setCharacterSize(30);
	m_HighScoreText.setFillColor(sf::Color::White);
	m_HighScoreText.setOrigin(m_HighScoreText.getGlobalBounds().width / 2,
							  m_HighScoreText.getGlobalBounds().height / 2);
	m_HighScoreText.setPosition(m_Data->window.getSize().x / 10 * 7.25f,
								m_Data->window.getSize().y / 2 + 10.0f);
	if (m_Score >= PLATINUM_SCORE)
	{
		m_Medal.setTexture(m_Data->assets.GetTexture("Platinum Medal"));
	}
	else if (m_Score >= GOLD_SCORE)
	{
		m_Medal.setTexture(m_Data->assets.GetTexture("Gold Medal"));
	}
	else if (m_Score >= SILVER_SCORE)
	{
		m_Medal.setTexture(m_Data->assets.GetTexture("Silver Medal"));
	}
	else if (m_Score >= BRONZE_SCORE)
	{
		m_Medal.setTexture(m_Data->assets.GetTexture("Bronze Medal"));
	}
	m_Medal.setPosition(125.0f, 250.0f);
}

void GameOverState::HandleInput()
{
	sf::Event event;
	while (m_Data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			m_Data->window.close();
		}
		if (m_Data->input.IsSpriteClicked(m_RetryButton, sf::Mouse::Left, m_Data->window))
		{
			m_Data->machine.AddState(StateRef(new GameState(m_Data)));
		}
	}
}

void GameOverState::Update(float dt)
{
	
}

void GameOverState::Draw(float dt)
{
	m_Data->window.clear();
	m_Data->window.draw(m_Background);
	m_Data->window.draw(m_GameOverTitle);
	m_Data->window.draw(m_GameOverBody);
	m_Data->window.draw(m_RetryButton);
	m_Data->window.draw(m_ScoreText);
	m_Data->window.draw(m_HighScoreText);
	m_Data->window.draw(m_Medal);

	m_Data->window.display();
}
