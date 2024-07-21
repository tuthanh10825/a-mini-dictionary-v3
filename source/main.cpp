// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
<<<<<<< Updated upstream
#include <wx/wx.h>
#include "frame.h"
=======
#include "MainFrame.h"
#include "HomeFrame.h"
>>>>>>> Stashed changes
class myApp : public wxApp
{
	virtual bool OnInit()
	{
<<<<<<< Updated upstream
		mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		MainFrame->SetClientSize(800, 800);
		MainFrame->Show(true); 
=======
		//mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		//MainFrame->SetClientSize(WIDTH, HEIGHT);
		//MainFrame->Show(true); 

		HomeFrame* homeFrame = new HomeFrame("Dictonary");
		homeFrame->Show();

>>>>>>> Stashed changes
		return true; 
	}
};
wxIMPLEMENT_APP(myApp);