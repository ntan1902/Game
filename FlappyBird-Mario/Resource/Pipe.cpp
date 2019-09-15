#include "Pipe.h"
#include "ConstValue.h"

Pipe::Pipe(GameDataRef data) : m_Data(data)
{
	m_LandY = m_Data->assets.GetTexture("Land").getSize().y;
	m_YOffset = 0;
}


Pipe::~Pipe()
{
}
void Pipe::RandomY()
{
	m_YOffset = rand() % (m_LandY);
}
void Pipe::SpawnBottomPipe()
{
	
	sf::Sprite sprite(m_Data->assets.GetTexture("Pipe Up"));
	sprite.setPosition(m_Data->window.getSize().x, 
					   m_Data->window.getSize().y - sprite.getGlobalBounds().height  - m_YOffset);
	m_Pipe.push_back(sprite);

}
void Pipe::SpawnTopPipe()
{
	sf::Sprite sprite(m_Data->assets.GetTexture("Pipe Down"));
	sprite.setPosition(m_Data->window.getSize().x,
					   - m_YOffset);
	m_Pipe.push_back(sprite);

	//Spawn Scoring Pipe
	sf::Sprite spriteScoring(m_Data->assets.GetTexture("Pipe Scoring"));
	spriteScoring.setPosition(m_Data->window.getSize().x + sprite.getGlobalBounds().width / 2,
							  0);
	m_PipeScoring.push_back(spriteScoring);

}
void Pipe::MoveUpDown(float dt, float DeltaY)
{
	for (int i = 0; i < m_Pipe.size(); i++)
	{
		sf::Vector2f newPosition = m_Pipe[i].getPosition();
		newPosition.y += DeltaY * 50.0f;
		m_Pipe[i].setPosition(newPosition);
	}
}
void Pipe::SpawnMarioPipe(float x)
{
	sf::Sprite sprite(m_Data->assets.GetTexture("Pipe Down"));
	sprite.setPosition(x,
				       -m_YOffset);
	m_Pipe.push_back(sprite);

	sf::Sprite sprite2(m_Data->assets.GetTexture("Pipe Up"));
	sprite2.setPosition(x,
						m_Data->window.getSize().y - sprite2.getGlobalBounds().height - m_YOffset);
	m_Pipe.push_back(sprite2);
}
void Pipe::MovePipes(float dt)
{
	

	for (int i = 0; i < m_Pipe.size(); i++)
	{
		float movement = PIPE_MOVEMENT_SPEED * dt;
		m_Pipe[i].move(-movement, 0);
	
	}
	for (int i = 0; i < m_Pipe.size(); i++)
	{
		if (m_Pipe[i].getPosition().x < 0 - m_Pipe[i].getGlobalBounds().width)
		{
			m_Pipe.erase(m_Pipe.begin() + i);

		}
	}
}
void Pipe::MovePipesScoring(float dt)
{
	for (int i = 0; i < m_PipeScoring.size(); i++)
	{
		float movement = PIPE_MOVEMENT_SPEED * dt;
		m_PipeScoring[i].move(-movement, 0);

	}
}
void Pipe::Invisible(float dt)
{
	for (int i = 0; i < m_Pipe.size(); i++)
	{


		float movement = PIPE_MOVEMENT_SPEED * dt;
		m_Pipe[i].move(movement, 0);
	}
}

void Pipe::DrawPipes()
{
	for (int i = 0; i < m_Pipe.size(); i++)
	{
		m_Data->window.draw(m_Pipe[i]);
	}
}
