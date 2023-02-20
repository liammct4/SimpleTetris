#include <chrono>
#include "Utilities.h"

SDL_Texture* DrawGradient(SDL_Renderer* renderer, SDL_Colour* colour, int w, int h, double dimnessFactor, int noiseDeviance)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
	Uint32* pixels = (Uint32*)surface->pixels;

	for (int i = 0; i < h; i += 1) {
		double fac = 1 - ((static_cast<double>(i) / h) * dimnessFactor);

		for (int j = 0; j < w; j++) {
			double r = fac * colour->r + (rand() % (noiseDeviance * 2)) - noiseDeviance;
			double g = fac * colour->g + (rand() % (noiseDeviance * 2)) - noiseDeviance;
			double b = fac * colour->b + (rand() % (noiseDeviance * 2)) - noiseDeviance;

			pixels[(i * surface->w) + j] = SDL_MapRGB(surface->format, r, g, b);;
		}
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

long long GetTimeInMilliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int ResolveToRange(int value, int start, int end)
{
	if (value > end)
	{
		return end;
	}
	else if (value < start)
	{
		return start;
	}
	else
	{
		return value;
	}
}

bool IsInbetween(int value, int start, int end)
{
	return value >= start && value < end;
}