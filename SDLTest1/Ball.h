#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <array>

#include "AABB.h"
#include "Wall.h"
#include "Paddle.h"


class Ball
{
public:
	static const float kVelocity;

	enum class Scores : int
	{DEFAULT = 0, PLAYER = 1, COMPUTER = 2};

	Ball() = default;
	Ball(int x, int y, float dirX, float dirY);
	~Ball();

	void init(SDL_Renderer* renderer);
	void update(const Wall& topWall, const Wall& bottomWall, const Paddle& leftPaddle, const Paddle& rightPaddle, const Wall& lefttWall, const Wall& rightWall);
	void draw(SDL_Renderer* renderer);

	void setPosX(int x) { mPosition.x = x; mAabb.setCenterX(x + mAabb.getExtentX()); }
	void setPosY(int y) { mPosition.y = y; mAabb.setCenterY(y + mAabb.getExtentY()); }
	void setVelocity(float velovcity) { mVelocity = velovcity; }

	const bool isScores(Scores score) const { return mScores == score; }
	const bool isCollided() { return mWallCollided; }
	void collisionReset() { mWallCollided = false; }

	void setDirection(const std::array<float, 2> direction) { mDirection = direction; }

	const AABB& getAabb() const { return mAabb; }
	AABB& getAabb() { return mAabb; }
private:
	bool mWallCollided = false;
	Scores mScores = Scores::DEFAULT;
	SDL_Texture* mImage = nullptr;
	SDL_Rect mPosition = { 0 };
	AABB mAabb;
	float mVelocity = 0.0f;
	std::array<float, 2>  mDirection = { 0,0 };
};

