#include <map>
#include <vector>
#include "Piece.h"
#include "Source.h"
#include "Utilities.h"
#include "PieceType.h"
#include "RectangleI.h"

bool Piece::Move(int x, int y)
{
	// TODO: Add collision checking.
	for (auto it = tiles->begin(); it < tiles->end(); it++)
	{
		GameTile* tile = *it;

		if (!IsInbetween(tile->x + x, 0, GAME_WIDTH) || !IsInbetween(tile->y + y, 0, GAME_HEIGHT))
		{
			return false;
		}
	}

	for (auto it = tiles->begin(); it < tiles->end(); it++)
	{
		GameTile* tile = *it;

		tile->x += x;
		tile->y += y;
	}

	return true;
}

RectangleI Piece::GetDimensions()
{
	int minX = INT_MAX, minY = INT_MAX;
	int maxX = 0, maxY = 0;

	for (auto it = tiles->begin(); it < tiles->end(); it++)
	{
		minX = std::min((*it)->x, minX);
		minY = std::min((*it)->y, minY);

		maxX = std::max((*it)->x, maxX);
		maxY = std::max((*it)->y, maxY);
	}

	return { minX, minY, maxX - minX, maxY - minY };
}

Piece* Piece::GetPiece(PieceType pieceType, int x, int y)
{
	std::vector<GameTile*>* tiles = new std::vector<GameTile*>();

	switch (pieceType)
	{
		case BoxPiece:
			tiles->push_back(new GameTile{ 0, 0 });
			tiles->push_back(new GameTile{ 1, 0 });
			tiles->push_back(new GameTile{ 0, 1 });
			tiles->push_back(new GameTile{ 1, 1 });
			break;
		case LinePiece:
			tiles->push_back(new GameTile{ 0, 0 });
			tiles->push_back(new GameTile{ 0, 1 });
			tiles->push_back(new GameTile{ 0, 2 });
			tiles->push_back(new GameTile{ 0, 3 });
			break;
		case ZPiece:
			tiles->push_back(new GameTile{ 0, 0 });
			tiles->push_back(new GameTile{ 1, 0 });
			tiles->push_back(new GameTile{ 1, 1 });
			tiles->push_back(new GameTile{ 2, 1 });
			break;
		case SPiece:
			tiles->push_back(new GameTile{ 0, 1 });
			tiles->push_back(new GameTile{ 1, 1 });
			tiles->push_back(new GameTile{ 1, 0 });
			tiles->push_back(new GameTile{ 2, 0 });
			break;
		case TPiece:
			tiles->push_back(new GameTile{ 0, 1 });
			tiles->push_back(new GameTile{ 1, 1 });
			tiles->push_back(new GameTile{ 2, 1 });
			tiles->push_back(new GameTile{ 1, 0 });
			break;
		case LeftLPiece:
			tiles->push_back(new GameTile{ 0, 0 });
			tiles->push_back(new GameTile{ 0, 1 });
			tiles->push_back(new GameTile{ 0, 2 });
			tiles->push_back(new GameTile{ 1, 2 });
			break;
		case RightLPiece:
			tiles->push_back(new GameTile{ 1, 0 });
			tiles->push_back(new GameTile{ 1, 1 });
			tiles->push_back(new GameTile{ 1, 2 });
			tiles->push_back(new GameTile{ 0, 2 });
			break;
	}

	for (auto it = tiles->begin(); it < tiles->end(); it++)
	{
		GameTile* tile = *it;

		tile->x += x;
		tile->y += y;
	}

	return new Piece(tiles);
}
