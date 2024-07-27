// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include <wx/wx.h>
#include "frame.h"
#include "properties.h"
#include "more-page.h"
#include "game-definition-page.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{
		//mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		//MainFrame->SetClientSize(WIDTH, HEIGHT);
		//MainFrame->Show(true); 
		DefGameWindow* defgamewindow = new DefGameWindow("Definition Game Page");
		defgamewindow->SetClientSize(1451, 631);
		defgamewindow->SetBackgroundColour(wxColor(255, 255, 255));
		defgamewindow->Show(true);
		return true; 
	}
};
wxIMPLEMENT_APP(myApp);
wxBEGIN_EVENT_TABLE(DefGameWindow, wxFrame)
EVT_RADIOBUTTON(wxID_ANY, DefGameWindow::OnRadioButton)
wxEND_EVENT_TABLE()