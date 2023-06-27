#ifndef __ANIMATEDGLTEXTURE_H
#define __ANIMATEDGLTEXTURE_H
#include "AnimatedTexture.h"
#include "GLTexture.h"

namespace SDLFramework {

	class AnimatedGLTexture
		: public GLTexture {

	protected:
		Timer* mTimer;
		
		Animation mAnim;

		virtual void RunAnimation();

	public:
		AnimatedGLTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, Animation::Layouts layout, bool managed = false);
		~AnimatedGLTexture();

		void SetWrapMode(Animation::WrapModes mode);

		virtual void ResetAnimation();
		bool IsAnimating();

		void Update();
	};
}
#endif