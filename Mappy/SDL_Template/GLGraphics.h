#ifndef __GLGRAPHICS_H
#define __GLGRAPHICS_H
#include "Graphics.h"
#include "GLTexture.h"
#include "ShaderUtil.h"

namespace SDLFramework {
	
	class GLGraphics
		: public Graphics {
		friend class Graphics;

	private:
		SDL_GLContext mGLContext;
		ShaderUtil shaderUtil;

		glm::mat4 orthoMatrix;

	public:
		void InitRenderData(Texture* texture, SDL_Rect* srcRect, GLuint quadVAO);
		void InitLoadShaderData();

		// Inherited from Graphics
		virtual void DrawSprite(GLTexture* texture, SDL_Rect* srcRect = nullptr, SDL_Rect* dstRect = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) override;

		virtual void ClearBackBuffer() override;
		virtual void Render() override;

	private:
		//Inherited from Graphics
		virtual bool Init() override;

		GLGraphics();
		~GLGraphics();
	};
}

#endif