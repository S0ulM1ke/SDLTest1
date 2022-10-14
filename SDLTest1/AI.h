#pragma once

#include "Paddle.h"
#include "Ball.h"
class AI
{
public:
	AI(const Paddle& paddle);
	Paddle::Direction getAiDir() { return mPaddle.getPaddleDir(); }
	void update(const Ball& ball, const Paddle& paddle);
private:
	Paddle mPaddle;
};

