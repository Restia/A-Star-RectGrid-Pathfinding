#ifndef _ANIMATIONTRACKER_H_
#define _ANIMATIONTRACKER_H_

#include <allegro5\allegro.h>
#include "Animater.h"

class AnimationTracker {
private:
	Animater**	_animaterArray;
	int			_numAnimations;
public:
	AnimationTracker();
	~AnimationTracker();

	void newAnimation(Animater* animater);
	void update();
	void drawAll();
};

#endif _ANIMATIONTRACKER_H_