#ifndef __LEVEL_H
#define __LEVEL_H
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Butterfly.h"
#include "Wasp.h"
#include "Boss.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class Level : public GameEntity {
public:
	enum LevelStates { Running, Finished, GameOver };

private:
	Timer * mTimer;
	PlaySideBar * mSideBar;
	BackgroundStars * mStars;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture * mStageLabel;
	Scoreboard * mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture * mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player * mPlayer;
	bool mPlayerHit;
	float mRespawnDelay;
	float mRespawnTimer;
	float mRespawnLabelOnScreen;

	Texture * mGameOverLabel;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LevelStates mCurrentState;

	bool mChallengeStage;

	Formation * mFormation;

	static const int MAX_BUTTERFLIES = 16;
	static const int MAX_WASPS = 20;
	static const int MAX_BOSSES = 4;

	int mButterflyCount;
	int mWaspCount;
	int mBossCount;

	Butterfly * mFormationButterflies[MAX_BUTTERFLIES];
	Wasp * mFormationWasps[MAX_WASPS];
	Boss * mFormationBosses[MAX_BOSSES];

	std::vector<Enemy*> mEnemies;

	XMLDocument mSpawningPatterns;
	int mCurrentFlyInPriority;
	int mCurrentFlyInIndex;

	float mSpawnDelay;
	float mSpawnTimer;
	bool mSpawningFinished;

	Butterfly * mDivingButterfly;
	bool mSkipFirstButterfly;
	float mButterflyDiveDelay;
	float mButterflyDiveTimer;

	Wasp * mDivingWasp;
	Wasp * mDivingWasp2;
	float mWaspDiveDelay;
	float mWaspDiveTimer;

	Boss * mDivingBoss;
	bool mCaptureDive;
	bool mSkipFirstBoss;
	float mBossDiveDelay;
	float mBossDiveTimer;

private:
	void StartStage();
	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();

	bool EnemyFlyingIn();

	void HandleEnemySpawning();
	void HandleEnemyFormation();
	void HandleEnemyDiving();
public:
	Level(int stage, PlaySideBar * sideBar, Player * player);
	~Level();

	LevelStates State();

	void Update() override;
	void Render() override;
};
#endif