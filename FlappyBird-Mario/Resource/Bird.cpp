#include "Bird.h"
#include <iostream>
#include <math.h>

Bird::Bird(GameDataRef data): m_Data(data)
{
	m_IndexAnimate = 0;
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bird Frame 1"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bird Frame 2"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bird Frame 3"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bird Frame 4"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bird Die"));

	m_Bird.setTexture(m_AnimateFrames[0]);

	m_Bird.setPosition(m_Data->window.getSize().x / 4 - m_Bird.getGlobalBounds().width / 2,
					   m_Data->window.getSize().y / 2 - m_Bird.getGlobalBounds().height / 2);
	
	m_BirdState = 0;
	m_Rotation = 0;
	m_Gravity = 0;

	sf::Vector2f origin = sf::Vector2f(m_Bird.getGlobalBounds().width / 2, 
									   m_Bird.getGlobalBounds().height / 2);
	m_Bird.setOrigin(origin);
}


Bird::~Bird()
{
}
void Bird::DrawBird()
{
	m_Data->window.draw(m_Bird);
}

void Bird::Animate(float dt)
{
	int sizeFrame = m_AnimateFrames.size() - 1;
	if (m_Clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / sizeFrame )
	{
		m_IndexAnimate++;
		m_IndexAnimate %= sizeFrame;
		
		m_Bird.setTexture(m_AnimateFrames[m_IndexAnimate]);
		m_Clock.restart();
	}
}

void Bird::Update(float dt)
{
	if (m_BirdState == eFALLING)
	{
		
		m_Gravity += GRAVITY_SPEED * dt ;
		m_Rotation += ROTATION_SPEED * dt * 0.5f; 
		
		if (m_Rotation > 30.0f)
			m_Rotation = 30.0f;

		m_Bird.move(0, m_Gravity);
	}
	else if (m_BirdState == eFLYING)
	{
		m_Gravity = -FLYING_SPEED * dt;
		m_Rotation -= ROTATION_SPEED * dt * 12.0f; 
		
		if (m_Rotation < -30.0f)
			m_Rotation = -30.0f;
		
		m_Bird.move(0, m_Gravity);
	}
	m_Bird.setRotation(m_Rotation);

	if (m_MovementClock.getElapsedTime().asSeconds() > FLYING_DURATION )
	{
		m_BirdState = eFALLING;
		m_MovementClock.restart();
	}
	
	
}

void Bird::MoveUpDown(float dt, float DeltaY)
{
	sf::Vector2f newPosition = m_Bird.getPosition();
	newPosition.y += DeltaY * 25.0f;
	m_Bird.setPosition(newPosition);
}

void Bird::Tap()
{
	m_BirdState = eFLYING;

	m_MovementClock.restart();
}

void Bird::Die(float dt)
{
	m_Bird.setTexture(m_AnimateFrames[m_AnimateFrames.size() -1]);
	m_Gravity += GRAVITY_SPEED * dt;
	
	if(m_Bird.getPosition().y < LAND_COORD_Y - BIRD_HEIGHT)
		m_Bird.move(0, m_Gravity);

	m_Rotation += ROTATION_SPEED * dt * 10;
	m_Bird.setRotation(m_Rotation);
	if (m_Rotation > 70)
	{
		m_Rotation = 70;
	}
	
}
