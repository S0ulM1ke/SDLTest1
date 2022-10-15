#include "Ball.h"

const float Ball::VELOCITY = 4.0f;

Ball::Ball(int x, int y) : 	mVelocity(VELOCITY), mDirection({ -0.5f, 0.5f })
{
	mPosition = { x, y };
	mVelocity = VELOCITY;

	mScores = Scores::DEFAULT;
}

Ball::~Ball()
{
	SDL_DestroyTexture(mImage);
}

void Ball::init(SDL_Renderer* renderer)
{
	IMG_Init(IMG_INIT_PNG);

	//  Используем изображение в качестве текстуры шара

	SDL_Surface* image = IMG_Load("ball.png");

	mImage = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	IMG_Quit();

	SDL_QueryTexture(mImage, nullptr, nullptr, &mPosition.w, &mPosition.h);

	mAabb.setCenterX(mPosition.x + mPosition.w / 2);
	mAabb.setCenterY(mPosition.y + mPosition.h / 2);
	mAabb.setExtentX(mPosition.w / 2);
	mAabb.setExtentY(mPosition.h / 2);
}

void Ball::update(const Wall& topWall, const Wall& bottomWall, const Paddle& leftPaddle, const Paddle& rightPaddle, const Wall& lefttWall, const Wall& rightWall)
{

	auto movement = std::array<int, 2>();
	movement[0] = static_cast<int>(mDirection[0] * mVelocity);
	movement[1] = static_cast<int>(mDirection[1] * mVelocity);

	mPosition.x += movement[0];
	mPosition.y += movement[1];

	mAabb.setCenterX(mAabb.getCenterX() + movement[0]);
	mAabb.setCenterY(mAabb.getCenterY() + movement[1]);

	const auto& topWallAabb = topWall.getAabb();
	const auto& bottomWallAabb = bottomWall.getAabb();
	const auto& leftPaddleAabb = leftPaddle.getAabb();
	const auto& rightPaddleAabb = rightPaddle.getAabb();
	const auto& leftWallAabb = lefttWall.getAabb();
	const auto& rightWallAabb = rightWall.getAabb();

	if (mAabb.collides(bottomWallAabb))
	{
		// Проверка столкновения с нижней стенкой

		mPosition.y = bottomWallAabb.getCenterY();
		mPosition.y -= bottomWallAabb.getExtentY();
		mPosition.y -= mPosition.h;

		mAabb.setCenterX(mPosition.x + mAabb.getExtentX());
		mAabb.setCenterY(mPosition.y + mAabb.getExtentY());

		mDirection[1] = -mDirection[1];
	}
	else if (mAabb.collides(topWallAabb))
	{
		// Проверка столкновения с верхней стенкой

		mPosition.y = topWallAabb.getCenterY();
		mPosition.y += topWallAabb.getExtentY();

		mAabb.setCenterX(mPosition.x + mAabb.getExtentX());
		mAabb.setCenterY(mPosition.y + mAabb.getExtentY());

		mDirection[1] = -mDirection[1];
	}
	else if (mAabb.collides(leftPaddleAabb))
	{
		// Проверка столкновения с левой ракеткой

		mPosition.x = leftPaddleAabb.getCenterX();
		mPosition.x += leftPaddleAabb.getExtentX();

		mAabb.setCenterX(mPosition.x + mAabb.getExtentX());
		mAabb.setCenterY(mPosition.y + mAabb.getExtentY());

		mDirection[0] = -mDirection[0];

		// Увеличиваем скорость мяча
		mVelocity += 1.0f;
	}
	else if (mAabb.collides(rightPaddleAabb))
	{
		// Проверка столкновения с правой ракеткой

		mPosition.x = rightPaddleAabb.getCenterX();
		mPosition.x -= rightPaddleAabb.getExtentX();
		mPosition.x -= mPosition.w;

		mAabb.setCenterX(mPosition.x + mAabb.getExtentX());
		mAabb.setCenterY(mPosition.y + mAabb.getExtentY());

		mDirection[0] = -mDirection[0];

		mVelocity += 1.0f;
	}
	else if (mAabb.collides(leftWallAabb))
	{
		// Проверка столкновения с левой стенкой
		// Начисляем компьютеру очко если было столкновение

		mWallCollided = true;
		mScores = Scores::COMPUTER;
	}
	else if (mAabb.collides(rightWallAabb))
	{
		// Проверка столкновения с правой стенкой
		// Начисляем игроку очко если было столкновение

		mWallCollided = true;
		mScores = Scores::PLAYER;
	}

}

void Ball::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, mImage, nullptr, &mPosition);
}
