#ifndef __WASP_H
#define __WASP_H
#include "Enemy.h"

class Wasp : public Enemy {
private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mDiver;

private:
	// Inherited via Enemy
	void FlyInComplete() override;

	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;

	void RenderDiveState() override;

public:
	static void CreateDivePaths();

	Wasp(int path, int index, bool challenge, bool diver);
	~Wasp();

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;
};
#endif