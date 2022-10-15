#include "Score.h"
#include <iostream>
#include <string>

Score::Score(int x, int y)
{
	mPosition = { x , y };
}

Score::~Score()
{
	SDL_DestroyTexture(mText);
}

void Score::increaseScore()
{
	SDL_DestroyTexture(mText);
	mValue++;
}

void Score::init(SDL_Renderer* renderer)
{
	TTF_Init();

	// Создание текстуры из текста - значение очков

	mFont = TTF_OpenFont("arial.ttf", 25);

	std::string displayedValue = std::to_string(mValue);

	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* scoreValue = TTF_RenderText_Solid(mFont, displayedValue.c_str(), color);

	mText = SDL_CreateTextureFromSurface(renderer, scoreValue);
	SDL_FreeSurface(scoreValue);
	TTF_CloseFont(mFont);

	TTF_Quit();


	SDL_QueryTexture(mText, nullptr, nullptr, &mPosition.w, &mPosition.h);

}

void Score::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, mText, nullptr, &mPosition);
}
