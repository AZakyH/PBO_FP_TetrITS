#include "IniWindow.h"
#include "Tetris.h"
#include "Character.h"

IniWindow::IniWindow(wxFrame *parent) :
	wxWindow(parent, wxID_ANY)
{
	tetris = (Tetris*)parent;
	InitComponents();
}


IniWindow::~IniWindow()
{
}

void IniWindow::InitComponents()
{
	ShowMenu();
}

void IniWindow::ShowMenu()
{
	menu = new Menu(this, wxSize(820, 992), tetris);
	menu->SetPosition(wxPoint(0, 0));
	menu->Show(true);
}

void IniWindow::ShowGame()
{
	board->Show(true);
	board->SetFocus();
	board->Start();
	menu->Show(false);
	character->Show(false);
}

void IniWindow::ShowCharMenu()
{
	wxMessageOutputDebug().Printf("Masuk ke ShowCharMenu");
	character = new Character(this, wxSize(820, 992), tetris);
	character->SetPosition(wxPoint(0, 0));
	character->Show(true);
	menu->Show(false);
}

void IniWindow::SetChar(int character)
{
	board = new Board(this, wxSize(410, 902), tetris);
	SetPosition(wxPoint(0, 0));
	board->SetSkill(character);
}