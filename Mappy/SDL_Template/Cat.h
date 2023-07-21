#ifndef __CAT_H
#define __CAT_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;
class Cat : public PhysEntity {

	Timer* mTimer;
	AudioManager* mAudio;

	bool mVisible;
	bool mWasHit;
	bool GoingDown;
	bool GoingUp;
	bool InPlace;
	bool PInPlace;
	bool mCanMove = true;
	bool TrampolineOnce = false;

	AnimatedGLTexture* mCat;
	AnimatedGLTexture* mHit;
	AnimatedGLTexture* mFalling;

	std::string Direction;
	float mMoveSpeed;
	float TTarget;
	float mTimer1 = 0.0f;
	Vector2 mMoveBounds;
	Vector2 mMovement;
private:
	void HandleMovement();

public :
	Cat();
	~Cat();

	void Visible(bool visible);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	void SetMoveBounds(Vector2(MB));
	void SetMovement(Vector2(MV));
	void CanMove(bool b);
	void SetGoingDown(bool b);
	void SetDirection(std::string b);
	void SetGoingUp(bool b);
	void SetInPlace(bool b);
	void SetPInPlace(bool P);
	void WasHit();
	void SetTrampolineOnce(bool b);
	void SetTrampolineTarget(float f);

	bool GetTrampolineOnce();
	bool GetGoingDown();
	bool GetGoingUp();
	std::string GetDirection();

	void Update() override;
	void Render() override;
};
#endif