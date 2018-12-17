#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "Menu.h"
#include "Tetris.h"
#include "IniWindow.h"

BEGIN_EVENT_TABLE(Menu, wxPanel)
	EVT_PAINT(Menu::OnPaint)
	EVT_BUTTON(1001, Menu::SinglePButton)
	EVT_BUTTON(1002, Menu::TwoPButton)
END_EVENT_TABLE()

Menu::Menu(wxWindow *window, wxSize panelSize, wxFrame *parent) :
	wxPanel(window, wxID_ANY, wxPoint(0, 0), panelSize, wxBORDER_NONE)
{
	pWindow = (IniWindow*)window;

	this->SetBackgroundColour(wxColour(*wxWHITE));
	
	//membaca file JPEG untuk Background
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);

	//membaca file png untuk Button
	wxImageHandler *pngLoader = new wxPNGHandler();
	wxImage::AddHandler(pngLoader);

	//load image
	this->LoadMenuBG();
	this->LoadButtons();

	//memunculkan buttons
	//wxButton* SinglePButton = new wxButton(this, 1001, wxT("Single Player"), wxPoint(330, 530), wxDefaultSize);
	//wxButton* TwoPButton = new wxButton(this, 1002, wxT("Two-Player"), wxPoint(330, 590), wxDefaultSize);
	wxBitmapButton* SinglePButton = new wxBitmapButton(this, 1001, *onePButton, wxPoint(213, 530));
	wxBitmapButton* TwoPButton = new wxBitmapButton(this, 1002, *twoPButton, wxPoint(213, 630));
}

Menu::~Menu()
{
	delete menuBG;
	delete onePButton;
	delete twoPButton;
}

void Menu::LoadMenuBG()
{
	wxImage menuImage(wxT("MenuBG.jpg"), wxBITMAP_TYPE_JPEG);
	menuBG = new wxBitmap(menuImage);
}

void Menu::LoadButtons()
{
	wxImage onePBImage(wxT("SPButton.png"), wxBITMAP_TYPE_PNG);
	onePButton = new wxBitmap(onePBImage);
	wxImage twoPBImage(wxT("TPButton.png"), wxBITMAP_TYPE_PNG);
	twoPButton = new wxBitmap(twoPBImage);
}

void Menu::OnPaint(wxPaintEvent &event)
{
	wxPaintDC pdc(this);
	if (menuBG != nullptr)
	{
		pdc.DrawBitmap(*menuBG, wxPoint(0, 0), true);
	}
}

void Menu::SinglePButton(wxCommandEvent& event)
{
	pWindow->ShowCharMenu();
}

void Menu::TwoPButton(wxCommandEvent& event)
{
	wxMessageBox(wxT("Sorry, this feature isn't available right now!"));
}