#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class Score
{
public:
	Score() = default;
	Score(int x, int y);
	~Score();
	void increaseScore();
	void init(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void setPosX(int x) { mPosition.x = x; }
	void setPosY(int y) { mPosition.y = y; }

private:
	int mValue = 0;
	SDL_Rect mPosition;
	SDL_Texture* mText = nullptr;
	_TTF_Font* mFont = nullptr;

};

