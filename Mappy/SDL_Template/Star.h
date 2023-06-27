#ifndef __STAR_H
#define __STAR_H
#include "Texture.h"
#include "Timer.h"
#include "Random.h"

using namespace SDLFramework;

class Star : public Texture {

private:
	static bool mScroll;

	Timer * mTimer;
	Random * mRand;

	bool mVisible;
	float mFlickerTimer;
	float mFlickerSpeed;

	float mScrollSpeed;

public:
	static void Scroll(bool b);

	Star(int layer);
	~Star();

	void Update() override;
	void Render() override;

private:
	void ScrollStar();
};
#endif

