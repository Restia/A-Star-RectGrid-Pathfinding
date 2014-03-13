#include "Game.h"

void Game::close_button_handler(void)
{
	_running = false;
}

Game::Game()
{
	_gc = new GamePlay();
	// Remember to check for failed initialization.
	_gc->setWindowTitle("Exercise 01 - 2 Heuristic Functions");
	_gc->clearScreen();
	_gc->setBackgroundColor(110, 119, 82);
	
	_gc->initKeyboard();
	_gc->refresh();
	_running = true;
}

void Game::run()
{
	long beforeTime, timeDiff, sleep;
	long fpsTime;
	int fps = 0;

	beforeTime = _gc->getCurrentTimeMillis();
	fpsTime = _gc->getCurrentTimeMillis();

	while (_running)
	{
		_running = !(_gc->isDown(ALLEGRO_KEY_ESCAPE) || _gc->needToClose());
		_gc->refresh();
		fps++;
		
		timeDiff = _gc->getCurrentTimeMillis() - beforeTime;
		sleep = 20 - timeDiff;
		if (_gc->getCurrentTimeMillis() - fpsTime >= 1000)
		{
			fpsTime = _gc->getCurrentTimeMillis();
			std::cout << "fps= " << fps << std::endl;
			fps = 0;
		}

		if (sleep < 0)
			sleep = 1;
		
		_gc->sleep(sleep);
		beforeTime = _gc->getCurrentTimeMillis();
	}
}