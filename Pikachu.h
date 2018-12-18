#pragma once
#include "Board.h"
#include "PikaLegend.h"

class Pikachu : public Board
{
public:
	Pikachu(wxWindow *window, wxSize panelSize, wxFrame *parent);
	~Pikachu();

	virtual void ActivateSkill();
	virtual void LoadGameBG();
};

