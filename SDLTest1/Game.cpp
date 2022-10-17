#include "Game.h"

#include <SDL_timer.h>

const std::array<int, 2> Game::kResolution = { 680, 480 };
const std::array<int, 2> Game::kBox = { 600, 400 };
const std::array<float, 2> Game::kBallDir = { 0.5f, -0.5f};
const int Game::kWhite = 255;
const int Game::kLineSize = 10;
const int Game::kPaddleIndent = 50;
const int Game::kBallIndent = 12;


Game::Game()
	: mResolution({ kResolution[0], kResolution[1] }), mBox({ kBox[0], kBox[1] }), mAi(mRightPaddle)
{
	// Rsolution - именяемый размер экрана
	// Box - игровое поле, подстраивается под разрешение не изменяя соотношение

	SDL_CreateWindowAndRenderer(mResolution[0], mResolution[1], SDL_WINDOW_RESIZABLE, &mGameWindow, &mGameWindowRenderer);
	SDL_RenderSetLogicalSize(mGameWindowRenderer, mBox[0], mBox[1]);

	mHafBox = { mBox[0] / 2, mBox[1] / 2 };
	mLine = {mHafBox[0] - kLineSize/2, kLineSize/2, kLineSize, mBox[1], kWhite};
	mLeftPaddle = { 0, mHafBox[1] - kPaddleIndent , Paddle::Type::PLAYER, kWhite};
	mRightPaddle = { mBox[0] - kPaddleIndent / 2, mHafBox[1] - kPaddleIndent , Paddle::Type::COMPUTER, kWhite};
	mTopWall = { 0, 0, mBox[0], 0 };
	mBottomWall = { 0, mBox[1], mBox[0], 0 };
	mLeftWall = { 0, 0, 0 , mBox[1] };
	mRightWall = { mBox[0], 0 , 0, mBox[1] };
	mBall = { mHafBox[0] - kBallIndent, mHafBox[1] - kBallIndent , kBallDir[1], kBallDir[0]};
	mPlayerScore = { mHafBox[0] / 2 , 0, kWhite};
	mComputerScore = {static_cast<int>(mHafBox[0] * 1.5), 0, kWhite};

	// Инициализация текстур шара и текущих очков
	mBall.init(mGameWindowRenderer);
	mPlayerScore.init(mGameWindowRenderer);
	mComputerScore.init(mGameWindowRenderer);
}

Game::~Game()
{
	SDL_DestroyWindow(mGameWindow);
	SDL_DestroyRenderer(mGameWindowRenderer);
	SDL_Quit();
}

void Game::gameLoop()
{
	// Цикл игры

	bool keep_running = true;
	while (keep_running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				keep_running = false;
				break;
			case SDL_KEYDOWN:
				onKeyDown(e.key);
				break;
			case SDL_KEYUP:
				onKeyUp(e.key);
				break;
			}
		}

		update(8); // Управление общей скоростью игры
		draw();
	}
}

void Game::update(int delayTime)
{
	// Вызывает методы для перемещения элементов по экрану и их взамиодействия

	mLeftPaddle.update(mTopWall, mBottomWall);
	mRightPaddle.update(mTopWall, mBottomWall);
	mBall.update(mTopWall, mBottomWall, mLeftPaddle, mRightPaddle, mLeftWall, mRightWall);
	mAi.update(mBall, mRightPaddle);
	mRightPaddle.setDirection(mAi.getAiDir());
	if (mBall.isCollided())
	{
		// В случае столкновения мяча со стенкой начисляем соответсвующему игроку очко и перерисовываем это значение

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

		// Делаем сброс уровня

		stateReset();
	}

	SDL_Delay(delayTime);
}

void Game::draw()
{
	// Отрисовка

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
	// Премещение ракетки на нажаую клавишу

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
	// Если клавиша отпущена - остановить ракетку

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
	// Сброс уровня

	const auto& ballAabb = mBall.getAabb();
	mBall.setPosX(mHafBox[0] - ballAabb.getExtentX());
	mBall.setPosY(mHafBox[1] - ballAabb.getExtentY());

	mBall.collisionReset();
	int random = rand() % 4;
	switch (random) {
	case 0: mBall.setDirection({ kBallDir[0],  kBallDir[0] }); break;
	case 1: mBall.setDirection({ kBallDir[0], kBallDir[1] }); break;
	case 2: mBall.setDirection({ kBallDir[1],  kBallDir[0] }); break;
	case 3: mBall.setDirection({ kBallDir[1], kBallDir[1] }); break;
	}

	mBall.setVelocity(mBall.kVelocity);

	const auto& paddleAabb = mLeftPaddle.getAabb();
	mLeftPaddle.setPosY(mHafBox[1] - paddleAabb.getExtentY());
	mRightPaddle.setPosY(mHafBox[1] - paddleAabb.getExtentY());

}