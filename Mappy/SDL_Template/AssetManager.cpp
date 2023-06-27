#include "AssetManager.h"
#include <fstream>

namespace SDLFramework {

	AssetManager* AssetManager::sInstance = nullptr;

	AssetManager* AssetManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AssetManager();
		}

		return sInstance;
	}

	void AssetManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	AssetManager::AssetManager() {
	}

	AssetManager::~AssetManager() {
		for (auto tex : mTextures) {
			if (tex.second != nullptr) {
				SDL_DestroyTexture(tex.second);
			}
		}
		mTextures.clear();

		for (auto text : mText) {
			if (text.second != nullptr) {
				SDL_DestroyTexture(text.second);
			}
		}
		mText.clear();

		for (auto font : mFonts) {
			if (font.second != nullptr) {
				TTF_CloseFont(font.second);
			}
		}
		mFonts.clear();

		for (auto mus : mMusic) {
			if (mus.second != nullptr) {
				Mix_FreeMusic(mus.second);
			}
		}
		mMusic.clear();

		for (auto sfx : mSFX) {
			if (sfx.second != nullptr) {
				Mix_FreeChunk(sfx.second);
			}
		}
		mSFX.clear();
	}

	SDL_Texture* AssetManager::GetTexture(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mTextures[fullPath] == nullptr) {
			mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
		}

		if (mTextures[fullPath] != nullptr && managed) {
			mTextureRefCount[mTextures[fullPath]] += 1;
		}

		return mTextures[fullPath];
	}

	TTF_Font* AssetManager::GetFont(std::string filename, int size) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		std::stringstream ss;
		ss << size;
		std::string key = fullPath + ss.str();

		if (mFonts[key] == nullptr) {
			mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
			if (mFonts[key] == nullptr) {
				std::cerr << "Unable to load font " << filename << "! TTF Error: " << TTF_GetError() << std::endl;
			}
		}

		return mFonts[key];
	}

	void AssetManager::UnloadTexture(SDL_Texture* texture) {
		bool found = false;
		std::string key;
		std::map<std::string, SDL_Texture*>::iterator it;

		for (it = mTextures.begin(); it != mTextures.end() && !found; it++) {
			if ((found = it->second == texture)) {
				SDL_DestroyTexture(it->second);
				key = it->first;
			}
		}

		if (found) {
			mTextures.erase(key);
		}
	}

	void AssetManager::UnloadSurface(SDL_Surface* surface) {
		bool found = false;
		std::string key;
		std::map<std::string, SDL_Surface*>::iterator it;

		for (it = mSurfaces.begin(); it != mSurfaces.end() && !found; it++) {
			if ((found = it->second == surface)) {
				SDL_FreeSurface(it->second);
				key = it->first;
			}
		}

		if (found) {
			mSurfaces.erase(key);
		}
	}

	void AssetManager::UnloadMusic(Mix_Music* music) {
		bool found = false;
		std::string key;
		std::map<std::string, Mix_Music*>::iterator it;

		for (it = mMusic.begin(); it != mMusic.end() && !found; it++) {
			if ((found = it->second == music)) {
				Mix_FreeMusic(it->second);
				key = it->first;
			}
		}

		if (found) {
			mMusic.erase(key);
		}
	}

	void AssetManager::UnloadSFX(Mix_Chunk* chunk) {
		bool found = false;
		std::string key;
		std::map<std::string, Mix_Chunk*>::iterator it;

		for (it = mSFX.begin(); it != mSFX.end() && !found; it++) {
			if ((found = it->second == chunk)) {
				Mix_FreeChunk(it->second);
				key = it->first;
			}
		}

		if (found) {
			mSFX.erase(key);
		}
	}

	SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
		std::stringstream ss;
		ss << size << (int)color.r << (int)color.g << (int)color.b;
		std::string key = text + filename + ss.str();

		if (mText[key] == nullptr) {
			TTF_Font* font = GetFont(filename, size);
			mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
		}

		if (mText[key] != nullptr && managed) {
			mTextureRefCount[mText[key]] += 1;
		}

		return mText[key];
	}

	SDL_Surface* AssetManager::GetSurface(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mSurfaces[fullPath] == nullptr) {
			mSurfaces[fullPath] = Graphics::Instance()->LoadSurface(fullPath);
		}

		if (mSurfaces[fullPath] != nullptr && managed) {
			mSurfaceRefCount[mSurfaces[fullPath]] += 1;
		}

		return mSurfaces[fullPath];
	}

	SDL_Surface* AssetManager::GetTextSurface(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
		std::stringstream ss;
		ss << size << (int)color.r << (int)color.g << (int)color.b;
		std::string key = text + filename + ss.str();

		if (mSurfaceText[key] == nullptr) {
			TTF_Font* font = GetFont(filename, size);
			mSurfaceText[key] = Graphics::Instance()->CreateTextSurface(font, text, color);
		}

		if (mSurfaceText[key] != nullptr && managed) {
			mSurfaceRefCount[mSurfaceText[key]] += 1;
		}

		return mSurfaceText[key];
	}

	Mix_Music* AssetManager::GetMusic(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mMusic[fullPath] == nullptr) {
			mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		}

		if (mMusic[fullPath] == nullptr) {
			std::cerr << "Unable to load music " << filename << "! Mix error: " << Mix_GetError() << std::endl;
		}
		else if (managed) {
			mMusicRefCount[mMusic[fullPath]] += 1;
		}

		return mMusic[fullPath];
	}

	Mix_Chunk* AssetManager::GetSFX(std::string filename, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + filename);

		if (mSFX[fullPath] == nullptr) {
			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
		}

		if (mSFX[fullPath] == nullptr) {
			std::cerr << "Unable to load SFX " << filename << "! Mix error: " << Mix_GetError() << std::endl;
		}
		else if (managed) {
			mSFXRefCount[mSFX[fullPath]] += 1;
		}

		return mSFX[fullPath];
	}

	void AssetManager::LoadShader(const GLchar* vertShader, const GLchar* fragShader, const GLchar* geomShader, std::string name) {
		std::string vFileContents;
		std::string fFileContents;
		std::string gFileContents;

		try {
			std::fstream vShaderFile(vertShader);
			std::fstream fShaderFile(fragShader);
			std::stringstream vBuffer;
			std::stringstream fBuffer;

			vBuffer << vShaderFile.rdbuf();
			vShaderFile.close();
			vFileContents = vBuffer.str();

			fBuffer << fShaderFile.rdbuf();
			fShaderFile.close();
			fFileContents = fBuffer.str();

			if (geomShader != nullptr) {
				std::fstream gShaderFile(geomShader);
				std::stringstream gBuffer;

				gBuffer << gShaderFile.rdbuf();
				gShaderFile.close();
				gFileContents = gBuffer.str();
			}

			const GLchar* vShaderCode = vFileContents.c_str();
			const GLchar* fShaderCode = fFileContents.c_str();
			const GLchar* gShaderCode = gFileContents.c_str();

			mShaders[name].Compile(vShaderCode, fShaderCode, geomShader != nullptr ? gShaderCode : nullptr);
		}
		catch (std::exception e) {
			std::cerr << "Unable to read shader files for shader " << name << "!" << std::endl;
		}
	}

	ShaderUtil AssetManager::GetShaderUtil(std::string name) {
		if (mShaders.find(name) == mShaders.end()) {
			std::cerr << "GetShaderUtil:: Unable to find shader " << name << "!" << std::endl;
		}
		return mShaders[name];
	}

	void AssetManager::DestroyTexture(SDL_Texture* texture) {
		std::map<SDL_Texture*, unsigned>::iterator it = mTextureRefCount.find(texture);

		if (it != mTextureRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				UnloadTexture(it->first);
				mTextureRefCount.erase(it->first);
			}
		}
		else {
			UnloadTexture(texture);
		}
	}

	void AssetManager::DestroySurface(SDL_Surface* surface) {
		std::map<SDL_Surface*, unsigned>::iterator it = mSurfaceRefCount.find(surface);

		if (it != mSurfaceRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				UnloadSurface(it->first);
				mSurfaceRefCount.erase(it->first);
			}
		}
		else {
			UnloadSurface(surface);
		}
	}

	void AssetManager::DestroyMusic(Mix_Music* music) {
		std::map<Mix_Music*, unsigned>::iterator it = mMusicRefCount.find(music);

		if (it != mMusicRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				UnloadMusic(it->first);
				mMusicRefCount.erase(it->first);
			}
		}
		else {
			UnloadMusic(music);
		}
	}

	void AssetManager::DestroySFX(Mix_Chunk* sfx) {
		std::map<Mix_Chunk*, unsigned>::iterator it = mSFXRefCount.find(sfx);

		if (it != mSFXRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				UnloadSFX(it->first);
				mSFXRefCount.erase(it->first);
			}
		}
		else {
			UnloadSFX(sfx);
		}
	}
}