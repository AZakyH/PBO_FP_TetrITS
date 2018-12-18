#pragma once
#include "Board.h"
#include "HamtaLegend.h"

class Hamtaro : public Board
{
public:
	Hamtaro(wxWindow *window, wxSize panelSize, wxFrame *parent);
	~Hamtaro();

	virtual void ActivateSkill();
	virtual void LoadGameBG();
};

