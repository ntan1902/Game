#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ConstValue.h"
#include "Game.h"
#include "Bullet.h"
class Mario
{
private:
	GameDataRef m_Data;
	std::vector<std::shared_ptr<Bullet>> m_Bullet;

	std::vector<sf::Texture> m_AnimateFrames;
	int m_IndexAnimate;
	sf::Clock m_Clock;
	sf::Clock m_FireClock;
	sf::Sprite m_Mario;
	bool m_bFire;

	sf::SoundBuffer m_FireBallSoundBuffer;
	sf::Sound m_FireBallSound;

public:
	Mario(GameDataRef data);
	~Mario();
public:
	void DrawMario();
	void MoveUpDown(float dt, float DeltaY);
	void Animate(float dt);
	void Update(float dt);
	void Invisible(float dt);
	void Visible(float dt);
	void Die(float dt);
	sf::Sprite &GetSprite(){ return m_Mario; }

	std::vector<std::shared_ptr<Bullet>> &GetBullets() { return m_Bullet; }
};

