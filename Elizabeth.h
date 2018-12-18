#pragma once
#include "Board.h"
#include "EliLegend.h"

class Elizabeth : public Board
{
public:
	Elizabeth(wxWindow *window, wxSize panelSize, wxFrame *parent);
	~Elizabeth();

	virtual void ActivateSkill();
	virtual void LoadGameBG();
};

