#include "Line.h"

Line::Line(int x, int y, int width, int height, int color) : mPosition({ x, y, width, height}), mColor(color)
{
}

void Line::draw(SDL_Renderer* renderer)
{
	// Отрисовка вертикальной линии-сетки

	for (float y = static_cast<float>(mPosition.y); y < mPosition.h; y+= (1.93f * mPosition.w))
	{
		SDL_Rect rect{ mPosition.x, static_cast<int>(y), mPosition.w, mPosition.w };
		SDL_SetRenderDrawColor(renderer, mColor, mColor, mColor, mColor);
		SDL_RenderFillRect(renderer, &rect);

	}
}
