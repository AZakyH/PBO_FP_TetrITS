#include <wx/wx.h>
#include "Board.h"
#include "Menu.h"
#include "Character.h"
#include "GameOver.h"
#include "Legend.h"

class Tetris;

class IniWindow : public wxWindow
{
private:
	Tetris* tetris; 
	Menu* menu;
	Character* character;
	GameOver* gameover;
public:
	IniWindow(wxFrame *parent);
	~IniWindow();

	Board* board;
	Legend* legend;
	void ShowMenu();
	void ShowGame(Board* board);
	void ShowCharMenu();
	void ShowGameOver();
};

