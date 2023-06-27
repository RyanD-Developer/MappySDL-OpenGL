#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "Timer.h"
#include "AudioManager.h"
#include "Scoreboard.h"
#include "Player.h"

class PlayScreen : public GameEntity {
private:
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mPlayerTwo;
	Texture* mHiScore;
	Scoreboard* mLives;
	Scoreboard* mPlayerOneScore;
	Scoreboard* mTopScore;
	Timer * mTimer;
	AudioManager * mAudio;

	Player * mPlayer;


public:
	PlayScreen();
	~PlayScreen();

	void Update() override;
	void Render() override;
};
#endif