#include <wx/wx.h>
#include "Board.h"
#include "Menu.h"
#include "Character.h"

class Tetris;

class IniWindow : public wxWindow
{
private:
	Tetris* tetris; 
	Menu* menu;
	Character* character;
public:
	IniWindow(wxFrame *parent);
	~IniWindow();
	void InitComponents();
	Board* board;
	void SetChar(int character);
	void ShowMenu();
	void ShowGame();
	void ShowCharMenu();
};

