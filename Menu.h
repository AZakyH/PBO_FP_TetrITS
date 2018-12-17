#pragma once
#include "wx\wx.h"

class Tetris;
class IniWindow;

class Menu : public wxPanel
{
public:
	Menu(wxWindow *window, wxSize panelSize, wxFrame *parent);
	~Menu();
	
	void OnPaint(wxPaintEvent &event);
	void SinglePButton(wxCommandEvent& event);
	void TwoPButton(wxCommandEvent& event);

private:
	Tetris *parentFrame;
	IniWindow *pWindow;
	wxBitmap *menuBG = nullptr;
	wxBitmap *onePButton = nullptr; 
	wxBitmap *twoPButton = nullptr; 
	DECLARE_EVENT_TABLE()
	void LoadMenuBG();
	void LoadButtons();
};

