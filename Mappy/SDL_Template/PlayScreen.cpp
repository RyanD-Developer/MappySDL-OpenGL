#include "PlayScreen.h"



PlayScreen::PlayScreen() {
	// top bar entities
	mBackground = new GLTexture("MappyRed.png", 4, 68, 1920, 1020);
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	mPlayerOne = new GLTexture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerTwo = new GLTexture("Lives", "emulogic.ttf", 32, { 0, 0, 255 });
	mHiScore = new GLTexture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerOneScore = new Scoreboard();
	mLives = new Scoreboard();
	mTopScore = new Scoreboard();

	mBackground->Parent(this);
	mTopBar->Parent(this);
	mPlayerOne->Parent(mTopBar);
	mPlayerTwo->Parent(mTopBar);
	mHiScore->Parent(mTopBar);
	mPlayerOneScore->Parent(mTopBar);
	mLives->Parent(mTopBar);
	mTopScore->Parent(mTopBar);

	mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
	mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.3f, 0.0f);
	mHiScore->Position(-30.0f, 0.0f);
	mBackground->Position(0.0f, 670.0f);
	mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.29f, 40.0f);
	mLives->Position(Graphics::SCREEN_WIDTH * 0.36f, 40.0f);
	mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);

	mLives->Score(3);
	mTopScore->Score(10000);
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position(Graphics::SCREEN_WIDTH * 0.4f, Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);
	for (int i = 0; i < 10; i++) {
		delete mTreasure[i];
		mTreasure[i] = new Treasure();
		mTreasure[i]->Parent(this);
		mTreasure[i]->Active(true);
		mTreasure[i]->Position(5000.0f, 5000.0f);
	}
}

PlayScreen::~PlayScreen() {
	delete mTopBar;
	mTopBar = nullptr;
	delete mPlayerOne;
	mPlayerOne = nullptr;
	delete mPlayerTwo;
	mPlayerTwo = nullptr;
	delete mHiScore;
	mHiScore = nullptr;
	delete mPlayerOneScore;
	mPlayerOneScore = nullptr;
	delete mLives;
	mLives = nullptr;
	delete mTopScore;
	mTopScore = nullptr;
	mTimer = nullptr;
	mAudio = nullptr;
	delete mBackground;
	mBackground = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
	for (int i = 0; i < 10; i++) {
		delete mTreasure[i];
		mTreasure[i] = nullptr;
	}
}

void PlayScreen::Update() {
	mPlayer->Update();	
	mPlayerOneScore->Score(mPlayer->Score());
	Timer1 += 0.026f;
	std::cout << mPlayer->Position().x << " , " << mPlayer->Position().y << std::endl;
	for (int i = 0; i < 10; i++) {
		if (mTreasure[i]->IgnoreCollisions()) {

		}
		else {
			if (i < 6) {
				mTreasure[i]->PositionX = i;
			}
			else {
				mTreasure[i]->PositionX = i - 4;
			}
			if (i < 6) {
				mTreasure[i]->PositionY = i;
			}
			else {
				mTreasure[i]->PositionY = i - 6;
			}
			if (i < 5) {
				mTreasure[i]->Sprite = i;
			}
			else {
				mTreasure[i]->Sprite = i - 5;
			}
			mTreasure[i]->Update();
			if ((mPlayer->Position().x + 68) >= mTreasure[i]->Position().x &&
				mPlayer->Position().x <= (mTreasure[i]->Position().x + 64) &&
				(mPlayer->Position().y + 64) >= mTreasure[i]->Position().y &&
				mPlayer->Position().y <= (mTreasure[i]->Position().y + 64) &&
				!mPlayer->IsAnimating()) {
				mTreasure[i]->Visible(false);
				mPlayer->AddScore(400);
			}
		}
	}
	if (mPlayer->Position().x < (mBackground->Position(Local).x + 58) - 960) {
		if (mPlayer->MoveReturn() == "Right") {
			mBackground->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
			for (int i = 0; i < 10; i++) {
				mTreasure[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
			}
		}
	}
	else if (mPlayer->Position().x > ((mBackground->Position().x + 960) - 153)) {
		if (mPlayer->MoveReturn() == "Left") {
			mBackground->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
			for (int i = 0; i < 10; i++) {
				mTreasure[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
			}
		}
	}
	else {
		if (mPlayer->MoveReturn() != "None") {
			if (mPlayer->MoveReturn() == "Right") {
				mBackground->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
				for (int i = 0; i < 10; i++) {
					mTreasure[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
				}
			}
			if (mPlayer->MoveReturn() == "Left") {
				mBackground->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
				for (int i = 0; i < 10; i++) {
					mTreasure[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
				}
			}
		}
	}
}

void PlayScreen::Render() {
	mBackground->Render();
	mPlayerOne->Render();
	mPlayerTwo->Render();
	mHiScore->Render();
	mPlayerOneScore->Render();
	mLives->Render();
	mTopScore->Render();
	for (int i = 0; i < 10; i++) {
		mTreasure[i]->Render();
	}
	mPlayer->Render();
}
