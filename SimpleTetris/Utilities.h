#include <SDL.h>
#include <vector>

/// <summary>
/// Draws a gradient with noise from the colour provided to black depending on the dimnessFactor.
/// </summary>
/// <param name="renderer">The renderer to create the texture from.</param>
/// <param name="colour">The base colour to draw.</param>
/// <param name="w">Width of the texture.</param>
/// <param name="h">Height of the texture.</param>
/// <param name="dimnessFactor">How much the gradient will dim.</param>
/// <param name="noiseDeviance">How much deviance in noise there is.</param>
/// <returns>A texture gradient.</returns>
SDL_Texture* DrawGradient(SDL_Renderer* renderer, SDL_Colour* colour, int w, int h, double dimnessFactor, int noiseDeviance);

/// <summary>
/// Gets the current time since epoch in milliseconds.
/// </summary>
/// <returns>The current time in milliseconds.</returns>
long long GetTimeInMilliseconds();

/// <summary>
/// Resolves a value between a range.
/// </summary>
/// <param name="value">The value to resolve.</param>
/// <param name="start">The minimum allowed.</param>
/// <param name="end">The maximum allowed.</param>
/// <returns>Returns a value between a range.</returns>
int ResolveToRange(int value, int start, int end);