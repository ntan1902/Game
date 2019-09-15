#include "Game.h"
#include "ConstValue.h"
#include <windows.h>

int main()
{
	srand(time(NULL));
	FreeConsole();
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");
	
	return EXIT_SUCCESS;

}