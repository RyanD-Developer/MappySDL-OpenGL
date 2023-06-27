#ifndef __STARLAYER_H
#define __STARLAYER_H
#include "Star.h"

class StarLayer {
private:
	static const int STAR_COUNT = 30;
	Star * mStars[STAR_COUNT];

public:
	StarLayer(int layer);
	~StarLayer();

	void Update();
	void Render();
};

#endif