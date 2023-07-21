#include "Cat.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

void Cat::HandleMovement() {
	
	if (GoingDown && mCanMove) {
		mFalling->Update();
		Translate(Vec2_Up * 150.0f * mTimer->DeltaTime(), World);
		if (Position().x > TTarget + 5) {
			Translate(-Vec2_Right * 150.0f * mTimer->DeltaTime(), World);
		}
		else if (Position().x < TTarget - 5) {
			Translate(Vec2_Right * 150.0f * mTimer->DeltaTime(), World);
		}
	}

	if (GoingUp && mCanMove) {
		mFalling->Update();
		Translate(-Vec2_Up * 150.0f * mTimer->DeltaTime(), World);
		if (Position().x > TTarget + 5) {
			Translate(-Vec2_Right * 150.0f * mTimer->DeltaTime(), World);
		}
		else if (Position().x < TTarget - 5) {
			Translate(Vec2_Right * 150.0f * mTimer->DeltaTime(), World);
		}
	}
	if (!GoingDown && !GoingUp && Direction == "None") {
		if (mMovement.x > Position().x) {
			Direction = "Right";
		}
		else if (mMovement.x < Position().x) {
			Direction = "Left";
		}
	}

	if (PInPlace && mCanMove && !InPlace) {
		mTimer1 = 0;
		if (mMovement.y - 30 >= Position().y - 10 && mMovement.y - 30 <= Position().y + 10 && mMovement.x > Position().x) {
			Direction = "Right";
		}
		else if (mMovement.y - 30 >= Position().y - 10 && mMovement.y - 30 <= Position().y + 10 && mMovement.x < Position().x) {
			Direction = "Left";
		}
	}

	if (InPlace) {
		TrampolineOnce = false;
	}

	else if (!PInPlace && mCanMove) {
		if (GoingUp || GoingDown) {
			mTimer1 += 0.026;
		}
		if (mTimer1 > 15) {
			if (Position().x + 200.0f < mMoveBounds.x) {
				GoingUp = false;
				GoingDown = false;
				Direction = "Right";
			}
			else {
				GoingUp = false;
				GoingDown = false;
				Direction = "Left";
			}
			mTimer1 = 0;
		}
	}

	for (int i = 0; i < 10; i++) {
		if (!InPlace && !GoingUp && mCanMove) {
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
	if (Direction == "Right" && mCanMove) {
		mCat->Scale(Vector2(-1.0f, 1.0f));
		SetDirection("Right");
		TTarget = 0.0f;
		GoingUp = false;
		GoingDown = false;
		mTimer1 = 0;
		mCat->Update();
		Translate(Vec2_Right * 150.0f * mTimer->DeltaTime(), World);
	}
	else if (Direction == "Left" && mCanMove) {
		mCat->Scale(Vector2(1.0f, 1.0f));
		SetDirection("Left");
		TTarget = 0.0f;
		GoingUp = false;
		GoingDown = false;
		mTimer1 = 0;
		mCat->Update();
		Translate(-Vec2_Right * 150.0f * mTimer->DeltaTime(), World);
	}
}

void Cat::SetInPlace(bool b) {
	InPlace = b;
}

void Cat::SetDirection(std::string b) {
	Direction = b;
}

void Cat::SetPInPlace(bool P) {
	PInPlace = P;
}

void Cat::SetMoveBounds(Vector2(MB)) {
	mMoveBounds = MB;
}

void Cat::CanMove(bool b) {
	mCanMove= b;
}

void Cat::SetMovement(Vector2(MV)) {
	mMovement = MV;
}

Cat::Cat() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mCanMove = true;
	Direction = "Left";

	mCat = new AnimatedGLTexture("CWalking.png", 0, 0, 68, 64, 3, 0.25f, Animation::Layouts::Horizontal);
	mCat->Parent(this);
	mCat->Position(Vec2_Zero);

	mHit = new AnimatedGLTexture("CHit.png", 0, 0, 68, 64, 3, 0.25f, Animation::Layouts::Horizontal);
	mHit->Parent(this);
	mHit->Position(Vec2_Zero);

	mFalling = new AnimatedGLTexture("CFalling.png", 0, 0, 68, 64, 2, 0.25f, Animation::Layouts::Horizontal);
	mFalling->Parent(this);
	mFalling->Position(Vec2_Zero);

	AddCollider(new BoxCollider(Vector2(50.0f, 46.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Visible(true);
}

Cat::~Cat() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mCat;
	mCat = nullptr;

	delete mHit;
	mHit = nullptr;

	delete mFalling;
	mFalling = nullptr;

}

bool Cat::IgnoreCollisions()
{
	return !mVisible || GoingDown || GoingUp;
}

void Cat::Hit(PhysEntity* other) {
	mVisible = false;
}

void Cat::WasHit() {
	mWasHit = true;
}

void Cat::Update() {
   if (Active()) {
		HandleMovement();
   }
}

void Cat::Render() {
	if (mVisible) {
		if (GoingDown) {
			mFalling->Render();
		}
		else if (GoingUp) {
			mFalling->Render();
		}
		else if (TTarget != 0.0f) {
			mFalling->Render();
		}
		else if (mWasHit) {
			mHit->Render();
		}
		else {
			mCat->Render();
		}
	}
        PhysEntity::Render();
}

void Cat::Visible(bool visible) {
	mVisible = visible;
}

void Cat::SetGoingDown(bool b) {
	SetDirection("None");
	GoingDown = b;
}
void Cat::SetGoingUp(bool b) {
	SetDirection("None");
	GoingUp = b;
}
bool Cat::GetGoingDown() {
	return GoingDown;
}
bool Cat::GetGoingUp() {
	return GoingUp;
}

std::string Cat::GetDirection() {
	return Direction;
}

void Cat::SetTrampolineOnce(bool b) {
	TrampolineOnce = b;
}

bool Cat::GetTrampolineOnce() {
	return TrampolineOnce;
}

void Cat::SetTrampolineTarget(float f) {
	TTarget = f;
}