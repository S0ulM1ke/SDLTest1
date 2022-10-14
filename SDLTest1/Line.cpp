#include "Line.h"

Line::Line(int x, int y, int width, int height) : mPosition({ x, y, width, height})
{
}

void Line::draw(SDL_Renderer* renderer)
{

	for (float y = static_cast<float>(mPosition.y); y < mPosition.h; y+= (1.93 * mPosition.w))
	{
		SDL_Rect rect{ mPosition.x, static_cast<int>(y), mPosition.w, mPosition.w };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);

	}
}
