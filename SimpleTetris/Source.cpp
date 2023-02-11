#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Utilities.h"
#define WINDOW_WIDTH 502
#define WINDOW_HEIGHT 602

SDL_Texture* backTexture;

bool init()
{
	auto flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS;
	auto imageFlags = IMG_INIT_PNG;
	int result = SDL_Init(flags);

	if (result != 0)
	{
		printf("SDL Init Error (%i): %s\n", result, SDL_GetError());

		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL TTF Init Error: %s\n", TTF_GetError());

		return false;
	}

	if (IMG_Init(imageFlags) != imageFlags)
	{
		printf("SDL Image Init Error: %s\n", IMG_GetError());

		return false;
	}

	return true;
}

void HandleEvents(bool* isRunning)
{
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{
		case SDL_QUIT:
			*isRunning = false;
			break;
	}
}

void Render(SDL_Renderer* renderer, SDL_Rect* screen)
{
	// Draw background.
	SDL_RenderCopy(renderer, backTexture, NULL, screen);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
	// Initialize SDL2, SDL2_image, SDL2_ttf.
	if (!init())
	{
		std::cout << "Error, cannot run application." << std::endl;
		std::cin.get();
	}

	// Create Window.
	SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_Rect* screen = new SDL_Rect({ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT });
	SDL_Colour baseColour{ 33, 33, 40, 255 };
	backTexture = DrawGradient(renderer, &baseColour, WINDOW_WIDTH, WINDOW_HEIGHT, 0.6, 2);

	bool isRunning = true;

	while (isRunning)
	{
		HandleEvents(&isRunning);

		Render(renderer, screen);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}