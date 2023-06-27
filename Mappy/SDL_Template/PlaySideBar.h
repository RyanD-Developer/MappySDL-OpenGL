#ifndef __PLAYSIDEBAR_H
#define __PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlaySideBar : public GameEntity {
private:
	static const int MAX_SHIP_TEXTURES = 5;

	Timer * mTimer;
	AudioManager * mAudio;

	Texture * mBackground;

	Texture * mHighLabel;
	Texture * mScoreLabel;
	Scoreboard * mHighScoreboard;

	Texture * mPlayerOneLabel;
	float mBlinkTimer;
	float mBlinkInterval;
	bool mPlayerOneLabelVisible;

	Scoreboard * mPlayerOneScore;

	GameEntity * mShips;
	Texture * mShipTextures[MAX_SHIP_TEXTURES];
	Scoreboard * mTotalShipsLabel;
	int mTotalShips;

	GameEntity * mFlags;
	std::vector<Texture *> mFlagTextures;
	int mRemainingLevels;
	float mFlagXOffset;
	float mFlagYOffset;
	float mFlagTimer;
	float mFlagInterval;

private:
	void ClearFlags();
	void AddNextFlag();
	void AddFlag(std::string filename, float width, int value);

public:
	PlaySideBar();
	~PlaySideBar();

	void SetHighScore(int score);
	void SetPlayerScore(int score);
	void SetShips(int ships);
	void SetLevel(int level);

	void Update() override;
	void Render() override;
};
#endif