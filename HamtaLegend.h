#pragma once
#include "Legend.h"


class HamtaLegend : public Legend
{
public:
	HamtaLegend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board);
	~HamtaLegend();

	Board* papan;

	virtual void LoadLegendBG();
	void OnPaint(wxPaintEvent &event);
	DECLARE_EVENT_TABLE()
};

