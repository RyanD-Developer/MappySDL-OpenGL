#ifndef __TIMER_H
#define __TIMER_H
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#include <SDL.h>
#elif defined(__APPLE__)
#include <SDL2/SDL.h>
#endif

namespace SDLFramework {

	class Timer
	{
	private:
		static Timer * sInstance;

		unsigned int mStartTicks;
		unsigned int mElapsedTicks;
		float mDeltaTime;
		float mTimeScale;

	public:
		static Timer * Instance();
		static void Release();

		void Reset();
		float DeltaTime() const;

		void TimeScale(float ts);
		float TimeScale() const;

		void Update();

	private:
		Timer();
		~Timer();
	};
}
#endif