#include "MainMenuState.h"
#include "ConstValue.h"
#include "GameState.h"
#include <sstream>
#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : m_Data(data)
{
}


MainMenuState::~MainMenuState()
{
}

void MainMenuState::Init()
{
	m_Data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	m_Data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
	m_Data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);


	m_Background.setTexture(m_Data->assets.GetTexture("Main Menu Background"));
	m_Title.setTexture(m_Data->assets.GetTexture("Game Title"));
	m_PlayButton.setTexture(m_Data->assets.GetTexture("Play Button"));

	m_Title.setPosition((SCREEN_WIDTH / 2) - (m_Title.getGlobalBounds().width / 2),
						(m_Title.getGlobalBounds().height / 2));
	m_PlayButton.setPosition((SCREEN_WIDTH / 2) - (m_PlayButton.getGlobalBounds().width / 2), 
							(SCREEN_HEIGHT / 2) - (m_PlayButton.getGlobalBounds().height / 2));
}

void MainMenuState::HandleInput()
{
	sf::Event event;
	while (m_Data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			m_Data->window.close();
		
		if (m_Data->input.IsSpriteClicked(m_PlayButton, sf::Mouse::Left, m_Data->window))
			m_Data->machine.AddState(StateRef(new GameState(m_Data)));
	}
}

void MainMenuState::Update(float dt)
{
	
}

void MainMenuState::Draw(float dt)
{
	m_Data->window.clear();
	m_Data->window.draw(m_Background);
	m_Data->window.draw(m_Title);
	m_Data->window.draw(m_PlayButton);

	m_Data->window.display();
}
