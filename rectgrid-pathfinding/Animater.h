#ifndef _ANIMATER_H_
#define _ANIMATER_H_

#include <allegro5\allegro.h>
#include <vector>

class Animater {
private:
	std::vector<ALLEGRO_BITMAP*> *_frames;
	int				_animationSize;
	int				_currFrame;
	int				_frameDur;
	bool			_stop;

private:
	long			_lastTick;
	void update();

public:
	Animater();
	~Animater();
	void addFrame(ALLEGRO_BITMAP* frame);
	void setFrameDur(int dur);
	ALLEGRO_BITMAP*	getCurrFrame();
	bool isStop();
};

#endif _ANIMATER_H_