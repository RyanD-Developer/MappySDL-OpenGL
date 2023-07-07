#include "Trampoline.h"
#include "PhysicsManager.h"
Trampoline::Trampoline() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mTrampolineG = new AnimatedGLTexture("TGreen.png", 0, 0, 120, 64, 6, 0.25f, Animation::Layouts::Horizontal);
	mTrampolineG->Parent(this);
	mTrampolineG->Position(Vec2_Zero);
	mTrampolineY = new AnimatedGLTexture("TYellow.png", 0, 0, 120, 64, 6, 0.25f, Animation::Layouts::Horizontal);
	mTrampolineY->Parent(this);
	mTrampolineY->Position(Vec2_Zero);
	mTrampolineB = new AnimatedGLTexture("TBlue.png", 0, 0, 120, 64, 6, 0.25f, Animation::Layouts::Horizontal);
	mTrampolineB->Parent(this);
	mTrampolineB->Position(Vec2_Zero);
	mTrampolineR = new AnimatedGLTexture("TRedB.png", 0, 0, 120, 64, 6, 0.25f, Animation::Layouts::Horizontal);
	mTrampolineR->Parent(this);
	mTrampolineR->Position(Vec2_Zero);
	mTrampolineB->SetWrapMode(Animation::WrapModes::Once);
	mTrampolineG->SetWrapMode(Animation::WrapModes::Once);
	mTrampolineY->SetWrapMode(Animation::WrapModes::Once);
	mTrampolineR->SetWrapMode(Animation::WrapModes::Once);
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}
void Trampoline::Visible(bool visible) {
	mVisible = visible;
}
Trampoline::~Trampoline() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTrampolineG;
	mTrampolineG = nullptr;
	delete mTrampolineB;
	mTrampolineB = nullptr;
	delete mTrampolineY;
	mTrampolineY = nullptr;
	delete mTrampolineR;
	mTrampolineR = nullptr;
}
bool Trampoline::IgnoreCollisions()
{
	return !mVisible;
}

void Trampoline::Hit(PhysEntity* other) {
	//collision for player gonna happen later
}

void Trampoline::Update() {
	if (!HaveSetColor) {
		if (TSetColor == 0) {
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			HaveSetColor = true;
		}
		else if (TSetColor == 1) {
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			HaveSetColor = true;
		}
		else if (TSetColor == 2) {
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			HaveSetColor = true;
		}
		else if (TSetColor == 3) {
			HaveSetColor = true;
		}
	}
	if (BounceAnim) {
		mTrampolineY->Update();
		mTrampolineB->Update();
		mTrampolineG->Update();
		if (!mTrampolineG->IsAnimating() || !mTrampolineB->IsAnimating() || !mTrampolineY->IsAnimating()) {
			mTrampolineY->ResetAnimation();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineY->Update();
			mTrampolineB->ResetAnimation();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineB->Update();
			mTrampolineG->ResetAnimation();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			mTrampolineG->Update();
			BounceAnim = false;
		}
	}
}

void Trampoline::Render() {
	if (mVisible) {
		if (TSetColor == 0) {
			mTrampolineG->Render();
		}
		else if (TSetColor == 1) {
			mTrampolineB->Render();
		}
		else if (TSetColor == 2) {
			mTrampolineY->Render();
		}
		else if (TSetColor == 3) {
			mTrampolineR->Render();
		}
	}

	PhysEntity::Render();
}

void Trampoline::SetColor(int Color) {
	TSetColor = Color;
	HaveSetColor = false;
}

void Trampoline::AddColor() {
	TSetColor += 1;
	BounceAnim = true;
}
void Trampoline::SetBounced(bool b) {
	Bounced = b;
}
bool Trampoline::GetBounced() {
	return Bounced;
}