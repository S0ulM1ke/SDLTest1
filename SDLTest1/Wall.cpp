#include "Wall.h"

Wall::Wall(int x, int y, int width, int height) :mPosition({ x, y, width, height})
{
	mAabb.setCenterX(x + width / 2);
	mAabb.setCenterY(y + height / 2);
	mAabb.setExtentX(width / 2);
	mAabb.setExtentY(height / 2);
}

void Wall::draw(SDL_Renderer* rerenderer)
{
	SDL_RenderFillRect(rerenderer, &mPosition);
}
