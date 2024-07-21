// a-mini-dictionary-v3.cpp : Defines the entry point for the application.

#include "MainFrame.h"
#include "HomeFrame.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{


		HomeFrame* homeFrame = new HomeFrame("Dictonary");
		homeFrame->Show();


		return true; 
	}
};
wxIMPLEMENT_APP(myApp);