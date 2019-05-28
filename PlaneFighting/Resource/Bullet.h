#ifndef _AMMO_H_
#define _AMMO_H_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>

class Bullet
{
private:
	sf::RenderWindow       *m_window;

	sf::Sprite              m_sprite;

	bool                    m_check_collision = false;

	int                     type_bullet_boss;
public:
	Bullet(sf::RenderWindow *window, sf::Texture &texture, float coord_x, float coord_y);
	void update();
	void draw();

	void setCheckCollision(bool check){ this->m_check_collision = check; }
	void MoveRightToLeft(float coord_x, float coord_y);
	void MoveBottomRightToTopLeft(float coord_x, float coord_y);
	
	void MoveFromBoss();
	void MoveFromBoss45();
	void MoveFromBossMinus45();

	sf::Vector2f getPosition() { return this->m_sprite.getPosition(); }
	sf::Sprite   getSprite(){ return this->m_sprite; }

	void setTypeBulletBoss(int type){ this->type_bullet_boss = type;}
	int getTypeBulletBoss(){ return this->type_bullet_boss; }
};

#endif