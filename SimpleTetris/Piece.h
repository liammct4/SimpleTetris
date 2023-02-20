#include <vector>
#include <map>
#include "GameTile.h"
#include "PieceType.h"
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
	void Move(int x, int y);

	static Piece* GetPiece(PieceType pieceType, int x, int y);
};

