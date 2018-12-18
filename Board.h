#ifndef BOARD_H
#define BOARD_H

#include "Shape.h"
#include <wx/wx.h>

class Tetris;
class Legend;
class IniWindow;

class Board : public wxPanel
{
public:
	Board(wxWindow *window, wxSize panelSize, wxFrame *parent);
	void Start();
	void Pause();
	void linesRemovedChanged(int numLines);

	void SetSkill(int character);
	int skill;

	Tetris *parent;
	Legend* legend = nullptr;
	
	void DrawSquare(wxPaintDC &dc, int x, int y, Blocks shape);
	Blocks & ShapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
	Shape holdPiece;

protected:
	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxCommandEvent& event);
	enum { BoardWidth = 10, BoardHeight = 22 };
	wxBitmap* gameBackGround = nullptr;
	virtual void LoadGameBG() = 0;
	
	int counter;
	bool extraLine;
	bool extraShape;

private:
	int SquareWidth() { return GetClientSize().GetWidth() / BoardWidth; }
	int SquareHeight() { return GetClientSize().GetHeight() / BoardHeight; }
	void ClearBoard();
	void HardDrop();
	void OneLineDown();
	void PieceDropped();
	void RemoveFullLines();
	void NewPiece();
	bool TryMove(const Shape& newPiece, int newX, int newY);
	virtual void ActivateSkill() = 0;
	int GhostFunction();
	wxTimer *timer;
	bool isStarted;
	bool isPaused;
	bool isFallingFinished;
	bool isHold;

	bool rotate;

	Shape curPiece;

	int curX;
	int curY;
	int gameTime;
	int nextLevel;
	int numLinesRemoved;
	int nextSkill;
	Blocks board[BoardWidth * BoardHeight];
	wxStatusBar *m_stsbar;


	IniWindow* pWindow;
};

#endif
