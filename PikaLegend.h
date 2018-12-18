#pragma once
#include "Legend.h"


class PikaLegend : public Legend
{
public:
	PikaLegend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board);
	~PikaLegend();

	Board* papan;

	virtual void LoadLegendBG();
	void OnPaint(wxPaintEvent &event);
	DECLARE_EVENT_TABLE()
};

