#include "Doors.h"
#include "PhysicsManager.h"
Doors::Doors() {
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = false;
	Sprite = 0;
	delete mDoors[0];
	mDoors[0] = new GLTexture("Doors.png", 12, 0, 19, 96);
	mDoors[0]->Parent(this);
	mDoors[0]->Position(Vec2_Zero);
	delete mDoors[1];
	mDoors[1] = new GLTexture("Doors.png", 56, 0, 36, 96);
	mDoors[1]->Parent(this);
	mDoors[1]->Position(8.0f, 0.0f);
	delete mDoors[2];
	mDoors[2] = new GLTexture("Doors.png", 128, 0, 56, 96);
	mDoors[2]->Parent(this);
	mDoors[2]->Position(18.0f, 0.0f);
	delete mDoors[3];
	mDoors[3] = new GLTexture("Doors.png", 236, 0, 64, 96);
	mDoors[3]->Parent(this);
	mDoors[3]->Position(22.0f, 0.0f);

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	Visible(true);
}
void Doors::Visible(bool visible) {
	mVisible = visible;
}
Doors::~Doors() {
	mTimer = nullptr;
	mAudio = nullptr;

	for (int i = 0; i < 4; i++) {
		delete mDoors[i];
		mDoors[i] = nullptr;
	}
}
bool Doors::IgnoreCollisions()
{
	return !mVisible;
}

void Doors::Hit(PhysEntity* other) {
}

void Doors::Update() {
	if (Position().x == 5000.0f || Position().y == 5000.0f) {
		if (PositionX == 0) {
			Position(534.0f, Position().y); //590 is middle of this row
		}
		else if (PositionX == 1) {
			Position(-42.0f, Position().y); //-19 is middle of this row
		}
		else if (PositionX == 2) {
			Position(-618.0f, Position().y); //-597 is middle of this row
		}
		// -32 from every y below this
		if (PositionY == 0) {
			Position(Position().x, 559.0f);
		}
		else if (PositionY == 1) {
			Position(Position().x, 687.0f);
		}
		else if (PositionY == 2) {
			Position(Position().x, 815.0f);
		}
		else if (PositionY == 3) {
			Position(Position().x, 943.0f);
		}
		else if (PositionY == 4) {
			Position(Position().x, 1071.0f);
		}
	}

	if (Animate) {
		if (Sprite < 3) {
			Sprite = Sprite + 0.25f;
		}
	}
}

void Doors::Render() {
	if (mVisible) {
		mDoors[(int)Sprite]->Render();
	}

	PhysEntity::Render();
}

void Doors::SetPositionX(int x) {
	PositionX = x;
}

void Doors::SetPositionY(int Y) {
	PositionY = Y;
}

void Doors::OpenDoor(bool b) {
	Animate = b;
	IsOpen = b;
}

bool Doors::CheckDoorOpen() {
	return IsOpen;
}