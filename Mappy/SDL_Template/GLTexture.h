#ifndef __GLTEXTURE_H
#define __GLTEXTURE_H
#include "Texture.h"

#include <glew.h>

namespace SDLFramework {

	class GLTexture
		: public Texture {
	public:
		GLuint ID;
		GLuint WrapS, WrapT;
		GLuint FilterMag, FilterMin;

		int Mode;
		bool Rendererd;
		void* Data;
		SDL_RendererFlip Flip;
		SDL_Surface* Surface;

		GLTexture(std::string filename, bool managed = false);
		GLTexture(std::string filename, int x, int y, int w, int h, bool managed = false);
		GLTexture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = false);
		virtual ~GLTexture();

		void Generate();
		void Bind();

		void SetSurfaceTexture(std::string filename, bool managed = false);
		void SetSurfaceTextTexture(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);

		// Inherited from Texture
		virtual void Render() override;
	};
}
#endif
