#ifndef __TRAMPOLINE_H
#define __TRAMPOLINE_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Trampoline : public PhysEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;

	AnimatedGLTexture* mTrampolineG;
	AnimatedGLTexture* mTrampolineB;
	AnimatedGLTexture* mTrampolineY;
	AnimatedGLTexture* mTrampolineR;
	int TSetColor = 0;
	bool mVisible;
	bool HaveSetColor;
	bool BounceAnim = false;
	bool Bounced = false;

public:
	Trampoline();
	~Trampoline();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void Visible(bool visible);
	
	bool GetBounced();
	void SetBounced(bool b);
	void SetColor(int Color);
	void AddColor();
	void Update() override;
	void Render() override;
};
#endif