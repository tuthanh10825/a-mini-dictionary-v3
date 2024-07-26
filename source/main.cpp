// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include <wx/wx.h>
#include "frame.h"
#include "properties.h"
#include "more-page.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{
		//mainFrame* MainFrame = new mainFrame(wxT("dictionary"));
		//MainFrame->SetClientSize(WIDTH, HEIGHT);
		//MainFrame->Show(true); 
		MoreWindow* morewindow = new MoreWindow("More Page"); 
		morewindow->SetClientSize(WIDTH, HEIGHT);
		morewindow->Show(true);
		return true; 
	}
};
wxIMPLEMENT_APP(myApp);