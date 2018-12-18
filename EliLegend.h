#pragma once
#include "Legend.h"


class EliLegend : public Legend
{
public:
	EliLegend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board);
	~EliLegend();

	Board* papan;

	virtual void LoadLegendBG();
	void OnPaint(wxPaintEvent &event);
	DECLARE_EVENT_TABLE()
};

