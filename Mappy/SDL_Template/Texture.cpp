#include "Texture.h"

namespace SDLFramework {

	Texture::Texture(std::string filename, bool managed) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename, managed);

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

		mClipped = false;

		mSourceRect = SDL_Rect();

		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	Texture::Texture(std::string filename, int x, int y, int w, int h, bool managed) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetTexture(filename, managed);

		mWidth = w;
		mHeight = h;

		mClipped = true;
		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;

		mSourceRect.x = x;
		mSourceRect.y = y;
		mSourceRect.w = mWidth;
		mSourceRect.h = mHeight;
	}

	Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed) {
		mGraphics = Graphics::Instance();
		mTex = AssetManager::Instance()->GetText(text, fontPath, size, color, managed);

		mClipped = false;

		SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

		mSourceRect = SDL_Rect();

		mDestinationRect.w = mWidth;
		mDestinationRect.h = mHeight;
	}

	Texture::~Texture() {
		AssetManager::Instance()->DestroyTexture(mTex);
		mTex = nullptr;
		mGraphics = nullptr;
	}

	Vector2 Texture::ScaledDimensions() {
		Vector2 scaledDimensions = Scale();
		scaledDimensions.x *= mWidth;
		scaledDimensions.y *= mHeight;

		return scaledDimensions;
	}

	void Texture::SetSourceRect(SDL_Rect * sourceRect) {
		mSourceRect = *sourceRect;
	}

	void Texture::Render() {
		UpdateDstRect();

		mGraphics->DrawTexture(mTex, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World));
	}

	void Texture::UpdateDstRect() {
		Vector2 pos = Position(World);
		Vector2 scale = Scale(World);
		mDestinationRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
		mDestinationRect.y = (int)(pos.y - mHeight * scale.y * 0.5f);
		mDestinationRect.w = (int)(mWidth * scale.x);
		mDestinationRect.h = (int)(mHeight * scale.y);
	}
}