#include "EliLegend.h"
#include "Board.h"

BEGIN_EVENT_TABLE(EliLegend, Legend)
EVT_PAINT(EliLegend::OnPaint)
END_EVENT_TABLE()

EliLegend::EliLegend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board)
	: Legend(window, panelSize, parent, board)
{
	papan = board;
	LoadLegendBG();
}

EliLegend::~EliLegend()
{
	//delete legendBG;
}

void EliLegend::LoadLegendBG()
{
	wxImage legendBGImage(wxT("Eli_Exp.jpg"), wxBITMAP_TYPE_JPEG);
	legendBG = new wxBitmap(legendBGImage);
}

void EliLegend::OnPaint(wxPaintEvent &event)
{
	wxPaintDC legendDC(this);
	if (legendBG != nullptr)
	{
		legendDC.DrawBitmap(*legendBG, wxPoint(0, 0), true);
	}

	if (papan->holdPiece.GetShape() != NoShape) {
		for (int i = 0; i < 4; ++i) {
			int x = 0 + papan->holdPiece.x(i);
			int y = 0 - papan->holdPiece.y(i);
			papan->DrawSquare(legendDC, 180 + x * 41,
				700 + y * 41,
				papan->holdPiece.GetShape());
		}
	}
}