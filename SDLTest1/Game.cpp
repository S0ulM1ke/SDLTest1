#include "Game.h"

#include <SDL_timer.h>

Game::Game()
	: mResolution({ 680,480 }), mBox({ 600, 400 }), mAi(mRightPaddle)
{
	SDL_CreateWindowAndRenderer(mResolution[0], mResolution[1], SDL_WINDOW_RESIZABLE, &mGameWindow, &mGameWindowRenderer);
	SDL_RenderSetLogicalSize(mGameWindowRenderer, mBox[0], mBox[1]);

	mHafBox = { mBox[0] / 2, mBox[1] / 2 };
	mLine = {mHafBox[0] - 10/2, 5, 10, mBox[1]};
	mLeftPaddle = { 0, mHafBox[1] - 50 , Paddle::Type::PLAYER};
	mRightPaddle = { mBox[0] - 50, mHafBox[1] - 50 , Paddle::Type::COMPUTER};
	mTopWall = { 0, 0, mBox[0], 0 };
	mBottomWall = { 0, mBox[1], mBox[0], 0 };
	mLeftWall = { 0, 0, 0 , mBox[1] };
	mRightWall = { mBox[0], 0 , 0, mBox[1] };
	mBall = { mHafBox[0] - 12, mHafBox[1] - 12 };
	mPlayerScore = { mHafBox[0] / 2 , 0};
	mComputerScore = {static_cast<int>(mHafBox[0] * 1.5), 0};

	mBall.init(mGameWindowRenderer);
	mPlayerScore.init(mGameWindowRenderer);
	mComputerScore.init(mGameWindowRenderer);
}

void Game::gameLoop()
{
	bool keep_running = true;
	while (keep_running)
	{
		while (SDL_PollEvent(&mGameWindowEvent) > 0)
		{
			switch (mGameWindowEvent.type)
			{
			case SDL_QUIT:
				keep_running = false;
				break;
			case SDL_KEYDOWN:
				onKeyDown(mGameWindowEvent.key);
				break;
			case SDL_KEYUP:
				onKeyUp(mGameWindowEvent.key);
				break;
			}
		}

		update(8);
		draw();
	}
}

void Game::update(int delayTime)
{
	mLeftPaddle.update(mTopWall, mBottomWall);
	mRightPaddle.update(mTopWall, mBottomWall);
	mBall.update(mTopWall, mBottomWall, mLeftPaddle, mRightPaddle, mLeftWall, mRightWall);
	mAi.update(mBall, mRightPaddle);
	mRightPaddle.setDirection(mAi.getAiDir());
	if (mBall.isCollided())
	{
		if (mBall.isScores(Ball::Scores::PLAYER))
		{
			mPlayerScore.increaseScore();
			mPlayerScore.init(mGameWindowRenderer);
		}
		else if (mBall.isScores(Ball::Scores::COMPUTER))
		{
			mComputerScore.increaseScore();
			mComputerScore.init(mGameWindowRenderer);
		}

		stateReset();
	}

	SDL_Delay(delayTime);
}

void Game::draw()
{
	SDL_RenderClear(mGameWindowRenderer);

	mLine.draw(mGameWindowRenderer);
	mLeftPaddle.draw(mGameWindowRenderer);
	mRightPaddle.draw(mGameWindowRenderer);
	mBall.draw(mGameWindowRenderer);
	mPlayerScore.draw(mGameWindowRenderer);
	mComputerScore.draw(mGameWindowRenderer);

	SDL_RenderPresent(mGameWindowRenderer);
}

void Game::onKeyDown(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym)
	{
	case SDLK_w:
		mLeftPaddle.setDirection(Paddle::Direction::UP);
		break;
	case SDLK_s:
		mLeftPaddle.setDirection(Paddle::Direction::DOWN);
		break;
	}
}

void Game::onKeyUp(SDL_KeyboardEvent& event)
{
	switch (event.keysym.sym)
	{
	case SDLK_w:
		if (mLeftPaddle.isMoving(Paddle::Direction::UP))
		{
			mLeftPaddle.setDirection(Paddle::Direction::NONE);
		}
		break;
	case SDLK_s:
		if (mLeftPaddle.isMoving(Paddle::Direction::DOWN))
		{
			mLeftPaddle.setDirection(Paddle::Direction::NONE);
		}
		break;
	}
}

void Game::stateReset()
{
	const auto& ballAabb = mBall.getAabb();
	mBall.setPosX(mHafBox[0] - ballAabb.getExtentX());
	mBall.setPosY(mHafBox[1] - ballAabb.getExtentY());

	mBall.collisionReset();
	int random = rand() % 4;
	switch (random) {
	case 0: mBall.setDirection({ 0.5f,  0.5f }); break;
	case 1: mBall.setDirection({ 0.5f, -0.5f }); break;
	case 2: mBall.setDirection({ -0.5f,  0.5f }); break;
	case 3: mBall.setDirection({ -0.5f, -0.5f }); break;
	}

	const auto& paddleAabb = mLeftPaddle.getAabb();
	mLeftPaddle.setPosY(mHafBox[1] - paddleAabb.getExtentY());
	mRightPaddle.setPosY(mHafBox[1] - paddleAabb.getExtentY());

}

