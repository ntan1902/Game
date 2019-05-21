#include "Player.h"


Player::Player(sf::RenderWindow *window) : m_count_heart(5)
{
	this->m_window = window;
	this->m_window->setMouseCursorVisible(true);
	
	this->m_texture_car.loadFromFile("Images/Car_1.png");
	this->m_texture_car.setSmooth(true);
	
	this->m_sprite_car.setTexture(this->m_texture_car);
	this->m_sprite_car.setOrigin(this->m_texture_car.getSize().x / 2, this->m_texture_car.getSize().y / 2); //Điều chỉnh con trỏ chuột ở trung tâm chiếc xe


	this->m_texture_heart.loadFromFile("Images/Heart.png");
	this->m_texture_heart.setSmooth(true);
	this->m_sprite_heart.setTexture(this->m_texture_heart);

}

void Player::update()
{
	sf::Vector2f car_position = this->m_sprite_car.getPosition();

	
	car_position.y = 450;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		car_position.x -= 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		car_position.x += 1;
	if (car_position.x <= 25)
		car_position.x = 25;
	if (car_position.x >= 275)
		car_position.x = 275;
	this->m_sprite_car.setPosition(car_position.x, car_position.y);
}
void Player::draw()
{

	this->m_window->draw(this->m_sprite_car);
	for (int i = 0; i < this->m_count_heart; i++)
	{
		this->m_sprite_heart.setPosition(5 + i*12, 5);
		this->m_window->draw(this->m_sprite_heart);
	}
}
int& Player::getCountHeart()
{
	return this->m_count_heart;
}

sf::Vector2f Player::getPosition()
{
	return this->m_sprite_car.getPosition();
}