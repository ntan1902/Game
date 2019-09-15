#include "HUD.h"



HUD::HUD(GameDataRef data) : m_Data(data)
{
	m_ScoreText.setFont(m_Data->assets.GetFont("Flappy Font"));
	m_ScoreText.setString("0");
	m_ScoreText.setCharacterSize(50);
	m_ScoreText.setFillColor(sf::Color::White);
	m_ScoreText.setOrigin(m_ScoreText.getGlobalBounds().width / 2,
						  m_ScoreText.getGlobalBounds().height / 2);
	m_ScoreText.setPosition(m_Data->window.getSize().x / 2, 
							m_Data->window.getSize().y / 10);

}


HUD::~HUD()
{
}

void HUD::Draw()
{
	m_Data->window.draw(m_ScoreText);
}

void HUD::UpdateScore(int score)
{
	m_ScoreText.setString(std::to_string(score));
}
