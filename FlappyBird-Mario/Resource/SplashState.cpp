#include "SplashState.h"
#include "ConstValue.h"
#include "MainMenuState.h"
#include <sstream>
#include <iostream>

SplashState::SplashState(GameDataRef data) : m_Data(data)
{
}


SplashState::~SplashState()
{
}

void SplashState::Init()
{
	m_Data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	m_Background.setTexture(m_Data->assets.GetTexture("Splash State Background"));
}

void SplashState::HandleInput()
{
	sf::Event event;
	while (m_Data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			m_Data->window.close();
	}
}

void SplashState::Update(float dt)
{
	if (m_Clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)));
	}
}

void SplashState::Draw(float dt)
{
	m_Data->window.clear();
	m_Data->window.draw(m_Background);
	m_Data->window.display();
}
