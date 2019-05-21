#include "Game.h"


Game::Game(sf::RenderWindow *window) : m_score(0)
{
	this->m_window = window;
	
	this->m_player = new Player(window);
	
	this->m_texture_threat_2.loadFromFile("Images/Car_2.png");
	this->m_texture_threat_2.setSmooth(true);

	this->m_texture_threat_3.loadFromFile("Images/Car_3.png");
	this->m_texture_threat_3.setSmooth(true);

	this->m_texture_threat_4.loadFromFile("Images/Car_4.png");
	this->m_texture_threat_4.setSmooth(true);

	this->m_texture_explosion.loadFromFile("Images/Explosion.png");
	this->m_texture_explosion.setSmooth(true);

	this->m_font.loadFromFile("Font/MarkerFelt.ttf");
	this->m_text.setFont(this->m_font);
	this->m_text.setString("Score: ");
	this->m_text.setCharacterSize(15);
	this->m_text.setPosition(200, 0);

}
bool Game::update()
{
	this->m_player->update();
	if (this->m_explosion.size() > 0)
	{
		for (std::list<Animation>::iterator it = this->m_explosion.begin(); it != this->m_explosion.end(); it++)
		{
			it->update();
		}
		if (this->m_explosion.begin()->checkEnd())
			this->m_explosion.pop_front();
	}
	if (this->m_threat.size() > 0)
	{
		for (std::list<Threat>::iterator it = this->m_threat.begin(); it != this->m_threat.end(); it++)
		{
			it->update();
		}
		
		if (this->m_threat.begin()->getPosition().y > 520)
		{
			this->m_threat.pop_front();
			this->m_player->getCountHeart()--;
		}


		for (std::list<Threat>::iterator it = this->m_threat.begin(); it != this->m_threat.end(); it++)
		{
			int x = abs(this->m_player->getPosition().x - it->getPosition().x);
			int y = abs(this->m_player->getPosition().y - it->getPosition().y);
			int check_x = (this->m_player->getPosition().x < it->getPosition().x) ? this->m_player->getPosition().x : it->getPosition().x;
			int check_y = (this->m_player->getPosition().y < it->getPosition().y) ? this->m_player->getPosition().y : it->getPosition().y;
			if (x <= 45 && y <= 95)
			{
				this->m_threat.erase(it);
				this->m_explosion.push_back(Animation(this->m_window, this->m_texture_explosion, 0, 0, 50, 50, 0.1, 20,sf::Vector2f(check_x + x/2,check_y + y/2)));
				this->m_score += 10;
				break;
			}
		}
	}

	this->m_text.setString("Score: " + std::to_string(this->m_score));


	float time;
	if (this->m_score < 100)
		time = 0.5;
	else if (this->m_score < 200)
		time = 0.4;
	else if (this->m_score < 300)
		time = 0.3;
	else 
		time = 0.2;

	this->m_time = this->m_clock.getElapsedTime();
	if (this->m_time.asSeconds() > time)
	{
		switch (std::rand() % 3)
		{
		case 0:
			this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_2));
			break;
		case 1:
			this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_3));
			break;
		case 2:
			this->m_threat.push_back(Threat(this->m_window, this->m_texture_threat_4));
			break;
		}
		this->m_clock.restart();
	}
	if (this->m_player->getCountHeart() >= 0)
		return true;
	else
	{
		std::string Information = "Your Score: " + std::to_string(this->m_score);
		if (MessageBox(NULL, Information.c_str(), "GAME OVER", MB_OK) == IDOK)
		return false;
	}
}
void Game::draw()
{
	
	if (this->m_threat.size() > 0)
	{
		for (std::list<Threat>::iterator it = this->m_threat.begin(); it != this->m_threat.end(); it++)
			it->draw();
	
	}
	if (this->m_explosion.size() > 0)
	{
		for (std::list<Animation>::iterator it = this->m_explosion.begin(); it != this->m_explosion.end(); it++)
		{
			it->draw();
		}
	}


	this->m_player->draw();
	this->m_window->draw(this->m_text);
}


Game::~Game()
{
	delete this->m_player;
	for (int i = 0; i<this->m_threat.size(); i++)
		this->m_threat.pop_back();
}