#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "InputManager.h"
#include "Doors.h"
#include "AudioManager.h"
#include "Scoreboard.h"
#include "Player.h"
#include "Treasure.h"
#include "Trampoline.h"

class PlayScreen : public GameEntity {
private:
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;
	Scoreboard* mLives;
	InputManager* mInput;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mTopScore;
	Timer * mTimer;
	AudioManager * mAudio;
    Texture* mBackground;
	Player * mPlayer;
	Treasure* mTreasure[10];
	Trampoline* mTrampoline[4];
	Doors* mDoors[5];
	
	int TC = 5000;
	bool BounceBool = false;
	bool xTaken[6];
	bool yTaken[5];
	bool StuckDoor = false;
	bool xDone = false;
	bool yDone = false;
	float Timer1 = 0.0f;


public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;
};
#endif