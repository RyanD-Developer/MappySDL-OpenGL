#ifndef __FORMATION_H
#define __FORMATION_H
#include "GameEntity.h"
#include "Timer.h"

using namespace SDLFramework;

class Formation : public GameEntity {
private:
	Timer * mTimer;

	// side-to-side movement while still spawning
	float mOffsetAmount;
	float mOffsetTimer;
	float mOffsetDelay;
	int mOffsetCounter;
	int mOffsetDirection;

	// breathing animation when formation locked
	float mSpreadTimer;
	float mSpreadDelay;
	int mSpreadCounter;
	int mSpreadDirection;

	Vector2 mGridSize;

	bool mLocked;

public:
	Formation();
	~Formation();

	Vector2 GridSize();

	int GetTick();

	void Lock();

	bool Locked();

	void Update() override;
};
#endif