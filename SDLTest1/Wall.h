#pragma once

#include <SDL.h>

#include "AABB.h"

class Wall
{
public:
	Wall(int x, int y, int width, int height);
	Wall() = default;

	void draw(SDL_Renderer* rerenderer);

	const AABB& getAabb() const { return mAabb; }
	AABB& getAabb() { return mAabb; }

private:
	SDL_Rect mPosition = { 0 };
	AABB mAabb;
};

