#ifndef __DOORS_H
#define __DOORS_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Doors : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	GLTexture* mDoors[4];

	bool mVisible;
	bool IsOpen = false;
	bool Animate = false;

	int PositionX;
	int PositionY;
	float Sprite;

public:
	Doors();
	~Doors();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void Visible(bool visible);
	void SetPositionX(int x);
	void SetPositionY(int Y);
	void Update() override;
	void Render() override;
	bool CheckDoorOpen();
	void OpenDoor(bool b);
};
#endif