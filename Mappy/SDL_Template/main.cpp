#include "GameManager.h"

using SDLFramework::GameManager;

int main(int argc, char * args[])
{
	GameManager * game = GameManager::Instance();

	game->Run();

	GameManager::Release();
	game = nullptr;

	return 0;
}