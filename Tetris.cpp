#include "Tetris.h"
#include "IniWindow.h"


Tetris::Tetris(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(820, 992))
{
	sb->SetStatusText(wxT("Let's Play!"));
	window = new IniWindow(this);
}

