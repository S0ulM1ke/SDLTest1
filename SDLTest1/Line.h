#pragma once

#include <SDL.h>
class Line
{
public:
	Line() = default;
	Line(int x, int y, int width, int height, int color);
	void draw(SDL_Renderer* renderer);
private:
	int mColor;
	SDL_Rect mPosition;
};

