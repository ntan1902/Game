#include "GameState.h"
#include "ConstValue.h"

#include "GameOverState.h"
#include <iostream>

GameState::GameState(GameDataRef data) : m_Data(data)
{
}


GameState::~GameState()
{
}

void GameState::Init()
{
	m_GameStates = eREADY;

	m_Data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
	m_Data->assets.LoadTexture("Game Ready", GAME_READY_FILEPATH);

	m_Data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
	m_Data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
	m_Data->assets.LoadTexture("Pipe Scoring", PIPE_SCORING_FILEPATH);


	m_Data->assets.LoadTexture("Land", LAND_FILEPATH);

	m_Data->assets.LoadTexture("Bird Die", BIRD_DIE_FILEPATH);
	m_Data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
	m_Data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
	m_Data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
	m_Data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);

	m_Data->assets.LoadTexture("Mario Frame 1", MARIO_FRAME_1_FILEPATH);
	m_Data->assets.LoadTexture("Mario Frame 2", MARIO_FRAME_2_FILEPATH);
	m_Data->assets.LoadTexture("Mario Frame 3", MARIO_FRAME_3_FILEPATH);
	m_Data->assets.LoadTexture("Bullet Frame 1", BULLET_FRAME_1_FILEPATH);
	m_Data->assets.LoadTexture("Bullet Frame 2", BULLET_FRAME_2_FILEPATH);
	m_Data->assets.LoadTexture("Bullet Ex 1", BULLET_EX_1_FILEPATH);
	m_Data->assets.LoadTexture("Bullet Ex 2", BULLET_EX_2_FILEPATH);
	m_Data->assets.LoadTexture("Bullet Ex 3", BULLET_EX_3_FILEPATH);
	
	m_Data->assets.LoadFont("Flappy Font", FONT_FILEPATH);

	if (!m_HitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
		std::cout << "Error loading Hit Sound\n";
	if (!m_PointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
		std::cout << "Error loading Point Sound\n";
	if (!m_WingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
		std::cout << "Error loading Wing Sound\n";
	m_HitSound.setBuffer(m_HitSoundBuffer);
	m_PointSound.setBuffer(m_PointSoundBuffer);
	m_WingSound.setBuffer(m_WingSoundBuffer);

	m_HitSound.setVolume(30);
	m_PointSound.setVolume(30);
	m_WingSound.setVolume(30);


	m_Land = std::make_unique<Land>(m_Data);
	m_Pipe = std::make_unique<Pipe>(m_Data);
	m_MarioPipe = std::make_unique<Pipe>(m_Data);
	m_Bird = std::make_unique<Bird>(m_Data);
	m_Collision = std::make_unique<Collision>();
	m_Flash = std::make_unique<Flash>(m_Data);
	m_Mario = std::make_unique<Mario>(m_Data);
	m_HUD = std::make_unique<HUD>(m_Data);
	

	sf::Sprite sprite = m_Mario->GetSprite();
	m_MarioPipe->SpawnMarioPipe(sprite.getPosition().x - 25);

	m_Score = 0;
	m_HUD->UpdateScore(m_Score);
	m_RunningTimeBird = 0;
	m_RunningTimeMario = 0;
	m_bVisibleMario = true;
	m_Background.setTexture(m_Data->assets.GetTexture("Game Background"));
	m_Ready.setTexture(m_Data->assets.GetTexture("Game Ready"));
	m_Ready.setPosition(m_Data->window.getSize().x / 2 - m_Ready.getGlobalBounds().width / 2 + 5.0f,
						m_Data->window.getSize().y / 2 - m_Ready.getGlobalBounds().height * 1.1f );
}

void GameState::HandleInput()
{
	sf::Event event;
	while (m_Data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			m_Data->window.close();
		}
		if (m_Data->input.IsSpriteClicked(m_Background, sf::Mouse::Left, m_Data->window))
		{
			if (m_GameStates != eGAMEOVER)
			{
				m_Bird->Tap();
				m_WingSound.play();
				if (m_GameStates == eREADY)
				{
					m_LastPositionOfMario = m_Mario->GetSprite().getPosition().x;
					m_MarioInvisibleClock.restart();
					m_bVisibleMario = false;
					m_GameStates = ePLAYING;
				}
			}
		}

	}

}

void GameState::Update(float dt)
{
	#pragma region READY
	if (m_GameStates == eREADY)
	{
		m_Land->MoveLand(dt);
		m_Bird->Animate(dt);


		float DeltaY = std::sin(m_RunningTimeBird + dt) - std::sin(m_RunningTimeBird);
		m_Bird->MoveUpDown(dt, DeltaY);
		DeltaY = std::cos(m_RunningTimeMario + dt) - std::cos(m_RunningTimeMario);
		m_MarioPipe->MoveUpDown(dt, DeltaY);
		m_Mario->MoveUpDown(dt, DeltaY);
		m_RunningTimeBird += dt * 10.0f;
		m_RunningTimeMario += dt;
	}
	#pragma endregion

	#pragma region PLAYING
	if (m_GameStates == ePLAYING)
	{
		/*To check collision*/
		sf::Sprite Bird = m_Bird->GetSprite();
		std::vector<std::shared_ptr<Bullet>> &bullet = m_Mario->GetBullets();
		std::vector<sf::Sprite> Land = m_Land->GetSprites();
		std::vector<sf::Sprite> Pipe = m_Pipe->GetSprites();
		std::vector<sf::Sprite> &PipeScoring = m_Pipe->GetSpritesScoring();

		if (!m_bVisibleMario)
		{
			for (int i = 0; i < bullet.size(); i++)
			{
				bullet[i]->Fire(dt);
				bullet[i]->Animate(dt);
			}
			if (m_Mario->GetSprite().getPosition().x <
				m_Data->window.getSize().x + m_Mario->GetSprite().getGlobalBounds().width / 2)
			{
				m_MarioPipe->Invisible(dt);
				m_Mario->Invisible(dt);
			}
			if (m_Clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				m_Pipe->RandomY();
				m_Pipe->SpawnBottomPipe();
				m_Pipe->SpawnTopPipe();
				m_Clock.restart();
			}
			if (m_Score % 10 == 0 && m_Score != 0)
			{
				m_MarioInvisibleClock.restart();
				m_bVisibleMario = true;
			}
		}
		else
		{
			if (m_LastPositionOfMario != m_Mario->GetSprite().getPosition().x)
			{
				m_MarioPipe->MovePipes(dt);
				m_Mario->Visible(dt);
			}
			else
			{
				m_Mario->Update(dt);
				m_Mario->Animate(dt);

				float DeltaY = std::cos(m_RunningTimeMario + dt) - std::cos(m_RunningTimeMario);
				m_RunningTimeMario += dt;
				m_MarioPipe->MoveUpDown(dt, DeltaY);
				m_Mario->MoveUpDown(dt, DeltaY);
			}
			if (m_MarioInvisibleClock.getElapsedTime().asSeconds() > TIME_MARIO_VISIBLE)
			{
				m_MarioInvisibleClock.restart();
				m_bVisibleMario = false;
			}
		}
		#pragma region CheckCollision
		for (int i = 0; i < Land.size(); i++)
		{		
			if (m_Collision->CheckCollision(Bird, Land[i]))
			{
				m_GameStates = eGAMEOVER;
				m_Clock.restart();
				m_HitSound.play();
			}
		}
		for (int i = 0; i < Pipe.size(); i++)
		{
			if (m_Collision->CheckCollision(Bird, Pipe[i], 0.625f, 1.0f))
			{
				m_GameStates = eGAMEOVER;
				m_Clock.restart();
				m_HitSound.play();
			}
		}
		for (int i = 0; i < PipeScoring.size(); i++)
		{
			if (m_Collision->CheckCollision(Bird, PipeScoring[i]))
			{
				m_Score++;
				m_PointSound.play();
				PipeScoring.erase(PipeScoring.begin() + i);
			}
		}
		for (int k = 0; k < bullet.size(); k++)
		{
			sf::Sprite sprite = bullet[k]->GetSprite();
			if (m_Collision->CheckCollision(Bird, sprite, 0.7f, 0.8f))
			{
				m_GameStates = eGAMEOVER;
				m_Clock.restart();
				m_HitSound.play();
				bullet.erase(bullet.begin() + k);
			}
		}
		#pragma endregion

		m_Land->MoveLand(dt);
		m_Bird->Animate(dt);
		m_Pipe->MovePipes(dt);
		m_Pipe->MovePipesScoring(dt);
		m_Bird->Update(dt);
		m_HUD->UpdateScore(m_Score);

	}
	#pragma endregion

	#pragma region GAMEOVER.
	if (m_GameStates == eGAMEOVER)
	{
		m_Flash->Show(dt);
		m_Bird->Die(dt);

		/*Check if bird dies before mario shows up*/
		if (m_bVisibleMario && m_LastPositionOfMario == m_Mario->GetSprite().getPosition().x)
		{
			m_Mario->Update(dt);
			m_Mario->Animate(dt);
		}
		if (m_Clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER)
		{
			m_Data->machine.AddState(StateRef(new GameOverState(m_Data, m_Score)));
		}
	}
	#pragma endregion 

}

void GameState::Draw(float dt)
{
	
	m_Data->window.clear();
	m_Data->window.draw(m_Background);
	if (m_GameStates == eREADY)
		m_Data->window.draw(m_Ready);
	m_Pipe->DrawPipes();
	m_MarioPipe->DrawPipes();
	m_Land->DrawLand();
	m_Bird->DrawBird();
	m_Mario->DrawMario();
	m_Flash->Draw();
	m_HUD->Draw();

	m_Data->window.display();
}