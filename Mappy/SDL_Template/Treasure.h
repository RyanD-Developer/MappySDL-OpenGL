#ifndef __TREASURE_H
#define __TREASURE_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Treasure : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	AnimatedGLTexture* mTreasure;
	bool TSetTexture = false;
	bool mVisible;
	int PositionX;
	int PositionY;
	int Sprite;
private:
	void HandleMovement();

public:
	Treasure();
	~Treasure();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void Visible(bool visible);
	bool WasHit();
	void SetPositionX(int x);
	void SetPositionY(int Y);
	void SetSprite(int s);
	void Update() override;
	void Render() override;
};
#endif