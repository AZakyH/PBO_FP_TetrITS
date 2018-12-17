#pragma once
#include "wx\wx.h"

class Tetris;
class IniWindow;

class GameOver : public wxPanel
{
public:
	GameOver(IniWindow *window, wxSize panelSize, wxFrame *parent);
	~GameOver();

	void OnPaint(wxPaintEvent &event);
	void MenuButton(wxCommandEvent& event);

private:
	Tetris *parentFrame;
	IniWindow *pWindow;
	wxBitmap *gameOverBG = nullptr;
	wxBitmap *menuButton = nullptr;
	DECLARE_EVENT_TABLE()
	void LoadGameOverBG();
	void LoadButtons();
};

