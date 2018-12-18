#include "PikaLegend.h"
#include "Board.h"

BEGIN_EVENT_TABLE(PikaLegend, Legend)
EVT_PAINT(PikaLegend::OnPaint)
END_EVENT_TABLE()

PikaLegend::PikaLegend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board)
	: Legend(window, panelSize, parent, board)
{
	papan = board;
	LoadLegendBG();
}

PikaLegend::~PikaLegend()
{
}

void PikaLegend::LoadLegendBG()
{
	wxImage legendBGImage(wxT("Pika_Exp.jpg"), wxBITMAP_TYPE_JPEG);
	legendBG = new wxBitmap(legendBGImage);
}

void PikaLegend::OnPaint(wxPaintEvent &event)
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