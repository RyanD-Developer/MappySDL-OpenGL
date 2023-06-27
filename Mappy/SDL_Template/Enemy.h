#ifndef __ENEMY_H
#define __ENEMY_H
#include "AnimatedTexture.h"
#include "BezierPath.h"
#include "Formation.h"
#include "PhysEntity.h"
#include "Player.h"

class Enemy : public PhysEntity {
public:
	enum States { FlyIn, InFormation, Diving, Dead };
	enum Types { Butterfly, Wasp, Boss };

protected:
	static std::vector<std::vector<Vector2>> sPaths;
	static Formation * sFormation;
	static Player * sPlayer;

	Timer * mTimer;

	Texture * mTextures[2];

	States mCurrentState;

	unsigned mCurrentPath;

	unsigned mCurrentWaypoint;
	const float EPSILON = 50.0f;

	float mSpeed;

	int mIndex;
	Types mType;

	bool mChallengeStage;

	Vector2 mDiveStartPosition;

	AnimatedTexture * mDeathAnimation;

protected:
	virtual void PathComplete();

	virtual void FlyInComplete();

	void JoinFormation();
	virtual Vector2 WorldFormationPosition();
	virtual Vector2 LocalFormationPosition() = 0;

	virtual void HandleFlyInState();
	virtual void HandleFormationState();
	virtual void HandleDiveState() = 0;
	virtual void HandleDeadState();

	void HandleStates();

	virtual void RenderFlyInState();
	virtual void RenderFormationState();
	virtual void RenderDiveState() = 0;
	virtual void RenderDeadState();

	void RenderStates();

	// Inherited from PhysEntity
	bool IgnoreCollisions() override;

public:
	static void CreatePaths();
	static void SetFormation(Formation * formation);
	static void CurrentPlayer(Player * player);

	Enemy(int path, int index, bool challenge);
	virtual ~Enemy();

	// Inherited from PhysEntity
	virtual void Hit(PhysEntity * other) override;
	
	States CurrentState();

	Types Type();

	int Index();

	virtual void Dive(int type = 0);

	bool InDeathAnimation();

	void Update() override;
	void Render() override;
};
#endif