#include <iostream>
#include <chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Source.h"
#include "Utilities.h"
#include "GameTile.h"
#include "Piece.h"

SDL_Texture* backTexture;
SDL_Texture* tileTexture;
SDL_Rect* gameArea;
SDL_Rect* nextPieceArea;
SDL_Rect* scoreArea;
std::vector<GameTile*>* gameTiles;
Piece* currentPiece;

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

void RenderTile(SDL_Renderer* renderer, GameTile* tile)
{
	int x = gameArea->x + (tile->x * TILE_SIZE);
	int y = gameArea->y + (tile->y * TILE_SIZE);

	// TODO: Add multiple colours specific to each tile.
	SDL_Rect* rect = new SDL_Rect({ x, y, TILE_SIZE, TILE_SIZE });
	SDL_RenderCopy(renderer, tileTexture, NULL, rect);
}


void Render(SDL_Renderer* renderer, SDL_Rect* screen)
{
	// Draw background.
	SDL_RenderCopy(renderer, backTexture, NULL, screen);

	// Draw UI.
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 100);

	SDL_RenderFillRect(renderer, gameArea);
	SDL_RenderFillRect(renderer, nextPieceArea);
	SDL_RenderFillRect(renderer, scoreArea);

	// Draw each tile.
	for (auto it = gameTiles->begin(); it < gameTiles->end(); it++)
	{
		RenderTile(renderer, *it);
	}

	for (auto it = currentPiece->tiles->begin(); it < currentPiece->tiles->end(); it++)
	{
		RenderTile(renderer, *it);
	}

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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	
	SDL_Rect* screen = new SDL_Rect({ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT });
	SDL_Colour baseColour{ 33, 33, 40, 255 };
	backTexture = DrawGradient(renderer, &baseColour, WINDOW_WIDTH, WINDOW_HEIGHT, 0.6, 2);

	// Load Assets.
	SDL_Surface* tileSurface = IMG_Load("Tile.png");
	tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);

	// UI Specifications.
	gameArea = new SDL_Rect({ 30, 30, TILE_SIZE * GAME_WIDTH, TILE_SIZE * GAME_HEIGHT });
	nextPieceArea = new SDL_Rect({ 310, 30, 160, 160 });
	scoreArea = new SDL_Rect({ 310, 220, 160, 50 });
	gameTiles = new std::vector<GameTile*>();

	bool isRunning = true;
	double nextMoveTime = GetTimeInMilliseconds();

	// Set placeholder
	currentPiece = Piece::GetPiece(BoxPiece, 2, 0);

	while (isRunning)
	{
		HandleEvents(&isRunning);

		Render(renderer, screen);

		// Basic timer for moving.
		auto currentTime = GetTimeInMilliseconds();

		if (currentTime >= nextMoveTime)
		{
			currentPiece->Move(0, 1);

			nextMoveTime = GetTimeInMilliseconds() + MOVE_INTERVAL;
		}
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}