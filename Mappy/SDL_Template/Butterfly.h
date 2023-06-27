#ifndef __BUTTERFLY_H
#define __BUTTERFLY_H
#include "Enemy.h"

class Butterfly : public Enemy {
private:
	static std::vector<std::vector<Vector2>> sDivePaths;

	bool mEscort;

private:
	// Inherited via Enemy
	Vector2 LocalFormationPosition() override;

	void HandleDiveState() override;

	void RenderDiveState() override;

public:
	static void CreateDivePaths();

	void Dive(int type = 0) override;

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;

	Butterfly(int path, int index, bool challenge);
	~Butterfly();
};
#endif