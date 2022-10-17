#pragma once

#include <SDL.h>

#include "AABB.h"
#include "Wall.h"

class Paddle
{
public:

	enum class Type 
	{PLAYER, COMPUTER};

	enum class Direction : int
	{ NONE = 0, UP = -1, DOWN  = 1};

	Paddle(int x, int y, Type type, int color);
	Paddle() = default;
	~Paddle() = default;

	void update(const Wall& topWall, const Wall& bottomWall);
	void draw(SDL_Renderer *renderer);

	void setDirection(Direction direction) { mDirection = direction; }
	const Direction getPaddleDir() const { return mDirection; }
	bool isMoving(Direction direction) const { return mDirection == direction; }

	void setPosY(int y) { mPosition.y = y; mAabb.setCenterY(y + mAabb.getExtentY()); }

	const AABB& getAabb() const { return mAabb; }
	AABB& getAabb() { return mAabb; }
private:

	static const int kWidth;
	static const int kHeight;
	static const int kPlayerVelocity;
	static const int kCompVelocity;
	int mColor = 0;
	int mVelocity = 0;
	Type mType;
	Direction mDirection;
	SDL_Rect mPosition = { 0 };
	AABB mAabb;
};

