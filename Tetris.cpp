#include "Tetris.h"
#include "IniWindow.h"


Tetris::Tetris(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(820, 992))
{
	wxStatusBar *sb = CreateStatusBar();
	sb->SetStatusText(wxT("0"));
	window = new IniWindow(this);
}

