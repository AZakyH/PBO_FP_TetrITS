#include "Elizabeth.h"

Elizabeth::Elizabeth(wxWindow *window, wxSize panelSize, wxFrame *parent)
	: Board(window, panelSize, parent)
{
	legend = new EliLegend(window, wxSize(410, 902), parent, this);
	legend->SetPosition(wxPoint(411, 0));
	legend->Show(true);
}

Elizabeth::~Elizabeth()
{
	delete legend;
}

void Elizabeth::ActivateSkill()
{
	counter = 10;
	extraShape = true;
}

void Elizabeth::LoadGameBG()
{
	wxImage gameBGImage(wxT("ElizabethBG.jpg"), wxBITMAP_TYPE_JPEG);
	gameBackGround = new wxBitmap(gameBGImage);
}