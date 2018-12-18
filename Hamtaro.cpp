#include "Hamtaro.h"

Hamtaro::Hamtaro(wxWindow *window, wxSize panelSize, wxFrame *parent)
	: Board(window, panelSize, parent)
{
	legend = new HamtaLegend(window, wxSize(410, 902), parent, this);
	legend->SetPosition(wxPoint(411,0));
	legend->Show(true);
}

Hamtaro::~Hamtaro()
{
	delete legend;
}

void Hamtaro::ActivateSkill()
{
	for (int k = 0; k < BoardHeight - 4; ++k) {
		for (int j = 0; j < BoardWidth; ++j)
			ShapeAt(j, k) = ShapeAt(j, k + 4);
	}
}

void Hamtaro::LoadGameBG()
{
	wxImage gameBGImage(wxT("HamtaroBG.jpg"), wxBITMAP_TYPE_JPEG);
	gameBackGround = new wxBitmap(gameBGImage);
}