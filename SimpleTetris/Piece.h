#include <vector>
#include <map>
#include "GameTile.h"
#include "PieceType.h"
#include "RectangleI.h"
#pragma once

class Piece
{
private:
	int pieceX;
	int pieceY;
	int dimensionWidth;
	int dimensionHeight;

	Piece(std::vector<GameTile*>* tiles)
	{
		this->tiles = tiles;
	}

public:
	std::vector<GameTile*>* tiles;

	/// <summary>
	/// Moves this by by a certain amount horizontally and vertically.
	/// </summary>
	/// <param name="x">The number to move the piece horizontally by.</param>
	/// <param name="y">The number to move the piece vertically by.</param>
	/// <returns>True if the piece was moved successfuly, otherwise false (out of bounds or colliding with other tiles.)</returns>
	bool Move(int x, int y);

	/// <summary>
	/// Gets the dimensions of this piece in terms of position and width/height.
	/// </summary>
	/// <returns>The dimensions of this piece.</returns>
	RectangleI GetDimensions();

	/// <summary>
	/// Builds a new piece according to the piece type given.
	/// </summary>
	/// <param name="pieceType">The type of piece to build.</param>
	/// <param name="x">Where the new piece will be placed horizontally.</param>
	/// <param name="y">Where the new piece will be placed vertically.</param>
	/// <returns>A new piece.</returns>
	static Piece* GetPiece(PieceType pieceType, int x, int y);
};

