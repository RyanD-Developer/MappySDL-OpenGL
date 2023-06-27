#ifndef __BOSS_H
#define __BOSS_H
#include "Enemy.h"
#include "CaptureBeam.h"
#include "Random.h"

using namespace SDLFramework;

class Boss : public Enemy {
private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mCaptureDive;
	int mCurrentPath;
	bool mCapturing;

	CaptureBeam * mCaptureBeam;

	bool mWasHit;

private:
	void HandleCaptureBeam();

	// Inherited via Enemy
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;

	void RenderDiveState() override;

public:
	static void CreateDivePaths();

	// Inherited from Enemy
	void Dive(int type = 0) override;
	void Hit(PhysEntity * other) override;

	Boss(int path, int index, bool challenge);
	~Boss();
};
#endif