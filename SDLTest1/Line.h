#pragma once

#include <SDL.h>
class Line
{
public:
	Line() = default;
	Line(int x, int y, int width, int height);
	void draw(SDL_Renderer* renderer);
private:
	SDL_Rect mPosition;
};

