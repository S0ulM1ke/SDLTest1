#include "AI.h"

AI::AI(const Paddle& paddle) : mPaddle(paddle)
{
}

void AI::update(const Ball& ball, const Paddle&paddle)
{

	const auto& ballAabb = ball.getAabb();
	const auto& paddleAabb = paddle.getAabb();
	if (paddleAabb.getCenterY() != ballAabb.getCenterY())
	{
		if (ballAabb.getCenterY() > paddleAabb.getCenterY())
		{
			mPaddle.setDirection(Paddle::Direction::DOWN);
		}
		else if (ballAabb.getCenterY() < paddleAabb.getCenterY())
		{
			mPaddle.setDirection(Paddle::Direction::UP);
		}
	}
	else
	{
		mPaddle.setDirection(Paddle::Direction::NONE);
	}

}
