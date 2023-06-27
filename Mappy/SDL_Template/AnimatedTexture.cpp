#include "AnimatedTexture.h"

namespace SDLFramework {

	void AnimatedTexture::RunAnimation() {
		if (!mAnim.done) {
			mAnim.frameTimer += mTimer->DeltaTime();

			if (mAnim.frameTimer >= mAnim.speed) {
				if (mAnim.wrapMode == Animation::WrapModes::Loop) {
					// reset timer, accounting for extra time
					mAnim.frameTimer -= mAnim.speed;
				}
				else {
					mAnim.done = true;
					// back up the timer to the last frame
					mAnim.frameTimer = mAnim.speed - mAnim.timePerFrame;
				}
			}

			if (mAnim.layout == Animation::Layouts::Horizontal) {
				mSourceRect.x = mAnim.startX + (int)(mAnim.frameTimer / mAnim.timePerFrame) * mWidth;
			}
			else {
				mSourceRect.y = mAnim.startY + (int)(mAnim.frameTimer / mAnim.timePerFrame) * mHeight;
			}
		}
	}

	AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, Animation::Layouts layout, bool managed)
		: Texture(filename, x, y, w, h, managed) {
		mTimer = Timer::Instance();

		mAnim.startX = x;
		mAnim.startY = y;

		mAnim.frameCount = frameCount;
		mAnim.speed = animationSpeed;
		mAnim.timePerFrame = mAnim.speed / mAnim.frameCount;
		mAnim.frameTimer = 0.0f;

		mAnim.wrapMode = Animation::WrapModes::Loop;
		mAnim.layout = layout;

		mAnim.done = false;
	}

	AnimatedTexture::~AnimatedTexture() { }

	void AnimatedTexture::SetWrapMode(Animation::WrapModes wrapMode) {
		mAnim.wrapMode = wrapMode;
	}

	void AnimatedTexture::ResetAnimation() {
		mAnim.frameTimer = 0.0f;
		mAnim.done = false;
	}

	bool AnimatedTexture::IsAnimating() {
		return !mAnim.done;
	}

	void AnimatedTexture::Update() {
		RunAnimation();
	}
}