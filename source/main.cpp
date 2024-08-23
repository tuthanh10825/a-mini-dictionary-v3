// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include "base-frame.h"
class myApp : public wxApp
{
	virtual bool OnInit()
	{
		BaseFrame* baseFrame = new BaseFrame(wxString("A mini dictionary")); 
		baseFrame->SetClientSize(WIDTH, HEIGHT); 
		baseFrame->Show(true); 
		return true; 
	}
	~myApp()
	{
  
		delete EVtree;
		delete EEtree;
		delete VEtree;
		delete EMOtree;

		delete SLtree;
	}
};
wxIMPLEMENT_APP(myApp);
