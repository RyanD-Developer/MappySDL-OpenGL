#ifndef __BACKGROUNDSTARS_H
#define __BACKGROUNDSTARS_H
#include "StarLayer.h"

class BackgroundStars {
private:
	static BackgroundStars * sInstance;
	static const int LAYER_COUNT = 3;
	StarLayer * mLayers[LAYER_COUNT];

public:
	static BackgroundStars * Instance();
	static void Release();

	void Scroll(bool b);

	void Update();
	void Render();

private:
	BackgroundStars();
	~BackgroundStars();
};

#endif