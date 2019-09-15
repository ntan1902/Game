#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "Mario.h"
#include "Bullet.h"
#include "HUD.h"

class GameState : public State
{
private:
	GameDataRef m_Data;
	sf::Clock m_Clock;
	sf::Sprite m_Background;
	sf::Sprite m_Ready;

	int m_GameStates;
	int m_Score;	
	float m_RunningTimeBird;
	float m_RunningTimeMario;

	float m_LastPositionOfMario;
	bool m_bVisibleMario;
	sf::Clock m_MarioInvisibleClock;

	std::unique_ptr<Pipe> m_Pipe;
	std::unique_ptr<Pipe> m_MarioPipe;
	std::unique_ptr<Land> m_Land;
	std::unique_ptr<Bird> m_Bird;
	std::unique_ptr<Collision> m_Collision;
	std::unique_ptr<Mario> m_Mario;
	std::unique_ptr<Flash> m_Flash;
	std::unique_ptr<HUD> m_HUD;

	sf::SoundBuffer m_HitSoundBuffer;
	sf::SoundBuffer m_PointSoundBuffer;
	sf::SoundBuffer m_WingSoundBuffer;

	sf::Sound m_HitSound;
	sf::Sound m_PointSound;
	sf::Sound m_WingSound;



public:
	GameState(GameDataRef data);
	~GameState();
public:
	virtual void Init() override;
	virtual void HandleInput() override;
	virtual void Update(float dt) override;
	virtual void Draw(float dt) override;
};

