#include "Timer.h"

namespace SDLFramework {

	Timer * Timer::sInstance = nullptr;

	Timer * Timer::Instance() {
		if (sInstance == nullptr) {
			sInstance = new Timer();
		}
		return sInstance;
	}

	void Timer::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	Timer::Timer() {
		Reset();
		mTimeScale = 1.0f;
	}


	Timer::~Timer() {
	}

	void Timer::Reset() {
		mStartTicks = SDL_GetTicks();
		mElapsedTicks = 0;
		mDeltaTime = 0.0f;
	}

	float Timer::DeltaTime() const {
		return mDeltaTime;
	}

	void Timer::TimeScale(float ts) {
		mTimeScale = ts;
	}

	float Timer::TimeScale() const {
		return mTimeScale;
	}

	void Timer::Update() {
		mElapsedTicks = SDL_GetTicks() - mStartTicks;
		mDeltaTime = mElapsedTicks * 0.001f;
	}
}