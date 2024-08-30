// a-mini-dictionary-v3.cpp : Defines the entry point for the application.
#include "base-frame.h"
class myApp : public wxApp
{
public: 
	myApp()
	{
		loadInserting(); 
		loadRemoving(); 
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
		
		if (isRebuildEE)
		{
			EEDef.loadText("data/ee/data.txt"); 
			EEDef.build(); 
			EEDef.serialize("ENG/ENG");
		}
		else
		{
			if (!EEDef.SA_index.empty())
				EEDef.serialize("ENG/ENG");
		}

		if (isRebuildEV)
		{
			EVDef.loadText("data/ev/data.txt");
			EVDef.build();
			EVDef.serialize("ENG/VIE");
		}
		else
		{
			if (!EVDef.SA_index.empty())
				EVDef.serialize("ENG/VIE");
		}

		if (isRebuildVE)
		{
			VEDef.loadText("data/ve/data.txt");
			VEDef.build();
			VEDef.serialize("VIE/ENG");
		}
		else
		{
			if (!VEDef.SA_index.empty())
				VEDef.serialize("VIE/ENG");
		}

		if (isRebuildSlang)
		{
			SLDef.loadText("data/slang/data.txt");
			SLDef.build();
			SLDef.serialize("SLANG");
		}
		else
		{
			if (!SLDef.SA_index.empty())
				SLDef.serialize("SLANG");
		}

		if (isRebuildEmo)
		{
			EMODef.loadText("data/emo/data.txt");
			EMODef.build();
			EMODef.serialize("EMOTICON");
		}
		else
		{
			if (!EMODef.SA_index.empty())
				EMODef.serialize("EMOTICON");
		}
		removingEE.clear(); 
		removingEV.clear();
		removingVE.clear(); 
		removingSlang.clear(); 
		removingEmo.clear();
		addingEE.clear(); 
		addingEV.clear(); 
		addingVE.clear(); 
		addingEmo.clear(); 
		addingSlang.clear(); 
		delete EVtree;
		delete EEtree;
		delete VEtree;
		delete EMOtree;
		delete SLtree;
		EEDef.clear(); 
		EVDef.clear(); 
		VEDef.clear(); 
		SLDef.clear(); 
		EMODef.clear();

	}
};
wxIMPLEMENT_APP(myApp);
