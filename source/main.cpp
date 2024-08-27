// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include "base-frame.h"
class myApp : public wxApp
{
public: 
	myApp()
	{
		loadInserting(); 
		loadRemoving(); 
		removingEE.begin();
	}
private: 
	virtual bool OnInit()
	{
		BaseFrame* baseFrame = new BaseFrame(wxString("A mini dictionary")); 
		baseFrame->SetClientSize(WIDTH, HEIGHT); 
		baseFrame->Show(true); 
		return true; 
	}
	~myApp()
	{
		saveInserting();
		saveRemoving();
		delete EVtree;
		delete EEtree;
		delete VEtree;
		delete EMOtree;
		delete SLtree;
		removingEE.clear(); 
		removingEV.clear();
		removingVE.clear(); 
		removingSlang.clear(); 
		removingEmo.clear();

	}
};
wxIMPLEMENT_APP(myApp);
