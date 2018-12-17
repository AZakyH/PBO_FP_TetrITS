#ifndef SHAPE_H
#define SHAPE_H

enum Blocks {
	NoShape, ZShape, SShape, LineShape,
	TShape, SquareShape, LShape, MirroredLShape, ExtraShape
};

class Shape
{
public:
	Shape() { SetShape(NoShape); }
	void SetShape(Blocks shape);
	void SetRandomShape();

	Blocks GetShape() const { return pieceShape; }
	int x(int index) const { return coords[index][0]; }
	int y(int index) const { return coords[index][1]; }

	int MinX() const;
	int MaxX() const;
	int MinY() const;
	int MaxY() const;

	Shape RotateLeft() const;
	Shape RotateRight() const;

private:
	void SetX(int index, int x) { coords[index][0] = x; }
	void SetY(int index, int y) { coords[index][1] = y; }
	Blocks pieceShape;
	int coords[4][2];
};

#endif
