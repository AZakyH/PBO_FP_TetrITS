#pragma once
#include "wx\wx.h"

class Tetris;
class IniWindow;

class Character : public wxPanel
{
public:
	Character(wxWindow *window, wxSize panelSize, wxFrame *parent);
	~Character();

	void OnPaint(wxPaintEvent &event);
	void ElizabethButton(wxCommandEvent& event);
	void PikachuButton(wxCommandEvent& event);
	void HamtaroButton(wxCommandEvent& event);

private:
	IniWindow *pWindow;
	wxBitmap *charmenuBG = nullptr;
	wxBitmap *elizabethB = nullptr;
	wxBitmap *pikachuB = nullptr;
	wxBitmap *hamtaroB = nullptr;

	DECLARE_EVENT_TABLE()
	void LoadCharMenuBG();
	void LoadCharButtons();
};

