#include "AudioManager.h"

namespace SDLFramework {

	AudioManager * AudioManager::sInstance = nullptr;

	AudioManager * AudioManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AudioManager();
		}
		return sInstance;
	}

	void AudioManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}

	void AudioManager::PlayMusic(std::string filename, int loops) {
		Mix_PlayMusic(mAssetManager->GetMusic(filename), loops);
	}

	void AudioManager::PlayMusic(Mix_Music * music, int loops) {
		Mix_PlayMusic(music, loops);
	}

	void AudioManager::PauseMusic() {
		if (Mix_PlayingMusic() != 0) {
			Mix_PauseMusic();
		}
	}

	void AudioManager::ResumeMusic() {
		if (Mix_PausedMusic() != 0) {
			Mix_ResumeMusic();
		}
	}

	void AudioManager::PlaySFX(std::string filename, int loops, int channel) {
		Mix_PlayChannel(channel, mAssetManager->GetSFX(filename), loops);
	}

	void AudioManager::PlaySFX(Mix_Chunk * sfx, int loops, int channel) {
		Mix_PlayChannel(channel, sfx, loops);
	}

	AudioManager::AudioManager() {
		mAssetManager = AssetManager::Instance();

		if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
			std::cerr << "Unable to initialize SDL audio! SDL Error: " << SDL_GetError() << std::endl;
			return;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
			std::cerr << "Unable to initialize audio! Mix Error: " << Mix_GetError() << std::endl;
		}
	}

	AudioManager::~AudioManager() {
		mAssetManager = nullptr;
		Mix_CloseAudio();
		Mix_Quit();
	}
}