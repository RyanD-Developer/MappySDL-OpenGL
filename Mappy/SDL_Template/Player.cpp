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
	else if (mInput->KeyDown(SDL_SCANCODE_UP)) {
		Translate(-Vec2_Up * 300.0f * mTimer->DeltaTime(), World);
		mRat->Scale(Vector2(1.0f, 1.0f));
		Direction = "Up";
	}
	else if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {
		Translate(Vec2_Up * 300.0f * mTimer->DeltaTime(), World);
		mRat->Scale(Vector2(1.0f, 1.0f));
		Direction = "Down";
	}
	else {
		Direction = "None";
	}
}
std::string Player::MoveReturn() {
	return Direction;
}

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mAnimating = false;
	mWasHit = false;

	mScore = 0;
	mLives = 2;

	mRat = new AnimatedGLTexture("Walking.png", 0, 0, 68, 64, 3, 0.25f, Animation::Layouts::Horizontal);
	mRat->Parent(this);
	mRat->Position(Vec2_Zero);

	mDeathAnimation = new AnimatedGLTexture("PlayerExplosion.png", 0, 0, 128, 128, 4, 1.0f, Animation::Layouts::Horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Position(Vec2_Zero);
	mDeathAnimation->SetWrapMode(Animation::WrapModes::Once);

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}

Player::~Player() {
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	delete mRat;
	mRat = nullptr;

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
void Player::SetMoveBounds(Vector2(FartniteBalls)) {
	mMoveBounds = FartniteBalls;
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
	return !mVisible || mAnimating;
}

void Player::Hit(PhysEntity* other) {
	mLives -= 1;
	mAnimating = true;
	mDeathAnimation->ResetAnimation();
	mAudio->PlaySFX("SFX/PlayerExplosion.wav");
	mWasHit = true;
}

bool Player::WasHit() {
	return mWasHit;
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
			HandleMovement();
		}
	}
}

void Player::Render() {
	if (mVisible) {
		if (mAnimating) {
			mDeathAnimation->Render();
		}
		else {
			mRat->Render();
		}
	}

	PhysEntity::Render();
}