#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
#include "GLTexture.h"
#include <vector>

using namespace SDLFramework;

class Scoreboard : public GameEntity {
private:
	std::vector<GLTexture *> mScore;

	SDL_Color mColor;

public:
	Scoreboard();
	Scoreboard(SDL_Color color);
	~Scoreboard();

	void Score(int score);

	void Render() override;

private:
	void ClearBoard();
};
#endif