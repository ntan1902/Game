#include "Game.h"
#include "SplashState.h"
Game::Game(int width, int height, std::string title)
{
	
	m_Data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	m_Data->window.setFramerateLimit(120);
	m_Data->machine.AddState(StateRef(new SplashState(m_Data)));
	Run();
}

Game::~Game()
{
}
void Game::Run()
{
	float newTime, frameTime, interpolation;
	float currentTime = m_Clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	while (m_Data->window.isOpen())
	{
		m_Data->machine.ProcessStateChanges();

		newTime = m_Clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= dt)
		{
			m_Data->machine.GetActiveState()->HandleInput();
			m_Data->machine.GetActiveState()->Update(dt);

			accumulator -= dt;
		}
		interpolation = accumulator / dt;
		m_Data->machine.GetActiveState()->Draw(interpolation);
	}
}
