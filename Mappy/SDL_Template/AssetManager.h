#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.h"
#include "ShaderUtil.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64)
#include <SDL_mixer.h>
#elif defined(__APPLE__)
#include <SDL2_mixer/SDL_mixer.h>
#endif
#include <map>
#include <sstream>

namespace SDLFramework {

	class AssetManager
	{
	private:
		static AssetManager* sInstance;

		std::map<std::string, SDL_Texture*> mTextures;
		std::map<std::string, SDL_Surface*> mSurfaces;
		std::map<std::string, TTF_Font*> mFonts;
		std::map<std::string, SDL_Texture*> mText;
		std::map<std::string, SDL_Surface*> mSurfaceText;
		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;

		std::map<SDL_Texture*, unsigned> mTextureRefCount;
		std::map<SDL_Surface*, unsigned> mSurfaceRefCount;
		std::map<Mix_Music*, unsigned> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned> mSFXRefCount;

		std::map<std::string, ShaderUtil> mShaders;

	private:
		TTF_Font* GetFont(std::string filename, int size);

		void UnloadTexture(SDL_Texture* texture);
		void UnloadSurface(SDL_Surface* surface);
		void UnloadMusic(Mix_Music* music);
		void UnloadSFX(Mix_Chunk* chunk);

		AssetManager();
		~AssetManager();

	public:
		static AssetManager* Instance();
		static void Release();

		SDL_Texture* GetTexture(std::string filename, bool managed = true);
		SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed = true);
		SDL_Surface* GetSurface(std::string filename, bool managed = true);
		SDL_Surface* GetTextSurface(std::string text, std::string filename, int size, SDL_Color color, bool managed = true);

		Mix_Music* GetMusic(std::string filename, bool managed = true);
		Mix_Chunk* GetSFX(std::string filename, bool managed = true);

		void LoadShader(const GLchar* vertShader, const GLchar* fragShader, const GLchar* geomShader = nullptr, std::string name = "Default");
		ShaderUtil GetShaderUtil(std::string name);

		void DestroyTexture(SDL_Texture* texture);
		void DestroySurface(SDL_Surface* surface);

		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);
	};
}
#endif