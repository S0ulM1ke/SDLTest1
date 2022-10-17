#pragma once

#include <SDL.h>
#include <array>

#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "AI.h"
#include "Score.h"
#include "Line.h"

class Game
{
public:
	Game();
	~Game();

	void gameLoop();
	void update(int delayTime);
	void draw();
	void onKeyDown(SDL_KeyboardEvent& event);
	void onKeyUp(SDL_KeyboardEvent& event);
	void stateReset();

	const Wall& getTopWall() const { return mTopWall; }
	Wall& getTopWall() { return mTopWall; }

	const Wall& getBottomWall() const { return mBottomWall; }
	Wall& getBottomWall() { return mBottomWall; }


private:
	static const std::array<int, 2> kResolution;
	static const std::array<int, 2> kBox;
	static const std::array<float, 2> kBallDir;
	static const int kWhite;
	static const int kLineSize;
	static const int kPaddleIndent;
	static const int kBallIndent;
	
	SDL_Window* mGameWindow;
	SDL_Renderer* mGameWindowRenderer;

	Wall mTopWall;
	Wall mBottomWall;
	Wall mLeftWall;
	Wall mRightWall;
	Line mLine;
	Ball mBall;
	Paddle mLeftPaddle;
	Paddle mRightPaddle;
	Score mPlayerScore;
	Score mComputerScore;
	std::array<int, 2> mResolution;
	std::array<int, 2> mBox;
	std::array<int, 2> mHafBox;
	AI mAi;
};

