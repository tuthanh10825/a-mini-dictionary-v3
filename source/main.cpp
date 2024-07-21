// a-mini-dictionary-v3.cpp : Defines the entry point for the application.

#include "main-frame.h"
#include "home-frame.h"
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