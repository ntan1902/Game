#ifndef _MENU_H
#define _MENU_H
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include"Data.h"
class Menu
{
private:
	sf::RenderWindow       *m_window;
	int                     m_indexSelected;
	sf::Font                m_font;
	sf::Text                m_menu[NUM_MENU];
	sf::Sprite              m_sprite;
	sf::Texture             m_texture;

	sf::Texture             m_texture_sound;
	sf::Sprite              m_sprite_sound;
	sf::Texture             m_texture_sound_mute;
	sf::Sprite              m_sprite_sound_mute;
	int                     m_count_mute_sound = 0;

public:
	Menu(sf::RenderWindow *window,float width, float height);
	~Menu();
	void draw();
	void MoveUp();
	void MoveDown();
	int getIndexSelected(){ return this->m_indexSelected; }
	void about();
	int &getCountMute(){ return this->m_count_mute_sound; }
};

#endif