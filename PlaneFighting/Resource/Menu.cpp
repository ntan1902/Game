#include "Menu.h"


Menu::Menu(sf::RenderWindow *window, float width, float height)
{
	this->m_window = window;
	
	this->m_texture.loadFromFile(file_name_background_menu);
	this->m_texture.setSmooth(true);
	this->m_sprite.setTexture(this->m_texture);

	this->m_texture_sound.loadFromFile(file_name_sound);
	this->m_texture_sound.setSmooth(true);
	this->m_sprite_sound.setTexture(this->m_texture_sound);
	this->m_sprite_sound.setPosition(SCREEN_WIDTH - 40, 0);

	this->m_texture_sound_mute.loadFromFile(file_name_sound_mute);
	this->m_texture_sound_mute.setSmooth(true);
	this->m_sprite_sound_mute.setTexture(this->m_texture_sound_mute);
	this->m_sprite_sound_mute.setPosition(SCREEN_WIDTH - 40, 0);
	
	this->m_font.loadFromFile(file_name_font);
		  
	this->m_menu[0].setFont(m_font);
	this->m_menu[0].setFillColor(sf::Color::Red);
	this->m_menu[0].setString("Play");
	this->m_menu[0].setCharacterSize(80);
	this->m_menu[0].setPosition(sf::Vector2f(width - 1000, height - 400));
		  
	this->m_menu[1].setFont(m_font);
	this->m_menu[1].setFillColor(sf::Color::White);
	this->m_menu[1].setString("Exit");
	this->m_menu[1].setCharacterSize(80);
	this->m_menu[1].setPosition(sf::Vector2f(width -1000, height - 300));
		  
	this->m_indexSelected = 0;
}

void Menu::draw()
{
	this->m_window->draw(this->m_sprite);
	for (int i = 0; i < NUM_MENU; i++)
	{
		this->m_window->draw(this->m_menu[i]);
	}
	if (this->m_count_mute_sound % 2 != 0)
		this->m_window->draw(this->m_sprite_sound_mute);
	else
		this->m_window->draw(this->m_sprite_sound);
}
void Menu::MoveUp()
{
	if (this->m_indexSelected - 1 >= 0)
	{		  
		this->m_menu[m_indexSelected].setFillColor(sf::Color::White);
		this->m_indexSelected--;
		this->m_menu[m_indexSelected].setFillColor(sf::Color::Red);
	}
}
void Menu::MoveDown()
{
	if (this->m_indexSelected + 1 < NUM_MENU)
	{		  
		this->m_menu[m_indexSelected].setFillColor(sf::Color::White);
		this->m_indexSelected++;
		this->m_menu[m_indexSelected].setFillColor(sf::Color::Red);
	}
}

Menu::~Menu()		   
{
	
}
