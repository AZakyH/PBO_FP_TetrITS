#include "Tetris.h"
#include "IniWindow.h"
#include "wx\icon.h"

Tetris::Tetris(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(820, 992))
{
	sb->SetStatusText(wxT("Let's Play!"));
	window = new IniWindow(this);
	//SetIcon(tetrits_xpm);

	wxIcon FrameIcon;
	FrameIcon.CopyFromBitmap(wxBitmap(_T("tetrits")));
	SetIcon(FrameIcon);
}

