#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include <wx/wx.h>

class Tetris;
class IniWindow;

class Board : public wxPanel
{
public:
	Board(wxWindow *window, wxSize panelSize, wxFrame *parent);
	void Start();
	void Pause();
	void linesRemovedChanged(int numLines);

	void SetSkill(int character);

	Tetris *parent;

protected:
	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxCommandEvent& event);

private:
	enum { BoardWidth = 10, BoardHeight = 22 };

	Blocks & ShapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }

	int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
	int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
	void ClearBoard();
	void HardDrop();
	void OneLineDown();
	void PieceDropped();
	void RemoveFullLines();
	void NewPiece();
	bool TryMove(const Shape& newPiece, int newX, int newY);
	void DrawSquare(wxPaintDC &dc, int x, int y, Blocks shape);
	void ActivateSkill(int skill);
	int skill;
	wxTimer *timer;
	bool isStarted;
	bool isPaused;
	bool isFallingFinished;
	bool isHold;

	bool extraLine;
	bool extraShape;

	bool rotate;

	Shape curPiece;
	Shape holdPiece;
	int curX;
	int curY;
	int gameTime;
	int nextLevel;
	int numLinesRemoved;
	int counter;
	int nextSkill;
	Blocks board[BoardWidth * BoardHeight];
	wxStatusBar *m_stsbar;

	wxBitmap* gameBackGround = nullptr;
	void LoadGameBG();

	IniWindow* pWindow;
};

#endif
