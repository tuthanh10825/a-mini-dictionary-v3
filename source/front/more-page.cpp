#include "more-page.h"
#include "properties.h"
#include "Globals.h"
#include "base-frame.h"

MoreWindow::MoreWindow(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{

	wxColour background;
	if (LIGHTMODE) {
		background = LIGHTMODE_backgroundANDNaviColor;
	}
	else {
		background = DARKMODE_backgroundColor;
	}


	wxPanel* aboutUsPanel = new wxPanel(this, wxID_ANY);
	aboutUsPanel->SetBackgroundColour(wxColor(101, 164, 165));
	wxStaticBitmap* aboutUsText = new wxStaticBitmap(aboutUsPanel, wxID_ANY, wxBitmap("assets/more/about-us-text.png", wxBITMAP_TYPE_PNG));
	
	wxBoxSizer* aboutUsTextHoriSizer = new wxBoxSizer(wxHORIZONTAL); 
	aboutUsTextHoriSizer->Add(aboutUsText, 3, wxALIGN_BOTTOM | wxBOTTOM, 15); 

	wxBoxSizer* aboutUsTextVertSizer = new wxBoxSizer(wxVERTICAL); 
	aboutUsTextVertSizer->Add(aboutUsTextHoriSizer, 0, wxLEFT | wxTOP, 60); 
	
	aboutUsPanel->SetSizerAndFit(aboutUsTextVertSizer); 

	wxPanel* descriptionPanel = new wxPanel(this, wxID_ANY); 
	descriptionPanel->SetBackgroundColour(background);


	wxStaticBitmap* descriptionText = new wxStaticBitmap(descriptionPanel, wxID_ANY, wxBitmap("assets/more/description-text.png", wxBITMAP_TYPE_PNG)); 
	
	wxBitmapButton* userManualButton = new wxBitmapButton(descriptionPanel, wxID_ANY, wxBitmap("assets/more/user-manual-button.png", wxBITMAP_TYPE_PNG)); 
	userManualButton->SetBackgroundColour(background);
	wxStaticBitmap* userManualText = new wxStaticBitmap(descriptionPanel, wxID_ANY, wxBitmap("assets/more/user-manual-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* userManualSizer = new wxBoxSizer(wxVERTICAL); 
	userManualSizer->Add(userManualButton, 0, wxALIGN_CENTER); 
	userManualSizer->Add(userManualText, 0, wxALIGN_CENTER);
	userManualButton->Bind(wxEVT_BUTTON, &MoreWindow::OnUserManualClicked, this); 

	darkmodeButton = new wxBitmapButton(descriptionPanel, wxID_ANY, wxBitmap("assets/more/dark-mode-button.png", wxBITMAP_TYPE_PNG)); 
	darkmodeButton->SetBackgroundColour(background);
	wxStaticBitmap* darkmodeText = new wxStaticBitmap(descriptionPanel, wxID_ANY, wxBitmap("assets/more/dark-mode-text.png", wxBITMAP_TYPE_PNG)); 
	wxBoxSizer* darkmodeSizer = new wxBoxSizer(wxVERTICAL); 
	darkmodeSizer->Add(darkmodeButton, 0, wxALIGN_CENTER); 
	darkmodeSizer->Add(darkmodeText, 0, wxALIGN_CENTER); 
	darkmodeButton->Bind(wxEVT_BUTTON, &MoreWindow::OnDarkmodeClicked, this);

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL); 
	buttonSizer->Add(userManualSizer, 1, wxALIGN_CENTER); 
	buttonSizer->Add(darkmodeSizer, 1, wxALIGN_CENTER); 

	wxBoxSizer* descriptionPanelSizer = new wxBoxSizer(wxVERTICAL);
	descriptionPanelSizer->Add(descriptionText, 1, wxEXPAND); 
	descriptionPanelSizer->Add(buttonSizer, 1, wxEXPAND); 

	descriptionPanel->SetSizerAndFit(descriptionPanelSizer); 

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 
	mainSizer->Add(aboutUsPanel, 0, wxEXPAND); 
	mainSizer->Add(descriptionPanel, 1, wxEXPAND);
	this->SetSizerAndFit(mainSizer); 
}

void MoreWindow::OnUserManualClicked(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser(wxString("https://github.com/tuthanh10825/a-mini-dictionary-v3"));
}

//void MoreWindow::OnDarkmodeClicked(wxCommandEvent&)
//{
//	LIGHTMODE = !LIGHTMODE;
//}
void MoreWindow::OnDarkmodeClicked(wxCommandEvent&)
{
	if (LIGHTMODE) LIGHTMODE = false;
	else LIGHTMODE = true;
	this->Refresh();
	this->Update();
}
