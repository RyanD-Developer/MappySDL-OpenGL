#ifndef __PLAYER_H
#define __PLAYER_H
#include "AnimatedGLTexture.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "PhysEntity.h"

using namespace SDLFramework;

class Player : public PhysEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;
	bool GoingDown;
	bool GoingUp;
	bool InPlace;
	bool mDead = false;

	int mScore;
	int mLives;

	AnimatedGLTexture* mRat;
	AnimatedGLTexture* mFalling;
	AnimatedGLTexture* mDeathAnimation;

	std::string Direction;
	float mMoveSpeed;
	float mTimer1 = 0.0f;
	Vector2 mMoveBounds;

private:
	void HandleMovement();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();
	void SetInPlace(bool b);

	int Score();
	int Lives();

	void AddScore(int change);

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;
	void Hit(PhysEntity* other) override;
	std::string MoveReturn();
	void SetMoveBounds(Vector2(MB));
	void SetGoingDown(bool b);
	void SetGoingUp(bool b);
	void Reset();
    void WasHit();
	void SetDead(bool D);
	
	bool GetDead();
	bool GetAnimating();
	bool GetWasHit();
	bool GetGoingDown();
	bool GetGoingUp();
	bool GetInPlace();

	void Update() override;
	void Render() override;
};
#endif