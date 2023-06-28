#include "Treasure.h"
#include "PhysicsManager.h"
Treasure::Treasure() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	mTreasure = new AnimatedGLTexture("MappySprites.png", 4, 596, 64, 64, 3, 0.25f, Animation::Layouts::Horizontal);
	mTreasure->Parent(this);
	mTreasure->Position(Vec2_Zero);

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}
void Treasure::Visible(bool visible) {
	mVisible = visible;
}
Treasure::~Treasure() {
	mTimer = nullptr;
	mAudio = nullptr;

	delete mTreasure;
	mTreasure = nullptr;
}
bool Treasure::IgnoreCollisions()
{
	return !mVisible;
}

void Treasure::Hit(PhysEntity* other) {
}

void Treasure::Update() {
	if (!TSetTexture) {
		if (Sprite == 0) {
			delete mTreasure;
			mTreasure = nullptr;
			mTreasure = new AnimatedGLTexture("MappySprites.png", 4, 596, 64, 64, 3, 0.25f, Animation::Layouts::Horizontal);
			mTreasure->Parent(this);
			mTreasure->Position(Vec2_Zero);
		}
		else if (Sprite == 1) {
			delete mTreasure;
			mTreasure = nullptr;
			mTreasure = new AnimatedGLTexture("MappySprites.png", 76, 596, 64, 64, 3, 0.25f, Animation::Layouts::Horizontal);
			mTreasure->Parent(this);
			mTreasure->Position(Vec2_Zero);
		}
		else if (Sprite == 2) {
			delete mTreasure;
			mTreasure = nullptr;
			mTreasure = new AnimatedGLTexture("MappySprites.png", 148, 596, 64, 64, 3, 0.25f, Animation::Layouts::Horizontal);
			mTreasure->Parent(this);
			mTreasure->Position(Vec2_Zero);
		}
		else if (Sprite == 3) {
			delete mTreasure;
			mTreasure = nullptr;
			mTreasure = new AnimatedGLTexture("MappySprites.png", 220, 596, 64, 64, 3, 0.25f, Animation::Layouts::Horizontal);
			mTreasure->Parent(this);
			mTreasure->Position(Vec2_Zero);
		}
		else if (Sprite == 4) {
			delete mTreasure;
			mTreasure = nullptr;
			mTreasure = new AnimatedGLTexture("MappySprites.png", 292, 596, 64, 64, 3, 0.25f, Animation::Layouts::Horizontal);
			mTreasure->Parent(this);
			mTreasure->Position(Vec2_Zero);
		}
		TSetTexture = true;
	}
	if (Position().x == 5000.0f || Position().y == 5000.0f) {
		if (PositionX == 0) {
			Position(648.0f, Position().y);
		}
		else if (PositionX == 1) {
			Position(425.0f, Position().y);
		}
		else if (PositionX == 2) {
			Position(74.0f, Position().y);
		}
		else if (PositionX == 3) {
			Position(-150.0f, Position().y);
		}
		else if (PositionX == 4) {
			Position(-500.0f, Position().y);
		}
		else if (PositionX == 5) {
			Position(-707.0f, Position().y);
		}
		if (PositionY == 0) {
			Position(Position().x, 577.0f);
		}
		else if (PositionY == 1) {
			Position(Position().x, 704.0f);
		}
		else if (PositionY == 2) {
			Position(Position().x, 831.0f);
		}
		else if (PositionY == 3) {
			Position(Position().x, 959.0f);
		}
		else if (PositionX == 4) {
			Position(Position().x, 1086.0f);
		}
		else if (PositionX == 5) {
			Position(Position().x, 450.0f);
		}
	}
}

void Treasure::Render() {
	if (mVisible) {
		mTreasure->Render();
	}

	PhysEntity::Render();
}