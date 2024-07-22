// a-mini-dictionary-v3.cpp : Defines the entry point for the application.


#include "base-frame.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{


		BaseFrame* mainFrame = new BaseFrame("Dictonary");
		mainFrame->SetClientSize(WIDTH, HEIGHT); 
		mainFrame->Show();
		


		return true; 
	}
};
wxIMPLEMENT_APP(myApp);