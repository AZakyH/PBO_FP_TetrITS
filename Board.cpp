#include "Board.h"
#include "Tetris.h"
#include "IniWindow.h"

Board::Board(wxWindow *window, wxSize panel, wxFrame *parent)
	: wxPanel(window, wxID_ANY, wxPoint(0, 0), panel, wxBORDER_NONE)
{
	pWindow = (IniWindow*)window;

	//membaca file JPEG untuk Background
	wxImageHandler *jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);

	timer = new wxTimer(this, 1);
	
	m_stsbar = parent->GetStatusBar();
	m_stsbar->SetStatusText("0");
	isFallingFinished = false;
	isStarted = false;
	isPaused = false;
	isHold = false;
	extraLine = false;
	extraShape = false;
	rotate = false;
	
	gameTime = 1000;
	nextLevel = 5;
	nextSkill = 10;
	numLinesRemoved = 0;

	curX = 0;
	curY = 0;
	
	skill = 0;
	counter = 0;

	holdPiece.SetShape(NoShape);
	ClearBoard();

	Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Board::OnKeyDown));
	Connect(wxEVT_TIMER, wxCommandEventHandler(Board::OnTimer));
}

void Board::Start()
{
	LoadGameBG();
	Connect(wxEVT_PAINT, wxPaintEventHandler(Board::OnPaint));

	if (isPaused)
		return;

	isStarted = true;
	isFallingFinished = false;
	numLinesRemoved = 0;
	ClearBoard();

	NewPiece();
	timer->Start(gameTime);
}

void Board::Pause()
{
	if (!isStarted)
		return;

	isPaused = !isPaused;
	if (isPaused) {
		timer->Stop();
		m_stsbar->SetStatusText(wxT("paused"));
	}
	else {
		timer->Start(gameTime);
		wxString str;
		str.Printf(wxT("%d"), numLinesRemoved);
		m_stsbar->SetStatusText(str);
	}
}

void Board::LoadGameBG()
{
	if (skill == 0)
	{
		wxImage gameBGImage(wxT("ElizabethBG.jpg"), wxBITMAP_TYPE_JPEG);
		gameBackGround = new wxBitmap(gameBGImage);
	}
	else if (skill == 1)
	{
		wxImage gameBGImage(wxT("PikachuBG.jpg"), wxBITMAP_TYPE_JPEG);
		gameBackGround = new wxBitmap(gameBGImage);
	}
	else
	{
		wxImage gameBGImage(wxT("HamtaroBG.jpg"), wxBITMAP_TYPE_JPEG);
		gameBackGround = new wxBitmap(gameBGImage);
	}
}

void Board::OnPaint(wxPaintEvent& event)
{
	wxPaintDC gameBG(this);

	if (gameBackGround != nullptr)
	{
		gameBG.DrawBitmap(*gameBackGround, wxPoint(0, 0), true);
	}

	wxPaintDC dc(this);

	wxSize size = GetClientSize();
	int boardTop = size.GetHeight() - BoardHeight * SquareHeight();


	for (int i = 0; i < BoardHeight; ++i) {
		for (int j = 0; j < BoardWidth; ++j) {
			Blocks shape = ShapeAt(j, BoardHeight - i - 1);
			if (shape != NoShape)
				DrawSquare(dc, 0 + j * SquareWidth(),
					boardTop + i * SquareHeight(), shape);
		}
	}

	if (curPiece.GetShape() != NoShape) {
		for (int i = 0; i < 4; ++i) {
			int x = curX + curPiece.x(i);
			int y = curY - curPiece.y(i);
			DrawSquare(dc, 0 + x * SquareWidth(),
				boardTop + (BoardHeight - y - 1) * SquareHeight(),
				curPiece.GetShape());
		}
	}
}

void Board::DrawSquare(wxPaintDC& dc, int x, int y, Blocks shape)
{
	static wxColour colors[] = { wxColour(0, 0, 0), wxColour(240, 0, 0),
		wxColour(0, 240, 0), wxColour(0, 240, 240),
		wxColour(160, 0, 240), wxColour(240, 240, 0),
		wxColour(240, 160, 0), wxColour(0, 0, 240), wxColour(100, 100, 100) };
	
	static wxColour light[] = { wxColour(0, 0, 0), wxColour(251, 179, 179),
		wxColour(179, 251, 179), wxColour(179, 251, 251),
		wxColour(227, 179, 251), wxColour(251, 251, 179),
		wxColour(251, 227, 179), wxColour(179, 179, 251), wxColour(150, 150, 150) };

	static wxColour dark[] = { wxColour(0, 0, 0), wxColour(120, 0, 0),
		wxColour(0, 120, 0), wxColour(0, 120, 120),
		wxColour(80, 0, 120), wxColour(120, 120, 0),
		wxColour(120, 80, 0), wxColour(0, 0, 120), wxColour(50, 50, 50) };

	wxPen pen(light[int(shape)]);
	pen.SetCap(wxCAP_PROJECTING);
	dc.SetPen(pen);

	dc.DrawLine(x, y + SquareHeight() - 1, x, y);
	dc.DrawLine(x, y, x + SquareWidth() - 1, y);

	wxPen darkpen(dark[int(shape)]);
	darkpen.SetCap(wxCAP_PROJECTING);
	dc.SetPen(darkpen);

	dc.DrawLine(x + 1, y + SquareHeight() - 1,
		x + SquareWidth() - 1, y + SquareHeight() - 1);
	dc.DrawLine(x + SquareWidth() - 1,
		y + SquareHeight() - 1, x + SquareWidth() - 1, y + 1);

	dc.SetPen(*wxTRANSPARENT_PEN);
	dc.SetBrush(wxBrush(colors[int(shape)]));
	dc.DrawRectangle(x + 1, y + 1, SquareWidth() - 2,
		SquareHeight() - 2);
}

void Board::OnKeyDown(wxKeyEvent& event)
{
	if (!isStarted || curPiece.GetShape() == NoShape) {
		event.Skip();
		return;
	}

	int keycode = event.GetKeyCode();

	if (keycode == 'p' || keycode == 'P') {
		Pause();
		return;
	}

	if (isPaused)
		return;

	switch (keycode) {
	case WXK_LEFT:
		TryMove(curPiece, curX - 1, curY);
		break;
	case WXK_RIGHT:
		TryMove(curPiece, curX + 1, curY);
		break;
	case WXK_DOWN:
		OneLineDown();
		break;
	case WXK_UP:
		rotate = true;
		TryMove(curPiece.RotateRight(), curX, curY);
		rotate = false;
		break;
	case WXK_SPACE:
		HardDrop();
		break;
	case 'z':
		TryMove(curPiece.RotateLeft(), curX, curY);
		break;
	case 'Z':
		TryMove(curPiece.RotateLeft(), curX, curY);
		break;
	case WXK_SHIFT:
		if (!isHold) {
			isHold = true;
			NewPiece();
		}
		break;
	default:
		event.Skip();
	}
}

void Board::OnTimer(wxCommandEvent& event)
{
	if (isFallingFinished) {
		isFallingFinished = false;
		NewPiece();
	}
	else {
		OneLineDown();
	}
}

void Board::ClearBoard()
{
	for (int i = 0; i < BoardHeight * BoardWidth; ++i)
		board[i] = NoShape;
}

void Board::HardDrop()
{
	int newY = curY;
	while (newY > 0) {
		if (!TryMove(curPiece, curX, newY - 1))
			break;
		--newY;
	}
	PieceDropped();
}

void Board::OneLineDown()
{
	if (!TryMove(curPiece, curX, curY - 1))
		PieceDropped();
}

void Board::PieceDropped()
{
	for (int i = 0; i < 4; ++i) {
		int x = curX + curPiece.x(i);
		int y = curY - curPiece.y(i);
		ShapeAt(x, y) = curPiece.GetShape();
	}

	RemoveFullLines();
	if (isHold)
		isHold = false;
	if (!isFallingFinished)
		NewPiece();
}

void Board::RemoveFullLines()
{
	int numFullLines = 0;

	for (int i = BoardHeight - 1; i >= 0; --i) {
		bool lineIsFull = true;

		for (int j = 0; j < BoardWidth; ++j) {
			if (ShapeAt(j, i) == NoShape) {
				lineIsFull = false;
				break;
			}
		}

		if (lineIsFull) {
			++numFullLines;
			for (int k = i; k < BoardHeight - 1; ++k) {
				for (int j = 0; j < BoardWidth; ++j)
					ShapeAt(j, k) = ShapeAt(j, k + 1);
			}
		}
	}

	if (numFullLines > 0) {
		numLinesRemoved += numFullLines;

		if (extraLine) {
			if (counter > 0) {
				if (numFullLines >= 1 && numFullLines <= 2) {
					numLinesRemoved++;
				}
				else {
					numLinesRemoved += 2;
				}
				counter--;
			}
			else {
				extraLine = false;
			}
		}

		if (numLinesRemoved >= nextLevel) {
			nextLevel += 5;
			gameTime = gameTime * 5 / 6;
			timer->Start(gameTime);
		}
		if (numLinesRemoved >= nextSkill) {
			nextSkill += 10;
			ActivateSkill(skill);
		}
		wxString str;
		str.Printf(wxT("%d"), numLinesRemoved);
		m_stsbar->SetStatusText(str);

		isFallingFinished = true;
		curPiece.SetShape(NoShape);
		Refresh();
	}
}

void Board::NewPiece()
{
	if (isHold) {
		if (holdPiece.GetShape() == NoShape) {
			holdPiece.SetShape(curPiece.GetShape());
			curPiece.SetRandomShape();
		}
		else {
			Shape temp;
			temp.SetShape(holdPiece.GetShape());
			holdPiece.SetShape(curPiece.GetShape());
			curPiece.SetShape(temp.GetShape());
		}
	}
	else {
		if (extraShape) {
			if (counter > 0) {
				counter--;
				curPiece.SetShape(ExtraShape);
			}
			else {
				extraShape = false;
				curPiece.SetRandomShape();
			}
		}
		else {
			curPiece.SetRandomShape();
		}
	}

	curX = BoardWidth / 2 + 1;
	curY = BoardHeight - 1 + curPiece.MinY();

	if (!TryMove(curPiece, curX, curY)) {
		curPiece.SetShape(NoShape);
		timer->Stop();
		isStarted = false;
		m_stsbar->SetStatusText(wxT("game over"));
		pWindow->ShowGameOver();
	}
}

bool Board::TryMove(const Shape& newPiece, int newX, int newY)
{
	int bounceXMIN = 0, bounceXMAX = BoardWidth;
	for (int i = 0; i < 4; ++i) {
		int x = newX + newPiece.x(i);
		int y = newY - newPiece.y(i);
		if (rotate) {
			if (x < 0) {
				if (x < bounceXMIN) {
					bounceXMIN = x;
				}
			}
			if (x >= BoardWidth) {
				if (x >= bounceXMAX) {
					bounceXMAX = x + 1;
				}
			}
			if (y < 0 || y >= BoardHeight)
				return false;
			if (ShapeAt(x, y) != NoShape)
				return false;
		}
		else {
			if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
				return false;
			if (ShapeAt(x, y) != NoShape)
				return false;
		}
	}

	curPiece = newPiece;
	curX = newX - bounceXMIN - (bounceXMAX - BoardWidth);
	curY = newY;
	Refresh();
	return true;
}

void Board::ActivateSkill(int skill) {
	if (skill == 0) { // skill Elizabeth
		counter = 10;
		extraShape = true;
	}
	else if (skill == 1) { // skill Pikachu
		counter = 3;
		extraLine = true;
	}
	else { // skill Hamtaro
		for (int k = 0; k < BoardHeight - 4; ++k) {
			for (int j = 0; j < BoardWidth; ++j)
				ShapeAt(j, k) = ShapeAt(j, k + 4);
		}
	}
}

void Board::SetSkill(int character)
{
	this->skill = character;
}
