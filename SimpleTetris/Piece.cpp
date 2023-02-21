#include <map>
#include <vector>
#include "Piece.h"
#include "Source.h"
#include "Utilities.h"
#include "PieceType.h"
#include "RectangleI.h"

bool Piece::Move(std::vector<GameTile*>* gameTiles, int x, int y)
{
	// Check preemptively if the piece cannot fit into the new location.
	for (auto it = tiles->begin(); it < tiles->end(); it++)
	{
		GameTile* tile = *it;

		int newX = tile->x + x;
		int newY = tile->y + y;

		// Check if out of bounds.
		if (!IsInbetween(newX, 0, GAME_WIDTH) || !IsInbetween(newY, 0, GAME_HEIGHT))
		{
			return false;
		}

		// Check if colliding with existing tiles.
		for (auto it2 = gameTiles->begin(); it2 < gameTiles->end(); it2++)
		{
			if ((*it2)->x == newX && (*it2)->y == newY)
			{
				return false;
			}
		}
	}

	// Apply the changes after it is safe to move.
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

void Piece::CopyTiles(std::vector<GameTile*>* sourceTiles)
{
	for (auto it = tiles->begin(); it < tiles->end(); it++)
	{
		sourceTiles->push_back(*it);
	}
}

PieceType Piece::GetRandomPieceType()
{
	return PieceType(rand() % 7);
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
