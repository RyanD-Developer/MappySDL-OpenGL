#ifndef __BULLET_H
#define __BULLET_H
#include "PhysEntity.h"
#include "Timer.h"

using namespace SDLFramework;

class Bullet : public PhysEntity {
private:
	static const int OFFSCREEN_BUFFER = 10;

	Timer * mTimer;

	Texture * mTexture;

	float mSpeed;

private:
	//Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:
	Bullet(bool friendly);
	~Bullet();

	void Fire(Vector2 pos);
	void Reload();

	// Inherited from PhysEntity
	void Hit(PhysEntity * other) override;

	void Update() override;
	void Render() override;
};
#endif