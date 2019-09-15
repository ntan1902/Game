#include "Bullet.h"
#include "ConstValue.h"


Bullet::Bullet(GameDataRef data, sf::Vector2f position): m_Data(data)
{
	m_Random = rand() % 3;
	m_IndexAnimate = 0;
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bullet Frame 1"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bullet Frame 2"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bullet Ex 1"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bullet Ex 2"));
	m_AnimateFrames.push_back(m_Data->assets.GetTexture("Bullet Ex 3"));


	m_Bullet.setTexture(m_AnimateFrames[0]);

	m_Bullet.setPosition(position.x - 30, position.y - 20);
	/*sf::Vector2f origin = sf::Vector2f(m_Bullet.getGlobalBounds().width / 2,
		m_Bullet.getGlobalBounds().height / 2);
	m_Bullet.setOrigin(origin);*/
}


Bullet::~Bullet()
{
}

void Bullet::Animate(float dt)
{
	int sizeFrame = m_AnimateFrames.size();
	if (m_Clock.getElapsedTime().asSeconds() > BULLET_ANIMATION_DURATION / sizeFrame)
	{
		m_IndexAnimate++;
		m_IndexAnimate %= sizeFrame;

		m_Bullet.setTexture(m_AnimateFrames[m_IndexAnimate]);
		m_Clock.restart();
	}
}

void Bullet::Draw()
{
	m_Data->window.draw(m_Bullet);
}

void Bullet::Fire(float dt)
{
	float movement = BULLET_SPEED * dt;
	if(m_Random == 0)
		m_Bullet.move(-movement, movement/3);
	else if(m_Random == 1)
		m_Bullet.move(-movement, 0);
	else
		m_Bullet.move(-movement, -movement/3);


}