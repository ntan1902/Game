#include "Mario.h"
#include <iostream>
#include <math.h>

Mario::Mario(GameDataRef data) : m_Data(data)
{
	m_bFire = false;
	m_IndexAnimate = 0;
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Mario Frame 1"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Mario Frame 2"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Mario Frame 3"));

	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Mario Frame 1"));

	if (!m_FireBallSoundBuffer.loadFromFile(FIRE_BALL_SOUND_FILEPATH))
		std::cout << "Error loading Fire Ball Sound\n";
	m_FireBallSound.setBuffer(m_FireBallSoundBuffer);
	m_FireBallSound.setVolume(30);

	m_Mario.setTexture(m_AnimateFrames[0]);

	sf::Vector2f origin = sf::Vector2f(m_Mario.getGlobalBounds().width / 2,
									   m_Mario.getGlobalBounds().height / 2);
	m_Mario.setOrigin(origin);

	m_Mario.setPosition(m_Data->window.getSize().x - m_Mario.getGlobalBounds().width/2,
						m_Data->window.getSize().y / 2 + 25.0f);

}


Mario::~Mario()
{
}
void Mario::DrawMario()
{
	m_Data->window.draw(m_Mario);
	for (int i = 0; i < m_Bullet.size(); i++)
	{
		m_Bullet[i]->Draw();
	}
}

void Mario::MoveUpDown(float dt, float DeltaY)
{
	sf::Vector2f newPosition = m_Mario.getPosition();
	newPosition.y += DeltaY * 50.0f;
	m_Mario.setPosition(newPosition);
}

void Mario::Animate(float dt)
{
	if (m_bFire)
	{
		int sizeFrame = m_AnimateFrames.size();
		if (m_Clock.getElapsedTime().asSeconds() > MARIO_ANIMATION_DURATION / sizeFrame)
		{
			m_IndexAnimate++;
			m_IndexAnimate %= sizeFrame;

			m_Mario.setTexture(m_AnimateFrames[m_IndexAnimate]);
			
			if (m_IndexAnimate == sizeFrame - 1)
			{
				std::shared_ptr<Bullet> bull = std::make_shared<Bullet>(m_Data, 
																		m_Mario.getPosition());
				m_Bullet.push_back(bull);
				m_FireBallSound.play();
			}

			m_Clock.restart();
		}
	}

}

void Mario::Update(float dt)
{
	if (m_FireClock.getElapsedTime().asSeconds() > TIME_MARIO_FIRE)
	{
		m_bFire = true;
	}
	if (m_IndexAnimate == m_AnimateFrames.size() - 1)
	{
		m_IndexAnimate = 0;
		m_bFire = false;
		m_FireClock.restart();
	}
	for (int i = 0; i < m_Bullet.size(); i++)
	{
		m_Bullet[i]->Fire(dt);
		m_Bullet[i]->Animate(dt);
	}
	for (int i = 0; i < m_Bullet.size(); i++)
	{
		sf::Sprite bullet = m_Bullet[i]->GetSprite();
		if (bullet.getPosition().x < 0 - bullet.getGlobalBounds().width)
		{
			m_Bullet.erase(m_Bullet.begin() + i);

		}
	}
}

void Mario::Invisible(float dt)
{


	float movement = PIPE_MOVEMENT_SPEED * dt;
	m_Mario.move(movement, 0);
	
}

void Mario::Visible(float dt)
{
	float movement = PIPE_MOVEMENT_SPEED * dt;
	m_Mario.move(-movement, 0);
}

void Mario::Die(float dt)
{
	
}
