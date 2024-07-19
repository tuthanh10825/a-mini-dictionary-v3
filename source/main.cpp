// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include <wx/wx.h>
#include "frame.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{
		mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		MainFrame->SetClientSize(800, 800);
		MainFrame->Show(true); 
		return true; 
	}
};
wxIMPLEMENT_APP(myApp);