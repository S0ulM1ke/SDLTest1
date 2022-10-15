#include "Paddle.h"


Paddle::Paddle(int x, int y, Type type)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.w = 25;
	mPosition.h = 75;
	mType = type;
	mDirection = Direction::NONE;

	auto halfWidth = (mPosition.w / 2);
	auto halfHeight = (mPosition.h / 2);

	mAabb.setCenterX(x + halfWidth);
	mAabb.setCenterY(y + halfHeight);
	mAabb.setExtentX(halfWidth);
	mAabb.setExtentY(halfHeight);

}


void Paddle::update(const Wall& topWall, const Wall& bottomWall)
{
	// Скорость в зависимости от типа ракетки (ракетка игрока или компьютера)

	switch (mType)
	{
	case Paddle::Type::PLAYER:
		mVelocity = 3;
		break;
	case Paddle::Type::COMPUTER:
		mVelocity = 2;
		break;
	}


	if (mDirection != Direction::NONE)
	{
		auto movement = (int)mDirection * mVelocity;
		mPosition.y += movement;
		mAabb.setCenterY(mAabb.getCenterY() + movement);
		if (mDirection == Direction::UP)
		{
			// Проверка столкновения с верхней стенкой

			const auto& wallAabb = topWall.getAabb();
			if (mAabb.collides(wallAabb))
			{
				mPosition.y = wallAabb.getCenterY();
				mPosition.y += wallAabb.getExtentY();

				mAabb.setCenterY(mPosition.y + mAabb.getExtentY());

				mDirection = Direction::NONE;
			}
		}
		else
		{
			// Проверка столкновения с нижней стенкой

			const auto& wallAabb = bottomWall.getAabb();
			if (mAabb.collides(wallAabb))
			{
				mPosition.y = wallAabb.getCenterY();
				mPosition.y -= wallAabb.getExtentY();
				mPosition.y -= mPosition.h;

				mAabb.setCenterY(mPosition.y + mAabb.getExtentY());

				mDirection = Direction::NONE;
			}
		}
	}

}

void Paddle::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &mPosition);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}


