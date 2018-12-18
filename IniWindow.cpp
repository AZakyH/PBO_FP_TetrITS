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
	if (board != nullptr) {board->Show(false);}
	if (character != nullptr) {character->Show(false);}
	if (gameover != nullptr) { gameover->Show(false); }
	if (legend != nullptr) { legend->Show(false); }
	tetris->sb->SetStatusText(wxT("Let's Play!"));
}

void IniWindow::ShowGame()
{
	board->Show(true);
	board->SetFocus();
	board->Start();
	ShowLegend();
	menu->Show(false);
	character->Show(false);
}

void IniWindow::ShowLegend()
{
	wxMessageOutputDebug().Printf("Masuk IniLegend");
	legend = new Legend(this, wxSize(410, 902), tetris, board);
	legend->SetPosition(wxPoint(411, 0));
	legend->Show(true);
}

void IniWindow::ShowCharMenu()
{
	wxMessageOutputDebug().Printf("Masuk ke ShowCharMenu");
	character = new Character(this, wxSize(820, 992), tetris);
	character->SetPosition(wxPoint(0, 0));
	character->Show(true);
	menu->Show(false);
	if (legend != nullptr) { legend->Show(false); }
}

void IniWindow::ShowGameOver()
{
	gameover = new GameOver(this, wxSize(820, 992), tetris);
	gameover->SetPosition(wxPoint(0, 0));
	gameover->Show(true);
	if (board != nullptr) {board->Show(false);}
	if (character != nullptr) {character->Show(false);}
	if (menu != nullptr) {menu->Show(false);}
	if (legend != nullptr) { legend->Show(false); }
}

void IniWindow::SetChar(int character)
{
	board = new Board(this, wxSize(410, 902), tetris);
	SetPosition(wxPoint(0, 0));
	board->SetSkill(character);
}