#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
class Pipe
{
private:
	GameDataRef m_Data;
	std::vector<sf::Sprite> m_Pipe;
	std::vector<sf::Sprite> m_PipeScoring;
	int m_LandY;
	float m_YOffset;
public:
	Pipe(GameDataRef data);
	~Pipe();
public:
	void RandomY();
	void SpawnBottomPipe();
	void SpawnTopPipe();
	void MoveUpDown(float dt, float DeltaY);
	void SpawnMarioPipe(float x);
	void MovePipes(float dt);
	void MovePipesScoring(float dt);

	void Invisible(float dt);
	void DrawPipes();

	std::vector<sf::Sprite> GetSprites() const { return m_Pipe; }
	std::vector<sf::Sprite> &GetSpritesScoring() { return m_PipeScoring; }


};

