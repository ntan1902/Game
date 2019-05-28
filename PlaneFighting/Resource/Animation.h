#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<vector>
class Animation
{
private:
	sf::RenderWindow           *m_window;
	sf::Texture                 m_texture;
	sf::Sprite                  m_sprite;
	float                       m_speed;
	float                       m_Frame;
	std::vector<sf::IntRect>    m_Frames;
public:
	Animation(sf::RenderWindow *window, sf::Texture &texture, int column, int line, int width, int height, float speed,int count, sf::Vector2f position);
	~Animation();
	void update();
	void draw();
	void move(float x, float y);
	void setFrame(float x){ this->m_Frame = x; }
	float getFrame(){ return this->m_Frame; }
	bool checkEnd();
	sf::Vector2f getPosition(){ return this->m_sprite.getPosition(); }
};

#endif