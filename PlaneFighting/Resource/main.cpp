#include"Game.h"
#include"Menu.h"
#include<iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	FreeConsole();
	window.setFramerateLimit(60);
	Menu menu(&window, SCREEN_WIDTH, SCREEN_HEIGHT);

	bool chooseWindow = true;
	int gameOn = 0;
	int gameStart = 0;
	float x_offset = 0;
	bool is_screen_run = true;
	int game_final = 1;

	 
	sf::Music music_menu;                            ///Music of menu
	music_menu.openFromFile(file_name_music_menu);
	music_menu.setVolume(20);
	music_menu.setLoop(true);
	music_menu.play();

	sf::Music music;                                //Music of game
	music.openFromFile(file_name_music_background);
	music.setLoop(true);
	music.setVolume(20);

	sf::Music music_final;                          //Music when fighting with boss
	music_final.openFromFile(file_name_music_final);
	music.setLoop(true);
	music_final.setVolume(20);

	int count_mute = 0;                           //The time of mute
	int music_type = 1;                            //1: game, 2:fighting with boss
	sf::Time time_delay;
	sf::Clock clock_delay;

	sf::Time time_final;
	sf::Clock clock_final;
	
	sf::Image Icon;
	Icon.loadFromFile("Images/plane_fly_bullet.png");
	window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());


	Game game(&window);
	srand(time(NULL));
	while (window.isOpen())
	{
		sf::Event e;
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::LostFocus:
				chooseWindow = false;
				break;
			case sf::Event::GainedFocus:
				chooseWindow = true;
				break;
			}
		}
		if (gameStart == 0 && chooseWindow)
		{
			if (mouse_position.x > 200 && mouse_position.x < 330 && mouse_position.y > 245 && mouse_position.y < 330)
			{
				menu.MoveUp();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					switch (menu.getIndexSelected())
					{
					case 0:
						gameStart = 1;     //Game in it
						music_menu.pause();
						if (count_mute % 2 == 0)
							music.play();
						break;
					case 1:
						gameStart = -1;    //Game off
						break;
					}
				}
			}
			else if (mouse_position.x > 200 && mouse_position.x < 330 && mouse_position.y > 345 && mouse_position.y < 410)
			{
				menu.MoveDown();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					switch (menu.getIndexSelected())
					{
					case 0:
						gameStart = 1;    //Game in it
						music_menu.pause();
						if(count_mute % 2 == 0)
							music.play();
						break;
					case 1:
						gameStart = -1;  //Game off
						break;
					}
				}
			}
			time_delay = clock_delay.getElapsedTime();
			if (mouse_position.x >= (1160) && mouse_position.x <= (1190) && mouse_position.y >= 4 && mouse_position.y <= 26 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && time_delay.asSeconds() > 0.1)
			{
				game.getCountMute()++;
				menu.getCountMute()++;
				count_mute++;
				if (count_mute % 2 != 0)
				{
					music_menu.pause();
				}
				else
				{
					music_menu.play();
				}
				clock_delay.restart();
			}
		}

		window.clear();
		if (gameStart == 0)
			menu.draw();
		else if (gameStart == -1)
			window.close();
		else
		{
			if (chooseWindow)
			{
				window.clear(sf::Color::Yellow);
				time_delay = clock_delay.getElapsedTime();
				if (mouse_position.x >= (1160) && mouse_position.x <= (1190) && mouse_position.y >= 4 && mouse_position.y <= 26 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && time_delay.asSeconds() > 0.1)
				{
					game.getCountMute()++;
					count_mute++;
					if (count_mute % 2 != 0)
					{
						if (music_type == 1)     //music_type = 1 is music background, 2 is music final
							music.pause();
						else
							music_final.pause();
					}
					else
					{
						if (music_type == 1)
							music.play();
						else
							music_final.play();
					}
					clock_delay.restart();
				}
				if (is_screen_run)
				{
					x_offset -= 3;
					if (x_offset <= -(4800 - SCREEN_WIDTH))
						is_screen_run = false;
					else
					{
						game.handleCollision();
						gameOn = game.update(x_offset);
					}
				}
				else
				{
					music_type = 2;
					if (game_final == 1 && game.getThreatOffScreen() >= 5)     //game_final is used for turning off music game, turning on music final 
					{
						if (count_mute % 2 == 0)
							music_final.play();
						music.pause();
						game_final++;
					}

					game.setFinal(true);
					game.handleCollision();
					gameOn = game.update_final();
				}
				game.draw();
				if (gameOn == 2)
				{
					std::string Information = "YOUR MARK: " + std::to_string(game.getMark());
					if (MessageBox(NULL, Information.c_str(), "YOU LOSE", MB_OK) == IDOK)
						window.close();
				}
				else if (gameOn == 1)
				{
					std::string Information = "YOUR MARK: " + std::to_string(game.getMark());
					if (MessageBox(NULL, Information.c_str(), "YOU WIN", MB_OK) == IDOK)
						window.close();
				}
			}
		}
		window.display();
	}

	return EXIT_SUCCESS;
}