#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "Legend.h"
#include "IniWindow.h"

BEGIN_EVENT_TABLE(Legend, wxPanel)
	EVT_PAINT(Legend::OnPaint)
END_EVENT_TABLE()

Legend::Legend(wxWindow *window, wxSize panelSize, wxFrame *parent, Board *board) :
	wxPanel(window, wxID_ANY, wxPoint(820, 0), panelSize, wxBORDER_NONE)
{
	wxMessageOutputDebug().Printf("Masuk ke Legend");
	papan = board;

	LoadLegendBG();
}

Legend::~Legend()
{
	delete legendBG;
}

void Legend::LoadLegendBG()
{
	if (papan->skill == 0)
	{
		wxImage legendBGImage(wxT("Eli_Exp.jpg"), wxBITMAP_TYPE_JPEG);
		legendBG = new wxBitmap(legendBGImage);
	}
	else if (papan->skill == 1)
	{
		wxImage legendBGImage(wxT("Pika_Exp.jpg"), wxBITMAP_TYPE_JPEG);
		legendBG = new wxBitmap(legendBGImage);
	}
	else
	{
		wxImage legendBGImage(wxT("Hamta_Exp.jpg"), wxBITMAP_TYPE_JPEG);
		legendBG = new wxBitmap(legendBGImage);
	}
	
}

void Legend::OnPaint(wxPaintEvent &event)
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
			papan->DrawSquare(legendDC, 180+x*41,
				700+y*41,
				papan->holdPiece.GetShape());
		}
	}
	//papan->DrawSquare(legendDC, 180, 630, papan->holdPiece.GetShape());
}