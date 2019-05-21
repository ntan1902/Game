#include"Game.h"
#include<Windows.h>
int main()
{
	sf::RenderWindow window(sf::VideoMode(300, 500), "Race Car");
	
	std::srand(time(NULL));
	sf::Music music;
	
	sf::Texture t;
	t.loadFromFile("Images/Road.png");
	sf::Sprite s;
	s.setTexture(t);

	sf::Image Icon;
	Icon.loadFromFile("Images/Icon.png");
	window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());

	music.openFromFile("Music/music.wav");
	music.setVolume(50);
	music.play();
	Game game(&window);
	bool checkChooseWindow = true;
	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::LostFocus)
				checkChooseWindow = false;
			if (e.type == sf::Event::GainedFocus)
				checkChooseWindow = true;
		}
		if (checkChooseWindow)
		{
			window.clear();
			window.draw(s);
			game.draw();
			if (!game.update())
				window.close();

			window.display();
		}
	}

}


