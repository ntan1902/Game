#include "Game.h"

Game::Game(sf::RenderWindow *window)
{
	this->m_window = window;
	this->m_player = new Player(window);
	for (int th_1 = 0; th_1 < NUM_THREAT; th_1++)
	{
		Threat *threat = new Threat(this->m_window);
		this->m_threat.push_back(threat);
	}
	this->m_texture_threat_tank_1.loadFromFile(file_name_tank_threat);
	this->m_texture_threat_tank_2.loadFromFile(file_name_tank_threat_2);
	
	this->m_texture_bullet_sphere.loadFromFile(file_name_sphere_threat);
	this->m_texture_bullet_sphere.setSmooth(true);
	
	this->m_texture_bullet_laser.loadFromFile(file_name_laser);
	this->m_texture_bullet_laser.setSmooth(true);

	for (int th_tank = 0; th_tank < NUM_THREAT_TANK; th_tank++)
	{
		ThreatTank *threat_tank;
		if (th_tank % 2 != 0)
		{
			threat_tank = new ThreatTank(this->m_window,this->m_texture_threat_tank_1, this->m_texture_bullet_laser);

		}
		else
		{
			threat_tank = new ThreatTank(this->m_window, this->m_texture_threat_tank_2, this->m_texture_bullet_sphere);

		}
		this->m_threat_tank.push_back(threat_tank);
	}
	//Boss
	this->m_boss = new Boss(this->m_window);


	this->m_texture_background.loadFromFile(file_name_bg4800);
	this->m_texture_background.setSmooth(true);
	this->m_sprite_background.setTexture(this->m_texture_background);

	this->m_texture_background_2.loadFromFile(file_name_bg1200);
	this->m_texture_background_2.setSmooth(true);
	this->m_sprite_background_2.setTexture(this->m_texture_background_2);
	
	this->m_texture_animation_1.loadFromFile(file_name_explosion);
	this->m_texture_animation_1.setSmooth(true);

	this->m_texture_animation_2.loadFromFile(file_name_exp);
	this->m_texture_animation_2.setSmooth(true);

	this->m_sound_buffer_explosion.loadFromFile(file_name_sound_buffer_explosion);
	this->m_sound_explosion.setBuffer(this->m_sound_buffer_explosion);
	this->m_sound_explosion.setVolume(20);
		  
	this->m_texture_sound.loadFromFile(file_name_sound);
	this->m_texture_sound.setSmooth(true);
	this->m_sprite_sound.setTexture(this->m_texture_sound);
	this->m_sprite_sound.setPosition(SCREEN_WIDTH - 40, 0);
		  
	this->m_texture_sound_mute.loadFromFile(file_name_sound_mute);
	this->m_texture_sound_mute.setSmooth(true);
	this->m_sprite_sound_mute.setTexture(this->m_texture_sound_mute);
	this->m_sprite_sound_mute.setPosition(SCREEN_WIDTH - 40, 0);

	this->m_font.loadFromFile(file_name_font);
	this->m_text.setFont(this->m_font);
	this->m_text.setString("Mark: ");
	this->m_text.setCharacterSize(25);
	this->m_text.setFillColor(sf::Color::Black);
	this->m_text.setPosition(SCREEN_WIDTH/2, 0);

}
int Game::update(int x_offset)
{
	//Move background
	this->m_sprite_background.setPosition(x_offset, 30);

	//Update Player
	this->m_player->update();

	//Update Threat
	if (this->m_threat.size() > 0)
	{
		for (int tt = 0; tt < this->m_threat.size(); tt++)
		{

			this->m_threat[tt]->update();
		}
	}
	if (this->m_threat_tank.size() > 0)
	{

		for (int th = 0; th < this->m_threat_tank.size(); th++)
		{
			if (th % 2 != 0)
			{
				this->m_threat_tank[th]->update(1);
			}
			else
				this->m_threat_tank[th]->update(2);
		}
	}

	if (this->m_list_animation.size() > 0)
	{
		for (int ani = 0; ani < this->m_list_animation.size(); ani++)
		{
			this->m_list_animation[ani]->update();
		}
		if (this->m_list_animation[0]->checkEnd())
			this->m_list_animation.erase(this->m_list_animation.begin());
	}

	//Handle sound
	if (this->m_count_mute_sound % 2 != 0)
		this->m_player->setMute(true);
	else
		this->m_player->setMute(false);
	if (this->m_player->getHeart() > 0)
		return 0;
	else
	{
		return 2;
	}
}

int Game::update_final()
{
	this->m_sprite_background_2.setPosition(0, 30);
	this->m_player->update();
	if (this->m_threatOffScreen >= (NUM_THREAT + NUM_THREAT_TANK))
		this->m_boss->update();

	//Update Threat off screen
	if (this->m_threat.size() > 0)
	{
		for (int tt = 0; tt < this->m_threat.size(); tt++)
		{
			if (!this->m_threat[tt]->getCheckCollision() && this->m_threat[tt]->getPosition().x > 0)
				this->m_threat[tt]->update();
			else
			{
				this->m_threat[tt]->setPosition(-50, this->m_threat[tt]->getPosition().y);    //Off screen
				this->m_threat[tt]->getBullet()->MoveRightToLeft(-50, this->m_threat[tt]->getPosition().y);  //Off screen
				m_threatOffScreen++;
			}
		}
	}
	if (this->m_threat_tank.size() > 0)
	{

		for (int th = 0; th < this->m_threat_tank.size(); th++)
		{
			if (!this->m_threat_tank[th]->getCheckCollision() && this->m_threat_tank[th]->getPosition().x > 0)
			{
				if (th % 2 != 0)
				{
					this->m_threat_tank[th]->update(1);
				}
				else
					this->m_threat_tank[th]->update(2);
			}
			else
			{
				this->m_threat_tank[th]->setPosition(-50, this->m_threat_tank[th]->getPosition().y); //Off screen
				this->m_threat_tank[th]->getBullet()->MoveRightToLeft(-50, this->m_threat_tank[th]->getPosition().y); //Off screen
				m_threatOffScreen++;
			}
		}
	}

	if (this->m_list_animation.size() > 0)
	{
		for (int ani = 0; ani < this->m_list_animation.size(); ani++)
		{
			this->m_list_animation[ani]->update();
		}
		if (this->m_list_animation[0]->checkEnd())
			this->m_list_animation.erase(this->m_list_animation.begin());
	}

	//Handle sound
	if (this->m_count_mute_sound % 2 != 0)
		this->m_player->setMute(true);
	else
		this->m_player->setMute(false);

	if (this->m_player->getHeart() > 0 && this->m_boss->getHeart() > 0)
		return 0;
	else if (this->m_player->getHeart() <= 0 && this->m_boss->getHeart() > 0)
	{
		return 2;
	}
	else
		return 1;
}

void Game::handleCollision()
{
	//Check Collision between Bullet of player and threat
	if (this->m_player->getBullet().size() > 0)
	{
		//Threat plane
		for (int th_2 = 0; th_2 < NUM_THREAT; th_2++)
		{
			std::vector<Bullet*> Bullet_list = this->m_player->getBullet();

			int size_Bullet = Bullet_list.size();
			for (int j = 0; j < size_Bullet; j++)
			{
				Bullet *Bullet = Bullet_list.at(j);
				int x, y, x_explosion, y_explosion;
				if (checkCollision(this->m_threat[th_2]->getPosition(), Bullet->getPosition(), THREAT_WIDTH, THREAT_HEIGHT, SPHERE_WIDTH, SPHERE_HEIGHT, x, y, x_explosion, y_explosion))
				{
					Animation *animation = new Animation(this->m_window, this->m_texture_animation_1, 0, 0, ANI_WIDTH_1, ANI_HEIGHT_1, 0.5, 20, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
					this->m_list_animation.push_back(animation);
					this->m_threat[th_2]->setCheckCollision(true);
					this->m_player->RemoveBullet(j);
					this->m_mark++;
					if (this->m_count_mute_sound % 2 == 0)
						this->m_sound_explosion.play();
					break;
				}
			}
		}
		//Threat tank
		for (int th_t = 0; th_t < NUM_THREAT_TANK; th_t++)
		{
			std::vector<Bullet*> Bullet_list = this->m_player->getBullet();

			int size_Bullet = Bullet_list.size();
			for (int j = 0; j < size_Bullet; j++)
			{
				Bullet *Bullet = Bullet_list.at(j);
				int x, y, x_explosion, y_explosion;
				if (checkCollision(this->m_threat_tank[th_t]->getPosition(), Bullet->getPosition(), THREAT_WIDTH, THREAT_HEIGHT, SPHERE_WIDTH, SPHERE_HEIGHT, x, y, x_explosion, y_explosion))
				{
					Animation *animation = new Animation(this->m_window, this->m_texture_animation_1, 0, 0, ANI_WIDTH_1, ANI_HEIGHT_1, 0.5, 20, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
					this->m_list_animation.push_back(animation);
					this->m_threat_tank[th_t]->setCheckCollision(true);
					this->m_player->RemoveBullet(j);
					this->m_mark++;
					if (this->m_count_mute_sound % 2 == 0)
						this->m_sound_explosion.play();
					break;
				}
			}
		}
		//BOSS
		std::vector<Bullet*> Bullet_list_b = this->m_player->getBullet();
		int size_Bullet = Bullet_list_b.size();
		for (int j = 0; j < size_Bullet; j++)
		{
			Bullet *Bullet = Bullet_list_b.at(j);
			int x, y, x_explosion, y_explosion;
			if (checkCollision(this->m_boss->getAnimationBoss()->getPosition(), Bullet->getPosition(), ANI_BOSS_WIDTH, ANI_BOSS_HEIGHT, SPHERE_WIDTH, SPHERE_HEIGHT, x, y, x_explosion, y_explosion))
			{
				Animation *animation = new Animation(this->m_window, this->m_texture_animation_1, 0, 0, ANI_WIDTH_1, ANI_HEIGHT_1, 0.5, 20, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
				this->m_list_animation.push_back(animation);

				this->m_player->RemoveBullet(j);
				this->m_mark++;
				this->m_boss->getHeart()--;
				if (this->m_count_mute_sound % 2 == 0)
					this->m_sound_explosion.play();
				break;
			}
		}


	}


	//Check Collision between Bullet of threat and player
	for (int th_3 = 0; th_3 < NUM_THREAT; th_3++)
	{
		int x, y, x_explosion, y_explosion;
		if (checkCollision(this->m_player->getPosition(), this->m_threat[th_3]->getBullet()->getPosition(), PLAYER_WIDTH, PLAYER_HEIGHT, SPHERE_WIDTH, SPHERE_HEIGHT, x, y, x_explosion, y_explosion))
		{
			Animation *animation_2 = new Animation(this->m_window, this->m_texture_animation_2, 0, 0, ANI_WIDTH_2, ANI_HEIGHT_2, 0.3, 4, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
			this->m_list_animation.push_back(animation_2);
			this->m_threat[th_3]->getBullet()->setCheckCollision(true);
			this->m_player->getHeart()--;
			if (this->m_count_mute_sound % 2 == 0)
				this->m_sound_explosion.play();
		}
	}
	for (int th_t = 0; th_t < NUM_THREAT_TANK; th_t++)
	{
		int x, y, x_explosion, y_explosion;
		if (checkCollision(this->m_player->getPosition(), this->m_threat_tank[th_t]->getBullet()->getPosition(), PLAYER_WIDTH, PLAYER_HEIGHT, SPHERE_WIDTH, SPHERE_HEIGHT, x, y, x_explosion, y_explosion))
		{
			Animation *animation_2 = new Animation(this->m_window, this->m_texture_animation_2, 0, 0, ANI_WIDTH_2, ANI_HEIGHT_2, 0.3, 4, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
			this->m_list_animation.push_back(animation_2);
			this->m_threat_tank[th_t]->getBullet()->setCheckCollision(true);
			this->m_player->getHeart()--;
			if (this->m_count_mute_sound % 2 == 0)
				this->m_sound_explosion.play();
		}
	}
	//Check Collision between Bullet of boss and player
	if (this->m_boss->getBullet().size() > 0)
	{
		std::vector<Bullet*> Bullet_list_boss = this->m_boss->getBullet();

		int size_Bullet = Bullet_list_boss.size();
		for (int j = 0; j < size_Bullet; j++)
		{
			Bullet *Bullet = Bullet_list_boss.at(j);
			int x, y, x_explosion, y_explosion;
			if (checkCollision(this->m_player->getPosition(), Bullet->getPosition(), PLAYER_WIDTH, PLAYER_HEIGHT, BOSS_BULLET_WIDTH, BOSS_BULLET_HEIGHT, x, y, x_explosion, y_explosion))
			{
				Animation *animation = new Animation(this->m_window, this->m_texture_animation_1, 0, 0, ANI_WIDTH_1, ANI_HEIGHT_1, 0.5, 20, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
				this->m_list_animation.push_back(animation);
				this->m_boss->RemoveBullet(j);
				this->m_player->getHeart()--;
				if (this->m_count_mute_sound % 2 == 0)
					this->m_sound_explosion.play();
				break;
			}
		}

	}

	//Check Collision between player and threat
	for (int th_3 = 0; th_3 < NUM_THREAT; th_3++)
	{
		int x, y, x_explosion, y_explosion;
		if (checkCollision(this->m_player->getPosition(), this->m_threat[th_3]->getPosition(), PLAYER_WIDTH, PLAYER_HEIGHT, THREAT_WIDTH, THREAT_HEIGHT, x, y, x_explosion, y_explosion))
		{
			Animation *animation_2 = new Animation(this->m_window, this->m_texture_animation_2, 0, 0, ANI_WIDTH_2, ANI_HEIGHT_2, 0.3, 4, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
			this->m_list_animation.push_back(animation_2);
			this->m_threat[th_3]->setCheckCollision(true);
			this->m_player->getHeart()--;
			if (this->m_count_mute_sound % 2 == 0)
				this->m_sound_explosion.play();
		}			  
	}
	for (int th_t = 0; th_t < NUM_THREAT_TANK; th_t++)
	{
		int x, y, x_explosion, y_explosion;
		if (checkCollision(this->m_player->getPosition(), this->m_threat_tank[th_t]->getPosition(), PLAYER_WIDTH, PLAYER_HEIGHT, THREAT_TANK_WIDTH, THREAT_TANK_HEIGHT, x, y, x_explosion, y_explosion))
		{
			Animation *animation_3 = new Animation(this->m_window, this->m_texture_animation_2, 0, 0, ANI_WIDTH_2, ANI_HEIGHT_2, 0.3, 4, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
			this->m_list_animation.push_back(animation_3);
			this->m_threat_tank[th_t]->setCheckCollision(true);
			this->m_player->getHeart()--;
			if (this->m_count_mute_sound % 2 == 0)
				this->m_sound_explosion.play();
		}
	}
	//Check collision between boss and player

	int x, y, x_explosion, y_explosion;
	if (checkCollision(this->m_player->getPosition(), this->m_boss->getAnimationBoss()->getPosition(), PLAYER_WIDTH, PLAYER_HEIGHT, ANI_BOSS_WIDTH/2, ANI_BOSS_HEIGHT/2, x, y, x_explosion, y_explosion))
	{
		Animation *animation_4 = new Animation(this->m_window, this->m_texture_animation_2, 0, 0, ANI_WIDTH_2, ANI_HEIGHT_2, 0.3, 4, sf::Vector2f(x_explosion + x / 2, y_explosion + y / 2));
		this->m_list_animation.push_back(animation_4);
		this->m_player->getHeart()--;
		if (this->m_count_mute_sound % 2 == 0)
			this->m_sound_explosion.play();
	}



	this->m_text.setString("Mark: " + std::to_string(this->m_mark));
}
bool Game::checkCollision(sf::Vector2f object_1, sf::Vector2f object_2, const int object_1_width, const int object_1_height, const int object_2_width, const int object_2_height,int &x, int &y, int &x_explosion, int &y_explosion)
{

	x = abs(object_1.x - object_2.x);
	y = abs(object_1.y - object_2.y);
	x_explosion = (object_1.x < object_2.x) ? object_1.x : object_2.x;
	y_explosion = (object_1.y < object_2.y) ? object_1.y : object_2.y;
	if (x < ((object_1_width / 2) + (object_2_width / 2) - 5) && y < ((object_1_height / 2) + (object_2_height / 2)  -  5) )
	{
		return true;
	}
	else
		return false;
}

void Game::draw()
{
	//Draw background
	if (this->m_final == false || this->m_threatOffScreen < (NUM_THREAT + NUM_THREAT_TANK))
	{
		this->m_window->draw(this->m_sprite_background);
	}
	else
	{
		this->m_window->draw(this->m_sprite_background_2);
	}
	
	//Draw sound
	if (this->m_count_mute_sound % 2 != 0)
		this->m_window->draw(this->m_sprite_sound_mute);
	else
		this->m_window->draw(this->m_sprite_sound);
	
	//Draw threat
	if (this->m_threat.size() > 0 )
	{
		for (int th_4 = 0; th_4 < this->m_threat.size(); th_4++)
			this->m_threat[th_4]->draw();
	}

	if (this->m_threat_tank.size() > 0 )
	{
		for (int th_t = 0; th_t < this->m_threat_tank.size(); th_t++)
		{
			this->m_threat_tank[th_t]->draw();
		}
	}
	
	//Draw player
	this->m_player->draw();
	
	//Draw animation
	if (this->m_list_animation.size() > 0)
	{
		for (int ani = 0; ani < this->m_list_animation.size(); ani++)
			this->m_list_animation[ani]->draw();
	}
	
	//Draw boss
	if (this->m_threatOffScreen >= (NUM_THREAT + NUM_THREAT_TANK))
		this->m_boss->draw();
	this->m_window->draw(this->m_text);
}

Game::~Game()
{
	delete this->m_player;
	for (int i = 0; i < NUM_THREAT; i++)
		delete this->m_threat[i];
	for (int i = 0; i < NUM_THREAT_TANK; i++)
		delete this->m_threat_tank[i];
	this->m_threat.clear();
	this->m_threat_tank.clear();
	this->m_list_animation.clear();
	delete this->m_boss;
}

