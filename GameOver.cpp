#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "GameOver.h"
#include "Tetris.h"
#include "IniWindow.h"

BEGIN_EVENT_TABLE(GameOver, wxPanel)
EVT_PAINT(GameOver::OnPaint)
EVT_BUTTON(1006, GameOver::MenuButton)
END_EVENT_TABLE()

GameOver::GameOver(IniWindow *window, wxSize panelSize, wxFrame *parent) :
	wxPanel(window, wxID_ANY, wxPoint(0, 0), panelSize, wxBORDER_NONE)
{
	pWindow = window;

	this->SetBackgroundColour(wxColour(*wxWHITE));

	//membaca file JPEG untuk Background
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);

	//membaca file png untuk Button
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	//load image
	this->LoadGameOverBG();
	this->LoadButtons();

	wxBitmapButton* MenuButton = new wxBitmapButton(this, 1006, *menuButton, wxPoint(213, 580));
}

GameOver::~GameOver()
{
	delete gameOverBG;
	delete menuButton;
}

void GameOver::LoadGameOverBG()
{
	wxImage gameOverImage(wxT("GameOverScreen.jpg"), wxBITMAP_TYPE_JPEG);
	gameOverBG = new wxBitmap(gameOverImage);
}

void GameOver::LoadButtons()
{
	wxImage menuBImage(wxT("MenuButton.png"), wxBITMAP_TYPE_PNG);
	menuButton = new wxBitmap(menuBImage);
}

void GameOver::OnPaint(wxPaintEvent &event)
{
	wxPaintDC pdc(this);
	if (gameOverBG != nullptr)
	{
		pdc.DrawBitmap(*gameOverBG, wxPoint(0, 0), true);
	}
}

void GameOver::MenuButton(wxCommandEvent & event)
{
	pWindow->ShowMenu();
}
