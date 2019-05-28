#include "Player.h"


Player::Player(sf::RenderWindow *window)
{
	this->m_window = window;
	
	this->m_texture.loadFromFile(file_name_plane_fly);
	this->m_texture.setSmooth(true);
	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setOrigin(this->m_texture.getSize().x / 2, this->m_texture.getSize().y / 2);
	this->m_sprite.setPosition(PLAYER_WIDTH / 2, PLAYER_HEIGHT / 2 + 30);

	this->m_texture_fire.loadFromFile(file_name_plane_fly_bullet);
	this->m_texture_fire.setSmooth(true);
	this->m_sprite_fire.setTexture(this->m_texture_fire);
	this->m_sprite_fire.setOrigin(this->m_texture_fire.getSize().x / 2, this->m_texture_fire.getSize().y / 2);


	this->m_texture_bullet_sphere.loadFromFile(file_name_sphere);
	this->m_texture_bullet_sphere.setSmooth(true);
	

	this->m_texture_bullet_laser.loadFromFile(file_name_laser);
	this->m_texture_bullet_laser.setSmooth(true);
	

	this->m_texture_heart.loadFromFile(file_name_heart);
	this->m_texture_heart.setSmooth(true);
	this->m_sprite_heart.setTexture(this->m_texture_heart);

	this->sound_buffer_fire.loadFromFile(file_name_sound_buffer_fire);
	this->sound_fire.setBuffer(this->sound_buffer_fire);
	this->sound_fire.setVolume(20);


}

void Player::update()
{
	//Move Player
	sf::Vector2f player_position = this->m_sprite.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		player_position.y -= PLAYER_HEIGHT/8;			
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		player_position.y += PLAYER_HEIGHT/8;			
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		player_position.x -= PLAYER_WIDTH/8;			
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		player_position.x += PLAYER_WIDTH/8;
	
	if (player_position.x <= PLAYER_WIDTH / 2)
		player_position.x = PLAYER_WIDTH / 2;
	if (player_position.x >= (SCREEN_WIDTH - PLAYER_WIDTH/ 2))
		player_position.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
	if (player_position.y <= 30 + PLAYER_HEIGHT / 2)
		player_position.y = 30 + PLAYER_HEIGHT / 2;
	if (player_position.y >= (SCREEN_HEIGHT / 2 + 215  - PLAYER_HEIGHT / 2))
		player_position.y = SCREEN_HEIGHT / 2 + 215 - PLAYER_HEIGHT / 2;

	//Update Bullet of Player
	if (this->m_bullet.size() > 0)
	{
		for (int i = 0; i < this->m_bullet.size(); i++)
			this->m_bullet[i]->update();
		if (this->m_bullet[0]->getPosition().x > SCREEN_WIDTH)
		{
			this->m_bullet.erase(this->m_bullet.begin());
		}
	}

	this->m_time = this->m_clock.getElapsedTime();
	//Fire Bullet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) && this->m_time.asSeconds() > 0.1)
	{
		this->fire = true;
		this->m_sprite_fire.setPosition(player_position.x, player_position.y);
		Bullet *bullet = new Bullet(this->m_window, this->m_texture_bullet_laser, player_position.x + PLAYER_WIDTH / 2 - 1.5, player_position.y + PLAYER_HEIGHT / 2 - 11);
		this->m_bullet.push_back(bullet);
		if (this->mute == false)
			this->sound_fire.play();

		this->m_clock.restart();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) && this->m_time.asSeconds() > 0.1)
	{
		this->fire = true;
		this->m_sprite_fire.setPosition(player_position.x, player_position.y);
		Bullet *bullet_2 = new Bullet(this->m_window, this->m_texture_bullet_sphere, player_position.x + PLAYER_WIDTH / 2 - 1.5, player_position.y + PLAYER_HEIGHT / 2 - 11);
		this->m_bullet.push_back(bullet_2);
		if (this->mute == false)
			this->sound_fire.play();

		this->m_clock.restart();
	}

	this->m_sprite.setPosition(player_position.x, player_position.y);

}
void Player::draw()
{
	if (this->fire == true)
	{
		this->m_window->draw(this->m_sprite_fire);
		this->fire = false;
	}
	else
		this->m_window->draw(this->m_sprite);
	for (int i = 0; i < this->m_bullet.size(); i++)
		this->m_bullet[i]->draw();
	for (int h = 0; h < this->m_heart; h++)
	{
		this->m_sprite_heart.setPosition(5 + h * 20, 5);
		this->m_window->draw(this->m_sprite_heart);
	}
}

void Player::RemoveBullet(int index)
{
	int size_Bullet = this->m_bullet.size();
	if (size_Bullet > 0 && size_Bullet > index)
	{
		this->m_bullet.erase(this->m_bullet.begin() + index);
	}
}
Player::~Player()
{
	for (int i = 0; i < this->m_bullet.size(); i++)
		delete this->m_bullet[i];
	this->m_bullet.clear();
}