#ifndef _TIMEGAME_H_
#define _TIMEGAME_H_
#include<SFML/Graphics.hpp>
class TimeGame
{
public:
	sf::Time  m_time;
	sf::Clock m_clock;
	TimeGame();
	~TimeGame();
};

#endif
