// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include <wx/wx.h>
#include "frame.h"
#include "properties.h"
#include "more-page.h"
#include "game-definition-page.h"
#include "game-word-page.h"
#include "favorite-page.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{
		//mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		//MainFrame->SetClientSize(WIDTH, HEIGHT);
		//MainFrame->Show(true); 
		wxFrame* favorWindow = new wxFrame(nullptr, wxID_ANY, "Favorite Window"); 

		ListWindow* listWindow = new ListWindow(favorWindow); 
		favorWindow->SetClientSize(WIDTH, HEIGHT); 
		favorWindow->Show(true); 
		return true; 
	}
};
wxIMPLEMENT_APP(myApp);
