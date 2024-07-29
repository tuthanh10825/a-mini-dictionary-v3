// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include <wx/wx.h>
#include "frame.h"
#include "properties.h"
#include "more-page.h"
#include "game-definition-page.h"
#include "game-word-page.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{
		//mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		//MainFrame->SetClientSize(WIDTH, HEIGHT);
		//MainFrame->Show(true); 
		Wgamewindow* wordgamewindow = new Wgamewindow("Word Game Page");
		wordgamewindow->SetClientSize(1451, 631);
		wordgamewindow->SetBackgroundColour(wxColor(255, 255, 255));
		wordgamewindow->Show(true);
		return true; 
	}
};
wxIMPLEMENT_APP(myApp);
wxBEGIN_EVENT_TABLE(DefGameWindow, wxFrame)
EVT_RADIOBUTTON(wxID_ANY, DefGameWindow::OnRadioButton)
wxEND_EVENT_TABLE()