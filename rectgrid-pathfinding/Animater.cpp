#include "Animater.h"

Animater::Animater()
{
	_frames = new std::vector<ALLEGRO_BITMAP*>();
	_animationSize = 0;
	_currFrame = 0;
	_frameDur = 0;
	_lastTick = -1;
	_stop = false;
}

Animater::~Animater()
{
	delete _frames;
}

void Animater::update()
{
	if (_stop)
		return;

	if (_lastTick < 0)
		_lastTick = (long)(al_get_time() * 1000);
	else {
		if ((long)(al_get_time()*1000) - _lastTick >= _frameDur)
		{
			if (_currFrame == _animationSize - 1)
			{
				_currFrame = 0;
				_stop = true;
			}
			else _currFrame++;
			_lastTick = (long)(al_get_time() * 1000);
		}
	}
}

void Animater::addFrame(ALLEGRO_BITMAP* frame)
{
	_frames->push_back(frame);
	_animationSize++;
}

void Animater::setFrameDur(int dur)
{
	_frameDur = dur;
}

ALLEGRO_BITMAP* Animater::getCurrFrame()
{
	update();
	return _frames->at(_currFrame);
}

bool Animater::isStop()
{
	return _stop;
}