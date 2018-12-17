#include <wx/wx.h>
#include "Board.h"

class IniWindow;

class Tetris : public wxFrame
{
public:
	Tetris(const wxString& title);
private:
	IniWindow *window;
};