#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

bool init()
{
	auto flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS;
	auto imageFlags = IMG_INIT_PNG;
	int result = SDL_Init(flags);

	if (result != 0) {
		printf("SDL Init Error (%i): %s\n", result, SDL_GetError());

		return false;
	}

	if (TTF_Init() == -1) {
		printf("SDL TTF Init Error: %s\n", TTF_GetError());

		return false;
	}

	if (IMG_Init(imageFlags) != imageFlags) {
		printf("SDL Image Init Error: %s\n", IMG_GetError());

		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (!init()) {
		std::cout << "Error, cannot run application." << std::endl;
		std::cin.get();
	}

	return 0;
}