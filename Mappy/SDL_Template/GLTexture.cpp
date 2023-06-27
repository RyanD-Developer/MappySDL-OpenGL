#include "GLGraphics.h"
#include "GLTexture.h"

namespace SDLFramework {

	GLTexture::GLTexture(std::string filename, bool managed)
		: Texture(filename, managed) { 
		SetSurfaceTexture(filename, managed);
		Data = Surface->pixels;
		
		WrapS = GL_CLAMP_TO_BORDER;
		WrapT = GL_CLAMP_TO_BORDER;

		FilterMag = GL_LINEAR;
		FilterMin = GL_LINEAR;

		mWidth = Surface->w;
		mHeight = Surface->h;
	}

	GLTexture::GLTexture(std::string filename, int x, int y, int w, int h, bool managed)
		: Texture(filename, x, y, w, h, managed) { 
		SetSurfaceTexture(filename, managed);
		Data = Surface->pixels;

		WrapS = GL_CLAMP_TO_BORDER;
		WrapT = GL_CLAMP_TO_BORDER;

		FilterMag = GL_LINEAR;
		FilterMin = GL_LINEAR;
	}

	GLTexture::GLTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed)
		: Texture(text, fontPath, size, color, managed) { 
		SetSurfaceTextTexture(text, fontPath, size, color, managed);

		WrapS = GL_CLAMP_TO_BORDER;
		WrapT = GL_CLAMP_TO_BORDER;

		FilterMag = GL_LINEAR;
		FilterMin = GL_LINEAR;

		mWidth = Surface->w;
		mHeight = Surface->h;
	}

	GLTexture::~GLTexture() {
		AssetManager::Instance()->DestroySurface(Surface);
		Surface = nullptr;
	}

	void GLTexture::Generate() {
		SDL_PixelFormat format = *Surface->format;

		GLint nOfColors = format.BytesPerPixel;
		if (nOfColors == 4) {
			if (format.Rmask == 0x000000FF) {
				Mode = GL_RGBA;
			}
			else {
				Mode = GL_BGRA;
			}
		}
		else if (nOfColors == 3) {
			if (format.Rmask == 0x000000FF) {
				Mode = GL_RGB;
			}
			else {
				Mode = GL_BGR;
			}
		}
		else {
			Mode = GL_RGBA;
		}

		glPixelStorei(GL_UNPACK_ROW_LENGTH, (Surface->pitch) / format.BytesPerPixel);

		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterMag);

		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, Surface->w, Surface->h, 0, Mode, GL_UNSIGNED_BYTE, Data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void GLTexture::Bind() {
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void GLTexture::SetSurfaceTexture(std::string filename, bool managed) {
		Surface = AssetManager::Instance()->GetSurface(filename, managed);
		Data = Surface->pixels;
		if (Surface != nullptr) {
			Generate();
		}
		else {
			std::cerr << "Unable to set surface " << filename << " in GLTexture! Surface is null." << std::endl;
		}
	}

	void GLTexture::SetSurfaceTextTexture(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
		Surface = AssetManager::Instance()->GetTextSurface(text, filename, size, color, managed);
		Data = Surface->pixels;
		if (Surface != nullptr) {
			Generate();
		}
		else {
			std::cerr << "Unable to set surface text " << filename << " in GLTexture! Surface is null." << std::endl;
		}
	}

	void GLTexture::Render() {
		UpdateDstRect();

		GLGraphics::Instance()->DrawSprite(this, mClipped ? &mSourceRect : nullptr, &mDestinationRect, Rotation(World), Flip);
	}
}