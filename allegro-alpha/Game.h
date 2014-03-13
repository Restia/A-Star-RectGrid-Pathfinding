#ifndef _GAME_H_
#define _GAME_H_
#include "GamePlay.h"
#include <math.h>

class Game {
private:
	GamePlay *_gc;
	// fps = 50
	bool _running;

private:
	void close_button_handler(void);

public:
	Game();
	~Game();

	void run();
};

#endif _GAME_H_