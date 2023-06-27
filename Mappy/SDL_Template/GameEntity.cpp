#include "GameEntity.h"

namespace SDLFramework {

	GameEntity::GameEntity(float x, float y)
		: mPosition(x, y), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {
	}

	SDLFramework::GameEntity::GameEntity(const Vector2 & position)
		: mPosition(position), mRotation(0.0f), mScale(Vec2_One), mActive(true), mParent(nullptr) {
	}


	GameEntity::~GameEntity() {
		mParent = nullptr;
	}

	void GameEntity::Position(float x, float y) {
		mPosition = Vector2(x, y);
	}

	void GameEntity::Position(const Vector2 & pos) {
		mPosition = pos;
	}

	Vector2 GameEntity::Position(Space space) {
		if (space == Local || mParent == nullptr) {
			return mPosition;
		}
		
		GameEntity* parent = mParent;
		Vector2 finalPos = mPosition, parentScale = Vec2_Zero;

		do {
			parentScale = mParent->Scale(Local);
			finalPos = RotateVector(Vector2(finalPos.x * parentScale.x, finalPos.y * parentScale.y), parent->Rotation(Local));
			finalPos += parent->Position(Local);

			parent = parent->Parent();
		} while (parent != nullptr);

		return finalPos;
	}

	void GameEntity::Rotation(float rot) {
		mRotation = rot;

		while (mRotation > 360.0f) {
			mRotation -= 360.0f;
		}

		while (mRotation < 0.0f) {
			mRotation += 360.0f;
		}
	}

	float GameEntity::Rotation(Space space) {
		if (space == Local || mParent == nullptr) {
			return mRotation;
		}

		return mParent->Rotation(World) + mRotation;
	}

	void GameEntity::Scale(Vector2 scale) {
		mScale = scale;
	}

	Vector2 GameEntity::Scale(Space space) {
		if (space == Local || mParent == nullptr) {
			return mScale;
		}

		Vector2 scale = mParent->Scale(World);
		scale.x *= mScale.x;
		scale.y *= mScale.y;

		return scale;
	}

	void GameEntity::Active(bool active) {
		mActive = active;
	}

	bool GameEntity::Active() const {
		return mActive;
	}

	void GameEntity::Parent(GameEntity * parent) {
		if (parent == nullptr) {
			mPosition = Position(World);
			mRotation = Rotation(World);
			mScale = Scale(World);
		}
		else {
			if (mParent != nullptr) {
				Parent(nullptr);
			}
			Vector2 parentScale = parent->Scale(World);

			mPosition = RotateVector(Position(World) - parent->Position(World), -parent->Rotation(World));
			mPosition.x /= parentScale.x;
			mPosition.y /= parentScale.y;

			mRotation -= parent->Rotation(World);
			mScale = Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
		}

		mParent = parent;
	}

	GameEntity * GameEntity::Parent() const {
		return mParent;
	}

	void GameEntity::Translate(Vector2 vec, Space space) {
		if (space == World) {
			mPosition += vec;
		}
		else {
			mPosition += RotateVector(vec, Rotation());
		}
	}

	void GameEntity::Rotate(float amount) {
		Rotation(mRotation + amount);
	}
}