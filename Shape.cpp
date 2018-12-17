#include <stdlib.h>
#include <algorithm>
#include "Shape.h"

using namespace std;

void Shape::SetShape(Blocks shape)
{
	static const int coordsTable[9][4][2] = {
		{ { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
		{ { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
		{ { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
		{ { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
		{ { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
		{ { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
		{ { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
		{ { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } },
		{ { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } }
	};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; ++j)
			coords[i][j] = coordsTable[shape][i][j];
	}
	pieceShape = shape;
}


void Shape::SetRandomShape()
{
	int x = rand() % 7 + 1;
	SetShape(Blocks(x));
}

int Shape::MinX() const
{
	int m = coords[0][0];
	for (int i = 0; i < 4; i++) {
		m = min(m, coords[i][0]);
	}
	return m;
}

int Shape::MaxX() const
{
	int m = coords[0][0];
	for (int i = 0; i < 4; i++) {
		m = max(m, coords[i][0]);
	}
	return m;
}

int Shape::MinY() const
{
	int m = coords[0][1];
	for (int i = 0; i < 4; i++) {
		m = min(m, coords[i][1]);
	}
	return m;
}

int Shape::MaxY() const
{
	int m = coords[0][1];
	for (int i = 0; i < 4; i++) {
		m = max(m, coords[i][1]);
	}
	return m;
}

Shape Shape::RotateLeft() const
{
	if (pieceShape == SquareShape)
		return *this;

	Shape result;
	result.pieceShape = pieceShape;
	for (int i = 0; i < 4; ++i) {
		result.SetX(i, y(i));
		result.SetY(i, -x(i));
	}
	return result;
}

Shape Shape::RotateRight() const
{
	if (pieceShape == SquareShape)
		return *this;

	Shape result;
	result.pieceShape = pieceShape;
	for (int i = 0; i < 4; ++i) {
		result.SetX(i, -y(i));
		result.SetY(i, x(i));
	}
	return result;
}
