#include "Pikachu.h"

Pikachu::Pikachu(wxWindow *window, wxSize panelSize, wxFrame *parent)
	: Board(window, panelSize, parent)
{
	legend = new PikaLegend(window, wxSize(410, 902), parent, this);
	legend->SetPosition(wxPoint(411, 0));
	legend->Show(true);
}

Pikachu::~Pikachu()
{
	delete legend;
}

void Pikachu::ActivateSkill()
{
	counter = 3;
	extraLine = true;
}

void Pikachu::LoadGameBG()
{
	wxImage gameBGImage(wxT("PikachuBG.jpg"), wxBITMAP_TYPE_JPEG);
	gameBackGround = new wxBitmap(gameBGImage);
}