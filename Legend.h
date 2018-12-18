#pragma once
#include "wx\wx.h"

class Board;
class Tetris;
class IniWindow;

class Legend : public wxPanel
{
public:
	Legend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board);
	~Legend();

	void OnPaint(wxPaintEvent &event);
private:
	Board* papan;
	wxBitmap *legendBG;

	DECLARE_EVENT_TABLE()
	void LoadLegendBG();
};

