#ifndef __RANDOM_H
#define __RANDOM_H
#include <random>
#include <chrono>

namespace SDLFramework {

	class Random {
	private:
		static Random * sInstance;

		std::mt19937 mGenerator;

	public:
		static Random * Instance();
		static void Release();

		unsigned RandomInt(); // [0,unsigned max]
		float RandomFloat(); // [0.0,1.0)
		int RandomRange(int lo, int hi); // [lo,hi]
		float RandomRange(float lo, float hi); // [lo,hi)

	private:
		Random();
		~Random();
	};
}
#endif

