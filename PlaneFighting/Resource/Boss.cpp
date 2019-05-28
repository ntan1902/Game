#include "Boss.h"


Boss::Boss(sf::RenderWindow *window)
{
	this->m_window = window;
	
	this->m_texture_bullet.loadFromFile(file_name_boss_bullet);
	this->m_texture_bullet.setSmooth(true);

	this->m_texture_bullet_45.loadFromFile(file_name_boss_bullet_45);
	this->m_texture_bullet_45.setSmooth(true);

	this->m_texture_bullet_minus_45.loadFromFile(file_name_boss_bullet_minus_45);
	this->m_texture_bullet_minus_45.setSmooth(true);

	this->m_texture_animation.loadFromFile(file_name_boss_animation);
	this->m_texture_animation.setSmooth(true);

	this->m_texture_heart.loadFromFile(file_name_heart_boss);
	this->m_texture_heart.setSmooth(true);
	this->m_sprite_heart.setTexture(this->m_texture_heart);


	this->m_animation_boss = new Animation(this->m_window, this->m_texture_animation, 0, 0, ANI_BOSS_WIDTH, ANI_BOSS_HEIGHT, 0.5, 32, sf::Vector2f(SCREEN_WIDTH + 300, SCREEN_HEIGHT/2));

}
void Boss::update()
{
	if (this->m_animation_boss->getFrame() == 17.5)
	{
		Bullet *bullet = new Bullet(this->m_window, this->m_texture_bullet, this->m_animation_boss->getPosition().x - ANI_BOSS_WIDTH / 2, this->m_animation_boss->getPosition().y + ANI_BOSS_HEIGHT / 2 - 20);
		bullet->setTypeBulletBoss(1);
		this->m_bullet.push_back(bullet);
		
		Bullet *bullet_45 = new Bullet(this->m_window, this->m_texture_bullet_45, this->m_animation_boss->getPosition().x - ANI_BOSS_WIDTH / 2, this->m_animation_boss->getPosition().y + ANI_BOSS_HEIGHT / 2 - 20);
		bullet_45->setTypeBulletBoss(2);
		this->m_bullet.push_back(bullet_45);
		
		Bullet *bullet_minus_45 = new Bullet(this->m_window, this->m_texture_bullet_minus_45, this->m_animation_boss->getPosition().x - ANI_BOSS_WIDTH / 2, this->m_animation_boss->getPosition().y + ANI_BOSS_HEIGHT / 2 - 20);
		bullet_minus_45->setTypeBulletBoss(3);
		this->m_bullet.push_back(bullet_minus_45);
		
	}
	if (this->m_bullet.size() > 0)
	{
		for (int i = 0; i < this->m_bullet.size(); i++)
		{
			switch (this->m_bullet[i]->getTypeBulletBoss())
			{
			case 1:
				this->m_bullet[i]->MoveFromBoss();
				break;
			case 2:
				this->m_bullet[i]->MoveFromBoss45();
				break;
			case 3:
				this->m_bullet[i]->MoveFromBossMinus45();
				break;
			}

		}
		if (this->m_bullet[0]->getPosition().x < 0 || this->m_bullet[0]->getPosition().y < 30 || this->m_bullet[0]->getPosition().y > SCREEN_HEIGHT)
		{
			this->m_bullet.erase(this->m_bullet.begin());
		}
	}


	this->m_animation_boss->update();

	this->m_time = this->m_clock.getElapsedTime();
	if (this->m_animation_boss->checkEnd() && this->m_time.asSeconds() > 3)
	{
		float x = rand() % (SCREEN_WIDTH - (SCREEN_WIDTH/2) + 1) + (SCREEN_WIDTH/2);
		float y = rand() % ((SCREEN_HEIGHT - 120) - (ANI_BOSS_HEIGHT / 3) + 1) + ANI_BOSS_HEIGHT / 3 ;
		this->m_animation_boss->move(x, y);
		this->m_animation_boss->setFrame(0);
		this->m_clock.restart();
	}	
}

void Boss::draw()
{
	this->m_animation_boss->draw();
	for (int i = 0; i < this->m_bullet.size(); i++)
		this->m_bullet[i]->draw();
	for (int h = 0; h < this->m_heart; h++)
	{
		this->m_sprite_heart.setPosition(this->m_animation_boss->getPosition().x + h*10 - ANI_BOSS_WIDTH/2 + 40, this->m_animation_boss->getPosition().y - ANI_BOSS_HEIGHT/2 + 60);
		this->m_window->draw(this->m_sprite_heart);
	}

}
void Boss::RemoveBullet(int index)
{
	int size_Bullet = this->m_bullet.size();
	if (size_Bullet > 0 && size_Bullet > index)
	{
		this->m_bullet.erase(this->m_bullet.begin() + index);
	}
}

Boss::~Boss()
{
	for (int i = 0; i < this->m_bullet.size(); i++)
		delete this->m_bullet[i];
	this->m_bullet.clear();
	delete this->m_animation_boss;
}
