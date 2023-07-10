#include "Player.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		mRat->Update();
		mRat->Scale(Vector2(-1.0f, 1.0f));
		Direction = "Right";
	}
	else if (mInput->KeyDown(SDL_SCANCODE_LEFT)) {
		mRat->Update();
		mRat->Scale(Vector2(1.0f, 1.0f));
		Direction = "Left";
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_T)) {
		mWasHit = true;
		WasHit();
	}
	else {
		Direction = "None";
	}

	if (GoingDown) {
		mFalling->Update();
		Translate(Vec2_Up * 150.0f * mTimer->DeltaTime(), World);
	}
    if (GoingUp) {
		mFalling->Update();
		Translate(-Vec2_Up * 150.0f * mTimer->DeltaTime(), World);
	}
	for (int i = 0; i < 10; i++) {
		if (!InPlace && !GoingUp) {
			if (Position().y < 449.2f && !GoingDown) {
				Translate(Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
			}
			else if (Position().y > 449.3f && Position().y < 576.7f && !GoingDown) {
				Translate(Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
			}
			else if (Position().y > 576.8f && Position().y < 704.2f && !GoingDown) {
				Translate(Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
			}
			else if (Position().y > 704.3f && Position().y < 831.8f && !GoingDown) {
				Translate(Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
			}
			else if (Position().y > 831.9f && Position().y < 959.2f && !GoingDown) {
				Translate(Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
			}
			else if (Position().y > 959.3f && Position().y < 1086.8f && !GoingDown) {
				if (Position().y < 1086.8) {
					Translate(Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
				}
				else if (Position().y > 1086.9) {
					Translate(-Vec2_Up * 10.0f * mTimer->DeltaTime(), World);
				}
			}
			if (Position().y >= 449.2 && Position().y <= 449.4 && !GoingDown) {
				InPlace = true;
			}
			else if (Position().y >= 576.7 && Position().y <= 576.9 && !GoingDown) {
				InPlace = true;
			}
			else if (Position().y >= 704.2 && Position().y <= 704.4 && !GoingDown) {
				InPlace = true;
			}
			else if (Position().y >= 831.8 && Position().y <= 832 && !GoingDown) {
				InPlace = true;
			}
			else if (Position().y >= 959.2 && Position().y <= 959.4 && !GoingDown) {
				InPlace = true;
			}
			else if (Position().y >= 1086.8 && Position().y <= 1086.9 && !GoingDown) {
				InPlace = true;
			}
		}
	}
	
}
std::string Player::MoveReturn() {
	return Direction;
}

void Player::SetInPlace(bool b) {
	InPlace = b;
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 3;

	mRat = new AnimatedGLTexture("Walking.png", 0, 0, 68, 64, 3, 0.25f, Animation::Layouts::Horizontal);
	mRat->Parent(this);
	mRat->Position(Vec2_Zero);

	mFalling = new AnimatedGLTexture("Falling.png", 0, 0, 68, 64, 2, 0.25f, Animation::Layouts::Horizontal);
	mFalling->Parent(this);
	mFalling->Position(Vec2_Zero);

	mDeathAnimation = new AnimatedGLTexture("DeathAnim.png", 0, 0, 72, 64, 11, 0.50f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);
	//AddCollider(new BoxCollider(Vector2(56.0f, 52.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	
	mAudio = nullptr;

	delete mRat;
	mRat = nullptr;

	delete mFalling;
	mFalling = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	/*for (auto b : mBullets) {
		delete b;
	}*/
}

void Player::Visible(bool visible) {
	mVisible = visible;
}

bool Player::IsAnimating() {
	return mAnimating;
}
void Player::SetMoveBounds(Vector2(MB)) {
	mMoveBounds = MB;
}
int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}

void Player::AddScore(int change) {
	mScore += change;
}

bool Player::IgnoreCollisions()
{
	return !mVisible || mDead;
}

void Player::Hit(PhysEntity* other) {
	mWasHit = true;
	mDead = true;
	WasHit();
}

void Player::WasHit() {
	mWasHit = true;
	mDead = true;
	mLives -= 1;
}

void Player::SetDead(bool D) {
	mDead = D;
}

bool Player::GetDead() {
	return mDead;
}

bool Player::GetWasHit() {
	return mWasHit;
}

bool Player::GetAnimating() {
	return mAnimating;
}

void Player::Update() {
	if (mAnimating) {

		if (mWasHit) {
			mWasHit = false;
		}

		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else {
		if (Active()) {
			if (mWasHit && mTimer1 < 3.1) {
				mTimer1 += 0.026;
			}
			else if (mWasHit) {
				mTimer1 = 0.0f;
				mAnimating = true;
				mDeathAnimation->ResetAnimation();
			}
			else {
				HandleMovement();
			}
		}
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			if (GoingDown) {
				mFalling->Render();
			}
			else if (GoingUp) {
				mFalling->Render();
			} else if (mWasHit && mTimer1 < 5.1) {
				mFalling->Render();
			}
			else {
				mRat->Render();
			}
		}
	}

	PhysEntity::Render();
}

void Player::SetGoingDown(bool b) {
	GoingDown = b;
}
void Player::SetGoingUp(bool b) {
	GoingUp = b;
}
bool Player::GetGoingDown() {
	return GoingDown;
}
bool Player::GetGoingUp() {
	return GoingUp;
}

void Player::Reset() {
	Direction = "None";
	mVisible = true;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 3;
}