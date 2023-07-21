#include "PlayScreen.h"

PlayScreen::PlayScreen() {
	mInput = InputManager::Instance();
	mBackground = new GLTexture("MappyRed.png", 4, 68, 1920, 1022);
	mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
	mPlayerOne = new GLTexture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerTwo = new GLTexture("Lives", "emulogic.ttf", 32, { 0, 0, 255 });
	mHiScore = new GLTexture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });
	mPlayerOneScore = new Scoreboard();
	mLives = new Scoreboard();
	mTopScore = new Scoreboard();
	GameOver = new GLTexture("Game Over Hit Escape to Retry", "emulogic.ttf", 32, { 255, 0, 0 });

	mBackground->Parent(this);
	GameOver->Parent(this);
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
	GameOver->Position((Graphics::SCREEN_WIDTH * 0.5f), Graphics::SCREEN_HEIGHT * 0.5f);
	mLives->Score(3);
	mTopScore->Score(10000);
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();
	TC[0] = 5000;
	TC[1] = 5000;
	TC[2] = 5000;
	TC[3] = 5000;

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Position((Graphics::SCREEN_WIDTH * 0.5f - 32), Graphics::SCREEN_HEIGHT * 0.8f);
	mPlayer->Active(true);
	for (int i = 0; i < 10; i++) {
		delete mTreasure[i];
		mTreasure[i] = new Treasure();
		mTreasure[i]->Parent(this);
		mTreasure[i]->Active(true);
		mTreasure[i]->Position(5000.0f, 5000.0f);
	}
	for (int i = 0; i < 5; i++) {
		delete mDoors[i];
		mDoors[i] = new Doors();
		mDoors[i]->Parent(this);
		mDoors[i]->Active(true);
		mDoors[i]->Position(5000.0f, 5000.0f);
	}
	for (int i = 0; i < 3; i++) {
		delete mCats[i];
		mCats[i] = new Cat();
		mCats[i]->Parent(this);
		mCats[i]->Active(true);
		mCats[i]->CanMove(true);
		if (i == 0) {
			mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.3f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
		}
		else if (i == 1) {
			mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.5f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
		}
		else if (i == 2) {
			mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.6f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
		}
	}
	for (int i = 0; i < 4; i++) {
		delete mTrampoline[i];
		mTrampoline[i] = new Trampoline();
		mTrampoline[i]->Parent(this);
		mTrampoline[i]->Active(true);
		if (i == 0) {
			mTrampoline[i]->Position(Vector2(784.0f, 1150.0f));
			mTrampoline[i]->SetColor(0);
		}
		else if (i == 1) {
			mTrampoline[i]->Position(Vector2(240.0f, 1150.0f));
			mTrampoline[i]->SetColor(0);
		}
		else if (i == 2) {
			mTrampoline[i]->Position(Vector2(-336.0f, 1150.0f));
			mTrampoline[i]->SetColor(0);
		}
		else if (i == 3) {
			mTrampoline[i]->Position(Vector2(-880.0f, 1150.0f));
			mTrampoline[i]->SetColor(0);
		}
	}
    
}

PlayScreen::~PlayScreen() {
	mInput = nullptr;
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
	delete GameOver;
	GameOver = nullptr;
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
	for (int i = 0; i < 3; i++) {
		delete mCats[i];
		mCats[i] = nullptr;
	}
	for (int i = 0; i < 4; i++) {
		delete mTrampoline[i];
		mTrampoline[i] = nullptr;
	}
	for (int i = 0; i < 5; i++) {
		delete mDoors[i];
		mDoors[i] = nullptr;
	}
}

void PlayScreen::Update() {
	if (!BGameOver) {
		if (mPlayer->GetDead()) {
			mLives->Score(mPlayer->Lives());
			mPlayer->Update();
			if (mPlayer->GetAnimating() || mPlayer->GetWasHit()) {
				//pause when player dead
			}
			else if (mPlayer->Lives() < 1) {
				BGameOver = true;
				mPlayer->SetDead(false);
			}
			else {
				LeevelComplete = true;
				mPlayer->SetDead(false);
			}
		}
		else {
			HandleLeevel();
			P1Score = mPlayer->Score();
			if (mPlayer->Score() > HiScore) {
				HiScore = mPlayer->Score();
			}
			mPlayerOneScore->Score(mPlayer->Score());
			mLives->Score(mPlayer->Lives());
			mPlayer->Update();
			mTopScore->Score(HiScore);
			Timer1 += 0.026f;
			std::cout << mPlayer->Position().x << " , " << mPlayer->Position().y << std::endl;
			TreasureCollected = 0;
			for (int i = 0; i < 10; i++) {
				if (mTreasure[i]->IgnoreCollisions()) {
					TreasureCollected += 1;
				}
				else {
					if (i < 6) {
						mTreasure[i]->SetPositionX(i);
					}
					else {
						mTreasure[i]->SetPositionX(i - 4);
					}
					if (i < 6) {
						mTreasure[i]->SetPositionY(i);
					}
					else {
						mTreasure[i]->SetPositionY(i - 6);
					}
					if (i < 5) {
						mTreasure[i]->SetSprite(i);
					}
					else {
						mTreasure[i]->SetSprite(i - 5);
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
			for (int i = 0; i < 4; i++) {
				mTrampoline[i]->Update();
				for (int j = 0; j < 3; j++) {
					if (mTrampoline[i]->GetColor() == 3) {
						if ((mCats[j]->Position().x + 34) <= mTrampoline[i]->Position().x + 60 &&
							mCats[j]->Position().x - 34 >= (mTrampoline[i]->Position().x - 60) &&
							(mCats[j]->Position().y + 32) >= mTrampoline[i]->Position().y - 14 &&
							mCats[j]->Position().y - 32 <= (mTrampoline[i]->Position().y + 50) &&
							mCats[j]->GetDirection() == "None") {
							mCats[j]->Visible(false);
							mCats[j]->CanMove(false);
							TC[j] = i;
						}
						if ((mCats[j]->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
							mCats[j]->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
							!mCats[j]->GetGoingUp() &&
							!mCats[j]->GetGoingDown() &&
							!mCats[j]->GetTrampolineOnce()) {
							mCats[j]->SetGoingDown(true);
							mCats[j]->SetTrampolineOnce(true);
							mCats[j]->SetTrampolineTarget(mTrampoline[i]->Position().x);
							TC[j] = i;
						}
						if ((mCats[j]->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
							mCats[j]->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
							mCats[j]->Position().y < 400.0f &&
							mCats[j]->GetGoingUp() &&
							!mCats[j]->GetGoingDown() &&
							mCats[j]->GetDirection() == "None") {
							mCats[j]->SetGoingUp(false);
							mCats[j]->SetGoingDown(true);
							TC[j] = i;
						}
						if (TC[j] != 5000) {
							mCats[j]->SetTrampolineTarget(mTrampoline[TC[j]]->Position().x);
							if ((mCats[j]->Position().x + 34) > (mTrampoline[TC[j]]->Position().x + 60) ||
								mCats[j]->Position().x - 34 < mTrampoline[TC[j]]->Position().x - 60) {
								mCats[j]->SetGoingDown(false);
								mCats[j]->SetGoingUp(false);
								BounceBool = false;
								mTrampoline[i]->SetBounced(false);
								mCats[j]->SetInPlace(false);
								TC[j] = 5000;
							}
						}
					}
					else {
						if ((mCats[j]->Position().x + 34) <= mTrampoline[i]->Position().x + 60 &&
							mCats[j]->Position().x - 34 >= (mTrampoline[i]->Position().x - 60) &&
							(mCats[j]->Position().y + 32) >= mTrampoline[i]->Position().y - 14 &&
							mCats[j]->Position().y - 32 <= (mTrampoline[i]->Position().y + 50) &&
							!mCats[j]->GetGoingUp() &&
							mCats[j]->GetDirection() == "None") {
							mTrampoline[i]->SetBounced(true);
							mCats[j]->SetGoingDown(false);
							mCats[j]->SetGoingUp(true);
							mTrampoline[i]->AddColor();
							TC[j] = i;
						}
						if ((mCats[j]->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
							mCats[j]->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
							!mCats[j]->GetGoingUp() &&
							!mCats[j]->GetGoingDown() &&
							!mCats[j]->GetTrampolineOnce()) {
							mCats[j]->SetGoingDown(true);
							mCats[j]->SetTrampolineOnce(true);
							mCats[j]->SetTrampolineTarget(mTrampoline[i]->Position().x);
							TC[j] = i;
						}
						if ((mCats[j]->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
							mCats[j]->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
							mCats[j]->Position().y < 400.0f &&
							!mCats[j]->GetGoingDown() &&
							mCats[j]->GetGoingUp() &&
							mCats[j]->GetDirection() == "None") {
							mCats[j]->SetGoingUp(false);
							mCats[j]->SetGoingDown(true);
							TC[j] = i;
						}
						if (TC[j] != 5000) {
							mCats[j]->SetTrampolineTarget(mTrampoline[TC[j]]->Position().x);
							if ((mCats[j]->Position().x + 34) > (mTrampoline[TC[j]]->Position().x + 60) ||
								mCats[j]->Position().x - 34 < mTrampoline[TC[j]]->Position().x - 60) {
								mCats[j]->SetGoingDown(false);
								mCats[j]->SetGoingUp(false);
								BounceBool = false;
								mTrampoline[i]->SetBounced(false);
								mCats[j]->SetInPlace(false);
								TC[j] = 5000;
							}
						}
					}
				}
				if (mTrampoline[i]->GetColor() == 3) {
					if ((mPlayer->Position().x + 34) <= mTrampoline[i]->Position().x + 60 &&
						mPlayer->Position().x - 34 >= (mTrampoline[i]->Position().x - 60) &&
						(mPlayer->Position().y + 32) >= mTrampoline[i]->Position().y - 14 &&
						mPlayer->Position().y - 32 <= (mTrampoline[i]->Position().y + 50) &&
						!mPlayer->IsAnimating()) {
						mPlayer->WasHit();
						mPlayer->SetGoingDown(false);
						mPlayer->SetGoingUp(true);
						TC[3] = i;
					}
					if ((mPlayer->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
						mPlayer->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
						!mPlayer->IsAnimating() &&
						!mPlayer->GetGoingUp()) {
						mPlayer->SetGoingDown(true);
						TC[3] = i;
					}
					if ((mPlayer->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
						mPlayer->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
						!mPlayer->IsAnimating() &&
						mPlayer->Position().y < 400.0f &&
						mPlayer->GetGoingUp()) {
						mPlayer->SetGoingUp(false);
						mPlayer->SetGoingDown(true);
						TC[3] = i;
					}
					if (TC[3] != 5000) {
						if ((mPlayer->Position().x + 34) > (mTrampoline[TC[3]]->Position().x + 60) ||
							mPlayer->Position().x - 34 < mTrampoline[TC[3]]->Position().x - 60) {
							mPlayer->SetGoingDown(false);
							mPlayer->SetGoingUp(false);
							BounceBool = false;
							mTrampoline[i]->SetBounced(false);
							mPlayer->SetInPlace(false);
							TC[3] = 5000;
						}
					}
				}
				else {
					if ((mPlayer->Position().x + 34) <= mTrampoline[i]->Position().x + 60 &&
						mPlayer->Position().x - 34 >= (mTrampoline[i]->Position().x - 60) &&
						(mPlayer->Position().y + 32) >= mTrampoline[i]->Position().y - 14 &&
						mPlayer->Position().y - 32 <= (mTrampoline[i]->Position().y + 50) &&
						!mPlayer->IsAnimating()) {
						mTrampoline[i]->SetBounced(true);
						mPlayer->SetGoingDown(false);
						mPlayer->SetGoingUp(true);
						mTrampoline[i]->AddColor();
						TC[3] = i;
					}
					if ((mPlayer->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
						mPlayer->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
						!mPlayer->IsAnimating() &&
						!mPlayer->GetGoingUp()) {
						mPlayer->SetGoingDown(true);
						TC[3] = i;
					}
					if ((mPlayer->Position().x + 34) <= (mTrampoline[i]->Position().x + 60) &&
						mPlayer->Position().x - 34 >= mTrampoline[i]->Position().x - 60 &&
						!mPlayer->IsAnimating() &&
						mPlayer->Position().y < 400.0f &&
						mPlayer->GetGoingUp()) {
						mPlayer->SetGoingUp(false);
						mPlayer->SetGoingDown(true);
						TC[3] = i;
					}
					if (TC[3] != 5000) {
						if ((mPlayer->Position().x + 34) > (mTrampoline[TC[3]]->Position().x + 60) ||
							mPlayer->Position().x - 34 < mTrampoline[TC[3]]->Position().x - 60) {
							mPlayer->SetGoingDown(false);
							mPlayer->SetGoingUp(false);
							BounceBool = false;
							mTrampoline[i]->SetBounced(false);
							mPlayer->SetInPlace(false);
							TC[3] = 5000;
						}
					}
				}
			}

			for (int i = 0; i < 3; i++) {
				mCats[i]->Update();
				if (mPlayer->GetInPlace()) {
					mCats[i]->SetPInPlace(true);
				}
				else {
					mCats[i]->SetPInPlace(false);
				}
				mCats[i]->SetMoveBounds(Vector2((mBackground->Position(Local).x + 58) - 960, ((mBackground->Position().x + 960) - 153)));
				mCats[i]->SetMovement(Vector2(mPlayer->Position(Local).x, mPlayer->Position(Local).y));
			}

			for (int i = 0; i < 5; i++) {
				if (mDoors[i]->IgnoreCollisions()) {

				}
				else {
					if (i < 3) {
						mDoors[i]->SetPositionX(i);
					}
					else {
						mDoors[i]->SetPositionX(i - 2);
					}
					mDoors[i]->SetPositionY(i);
					mDoors[i]->Update();
				}
			}

			for (int k = 0; k < 5; k++) {
				if (!mDoors[k]->CheckDoorOpen() && mPlayer->Position().x - 34 < (mDoors[k]->Position().x + 10) && mPlayer->Position().x + 34 < (mDoors[k]->Position().x + 78) && mPlayer->Position().x - 34 > (mDoors[k]->Position().x - 10) && (mPlayer->Position().y + 32) >= mDoors[k]->Position().y - 48 && mPlayer->Position().y - 32 <= (mDoors[k]->Position().y + 48)) {
					StuckDoor = true;
					if (mPlayer->MoveReturn() == "Right") {
						mBackground->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						for (int i = 0; i < 10; i++) {
							mTreasure[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 4; i++) {
							mTrampoline[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 5; i++) {
							mDoors[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 3; i++) {
							mCats[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						StuckDoor = false;
					}
				}
				else if (!mDoors[k]->CheckDoorOpen() && mPlayer->Position().x + 34 > (mDoors[k]->Position().x - 10) && mPlayer->Position().x - 34 > (mDoors[k]->Position().x - 78) && mPlayer->Position().x + 34 < (mDoors[k]->Position().x + 10) && (mPlayer->Position().y + 32) >= mDoors[k]->Position().y - 48 && mPlayer->Position().y - 32 <= (mDoors[k]->Position().y + 48)) {
					StuckDoor = true;
					if (mPlayer->MoveReturn() == "Left") {
						mBackground->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						for (int i = 0; i < 10; i++) {
							mTreasure[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 4; i++) {
							mTrampoline[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 5; i++) {
							mDoors[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 3; i++) {
							mCats[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						StuckDoor = false;
					}
					if (mInput->KeyPressed(SDL_SCANCODE_SPACE)) {
						StuckDoor = false;
						mDoors[k]->OpenDoor(true);
					}
				}
			}

			if (!StuckDoor) {
				if (mPlayer->Position().x < (mBackground->Position(Local).x + 58) - 960) {
					if (mPlayer->MoveReturn() == "Right") {
						mBackground->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						for (int i = 0; i < 10; i++) {
							mTreasure[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 4; i++) {
							mTrampoline[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 5; i++) {
							mDoors[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 3; i++) {
							mCats[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
					}
				}
				else if (mPlayer->Position().x > ((mBackground->Position().x + 960) - 153)) {
					if (mPlayer->MoveReturn() == "Left") {
						mBackground->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						for (int i = 0; i < 10; i++) {
							mTreasure[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 4; i++) {
							mTrampoline[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 5; i++) {
							mDoors[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
						}
						for (int i = 0; i < 3; i++) {
							mCats[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
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
							for (int i = 0; i < 4; i++) {
								mTrampoline[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
							for (int i = 0; i < 5; i++) {
								mDoors[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
							for (int i = 0; i < 3; i++) {
								mCats[i]->Translate(-Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
						}
						if (mPlayer->MoveReturn() == "Left") {
							mBackground->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							for (int i = 0; i < 10; i++) {
								mTreasure[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
							for (int i = 0; i < 4; i++) {
								mTrampoline[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
							for (int i = 0; i < 5; i++) {
								mDoors[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
							for (int i = 0; i < 3; i++) {
								mCats[i]->Translate(Vec2_Right * 300.0f * mTimer->DeltaTime(), World);
							}
						}
					}
				}
			}
		}
	}
    else if(BGameOver){
	 HandleLeevel();
	}
}

void PlayScreen::Render() {
	if (!BGameOver) {
		mBackground->Render();
		mPlayerOne->Render();
		mPlayerTwo->Render();
		mHiScore->Render();
		mPlayerOneScore->Render();
		mLives->Render();
		mTopScore->Render();
		if (mPlayer->GetDead() && mPlayer->IgnoreCollisions() && mPlayer->GetAnimating()) {

		}
		else {

		}
		for (int i = 0; i < 10; i++) {
			mTreasure[i]->Render();
		}
		for (int i = 0; i < 4; i++) {
			mTrampoline[i]->Render();
		}
		for (int i = 0; i < 3; i++) {
			mCats[i]->Render();
		}
		for (int i = 0; i < 5; i++) {
			mDoors[i]->Render();
		}
		mPlayer->Render();
	}
	else if(BGameOver){
		GameOver->Render();
	}
}

void PlayScreen::HandleLeevel() {
	if (TreasureCollected == 10) {
		mLeevel += 1;
		LeevelComplete = true;
	}
	if (LeevelComplete) {
		mPlayer->Position((Graphics::SCREEN_WIDTH * 0.5f - 32), Graphics::SCREEN_HEIGHT * 0.8f);
		if (mLeevel == 1) {
			delete mBackground;
			mBackground = new GLTexture("MappyRed.png", 4, 68, 1920, 1022);
			mBackground->Parent(this);
			mBackground->Position(0.0f, 670.0f);
			for (int i = 0; i < 10; i++) {
				mTreasure[i]->Visible(true);
				mTreasure[i]->Position(5000.0f, 5000.0f);
			}
			for (int i = 0; i < 5; i++) {
				delete mDoors[i];
				mDoors[i] = new Doors();
				mDoors[i]->Parent(this);
				mDoors[i]->Active(true);
				mDoors[i]->Position(5000.0f, 5000.0f);
			}
			for (int i = 0; i < 3; i++) {
				delete mCats[i];
				mCats[i] = new Cat();
				mCats[i]->Parent(this);
				mCats[i]->Active(true);
				mCats[i]->CanMove(true);
				if (i == 0) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.3f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
				else if (i == 1) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.5f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
				else if (i == 2) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.6f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
			}
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					mTrampoline[i]->Position(Vector2(784.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 1) {
					mTrampoline[i]->Position(Vector2(240.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 2) {
					mTrampoline[i]->Position(Vector2(-336.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 3) {
					mTrampoline[i]->Position(Vector2(-880.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
			}
			LeevelComplete = false;
		}
		else if (mLeevel == 2) {
			delete mBackground;
			mBackground = new GLTexture("MappyGreen.png", 4, 68, 1920, 1022);
			mBackground->Parent(this);
			mBackground->Position(0.0f, 670.0f);
			for (int i = 0; i < 10; i++) {
				mTreasure[i]->Visible(true);
				mTreasure[i]->Position(5000.0f, 5000.0f);
			}
			for (int i = 0; i < 3; i++) {
				delete mCats[i];
				mCats[i] = new Cat();
				mCats[i]->Parent(this);
				mCats[i]->Active(true);
				mCats[i]->CanMove(true);
				if (i == 0) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.3f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
				else if (i == 1) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.5f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
				else if (i == 2) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.6f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
			}
			for (int i = 0; i < 5; i++) {
				delete mDoors[i];
				mDoors[i] = new Doors();
				mDoors[i]->Parent(this);
				mDoors[i]->Active(true);
				mDoors[i]->Position(5000.0f, 5000.0f);
			}
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					mTrampoline[i]->Position(Vector2(784.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 1) {
					mTrampoline[i]->Position(Vector2(240.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 2) {
					mTrampoline[i]->Position(Vector2(-336.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 3) {
					mTrampoline[i]->Position(Vector2(-880.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
			}
			LeevelComplete = false;
		}
		else if (mLeevel == 3) {
			delete mBackground;
			mBackground = new GLTexture("MappyBlue.png", 4, 68, 1920, 1022);
			mBackground->Parent(this);
			mBackground->Position(0.0f, 670.0f);
			for (int i = 0; i < 10; i++) {
				mTreasure[i]->Visible(true);
				mTreasure[i]->Position(5000.0f, 5000.0f);
			}
			for (int i = 0; i < 3; i++) {
				delete mCats[i];
				mCats[i] = new Cat();
				mCats[i]->Parent(this);
				mCats[i]->Active(true);
				mCats[i]->CanMove(true);
				if (i == 0) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.3f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
				else if (i == 1) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.5f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
				else if (i == 2) {
					mCats[i]->Position((Graphics::SCREEN_WIDTH * 0.6f - 32), Graphics::SCREEN_HEIGHT * 0.4f);
				}
			}
			for (int i = 0; i < 5; i++) {
				delete mDoors[i];
				mDoors[i] = new Doors();
				mDoors[i]->Parent(this);
				mDoors[i]->Active(true);
				mDoors[i]->Position(5000.0f, 5000.0f);
			}
			for (int i = 0; i < 4; i++) {
				if (i == 0) {
					mTrampoline[i]->Position(Vector2(784.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 1) {
					mTrampoline[i]->Position(Vector2(240.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 2) {
					mTrampoline[i]->Position(Vector2(-336.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
				else if (i == 3) {
					mTrampoline[i]->Position(Vector2(-880.0f, 1150.0f));
					mTrampoline[i]->SetColor(0);
				}
			}
			LeevelComplete = false;
		}
		else if (mLeevel > 3) {
			mLeevel -= 4;
		}
	}
}

void PlayScreen::Reset() {
	BGameOver = false;
	LeevelComplete = true;
	mLeevel = 1;
	mPlayer->Reset();
}

bool PlayScreen::ReturnGameOver() {
	return BGameOver;
}