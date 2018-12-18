#include <wx/wx.h>
#include "Board.h"

class IniWindow;

class Tetris : public wxFrame
{
public:
	Tetris(const wxString& title);
	wxStatusBar *sb = CreateStatusBar();
private:
	IniWindow *window;
	wxBitmap* logo;
};