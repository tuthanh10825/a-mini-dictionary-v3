#include "home-page.h"
#include "Globals.h"
#include "wx/wx.h"
#include "properties.h"


HomePage::HomePage(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	wxColour background, selection;
	if (LIGHTMODE) {
		background = LIGHTMODE_backgroundANDNaviColor;
	}
	else {
		background = DARKMODE_backgroundColor;
	}
	
	//for rightpanel. 
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL); 
	rightPanel = new wxPanel(this, wxID_ANY);
	rightPanel->SetBackgroundColour(background);
	

	wxBitmap* label = new wxBitmap("assets/homepage/label.png", wxBITMAP_TYPE_PNG);
	showLabel = new wxStaticBitmap(rightPanel, wxID_ANY, *label);
	showLabel->SetBackgroundColour(background);
	rightSizer->Add(showLabel, 1, wxEXPAND); 

	std::string s;
	if (LIGHTMODE) s = '1'; else s = "";
	wxBoxSizer* quizSizer = new wxBoxSizer(wxVERTICAL); 
	wxBitmap* quizBitmap = new wxBitmap("assets/homepage/quiz-button"+s+".png", wxBITMAP_TYPE_PNG); 
	quizButton = new wxBitmapButton(rightPanel, wxID_ANY, *quizBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP | wxBORDER_RAISED);
	quizButton->SetBackgroundColour(background);
	quizSizer->Add(quizButton, 0); 
	rightSizer->Add(quizSizer, 1, wxLEFT, 60); 
	
	wxBoxSizer* favorSizer = new wxBoxSizer(wxVERTICAL);
	wxBitmap* favorBitmap = new wxBitmap("assets/homepage/favor-button"+s+".png", wxBITMAP_TYPE_PNG); 
	favorButton = new wxBitmapButton(rightPanel, wxID_ANY, *favorBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	favorSizer->Add(favorButton, 0); 
	favorButton->SetBackgroundColour(background);
	rightSizer->Add(favorSizer, 1, wxALIGN_RIGHT | wxRIGHT, 60);

	wxBoxSizer* randomSizer = new wxBoxSizer(wxVERTICAL); 
	wxBitmap* randomBitmap = new wxBitmap("assets/homepage/random-button"+s+".png", wxBITMAP_TYPE_PNG);
	randomButton = new wxBitmapButton(rightPanel, wxID_ANY, *randomBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	randomSizer->Add(randomButton, 0);
	randomButton->SetBackgroundColour(background);
	rightSizer->Add(randomSizer, 1, wxLEFT, 60);

	wxBoxSizer* editSizer = new wxBoxSizer(wxVERTICAL);
	wxBitmap* editBitmap = new wxBitmap("assets/homepage/edit-button"+s+".png", wxBITMAP_TYPE_PNG); 
	editButton = new wxBitmapButton(rightPanel, wxID_ANY, *editBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	editSizer->Add(editButton, 0);
	editButton->SetBackgroundColour(background);
	rightSizer->Add(editSizer, 1, wxALIGN_RIGHT | wxRIGHT, 60);
	
	rightPanel->SetSizerAndFit(rightSizer); 
	
	// for left panel. 
	leftPanel = new wxPanel(this, wxID_ANY);
	leftPanel->SetBackgroundColour(background); 

	wxBoxSizer* centeringSizer = new wxBoxSizer(wxVERTICAL);

	subPanel = new wxPanel(leftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	
	
	centeringSizer->Add(subPanel, 1, wxALL | wxEXPAND, 100);
	leftPanel->SetSizerAndFit(centeringSizer);

	wxBoxSizer* wotdSizer = new wxBoxSizer(wxVERTICAL);

	wxBitmap* wotdBitmap = new wxBitmap("assets/homepage/word-of-the-day"+s+".png", wxBITMAP_TYPE_PNG); 
	wordOfTheDay = new wxStaticBitmap(subPanel, wxID_ANY, *wotdBitmap); 
	wotdSizer->Add(wordOfTheDay, 1); 

	wordPanel = new wxPanel(subPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER);

	// Add content to wordPanel
	wxBoxSizer* wordSizer = new wxBoxSizer(wxVERTICAL);

	if (!EEtree->isLoaded())
		EEtree->loadWord(EEDATASET);
	auto randomText = EEtree->random();
	wxString wordText = wxString(una::utf32to16(randomText.first));
	std::string defText = randomText.second;

	wordInfo = new wxStaticText(wordPanel, wxID_ANY, wordText, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxFont::AddPrivateFont("fonts/pala.ttf");
	wxFont pala(40, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
	wordInfo->SetFont(pala);

	defInfo= new wxStaticText(wordPanel, wxID_ANY, defText, wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT);
	wxFont pala20(20, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
	defInfo->SetFont(pala20);

	// Add components with proportion 0 to avoid extra spacing
	wordSizer->Add(wordInfo, 0, wxALL | wxALIGN_LEFT, 10);
	wordSizer->Add(defInfo, 0, wxALL | wxALIGN_LEFT, 5);
	wordPanel->SetSizerAndFit(wordSizer);

	wotdSizer->Add(wordPanel, 3, wxEXPAND);
	subPanel->SetSizerAndFit(wotdSizer);


	// handle left & right.
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(leftPanel, 1, wxEXPAND);
	mainSizer->Add(rightPanel, 1, wxEXPAND);

	this->SetSizerAndFit(mainSizer);
	return;

}

void HomePage::FlipColor()
{

	wxColour background, selection;
	if (LIGHTMODE) {
		background = LIGHTMODE_backgroundANDNaviColor;
	}
	else {
		background = DARKMODE_backgroundColor;
	}
	showLabel->SetBackgroundColour(background);
	std::string s;
	if (LIGHTMODE) s = '1'; else s = "";
	quizButton->SetBitmapLabel(wxBitmap("assets/homepage/quiz-button" + s + ".png", wxBITMAP_TYPE_PNG)); 
	quizButton->SetBackgroundColour(background); 

	favorButton->SetBitmapLabel(wxBitmap("assets/homepage/favor-button" + s + ".png", wxBITMAP_TYPE_PNG)); 
	favorButton->SetBackgroundColour(background); 
	
	randomButton->SetBitmapLabel(wxBitmap("assets/homepage/random-button" + s + ".png", wxBITMAP_TYPE_PNG)); 
	randomButton->SetBackgroundColour(background); 
	
	editButton->SetBitmapLabel(wxBitmap("assets/homepage/edit-button" + s + ".png", wxBITMAP_TYPE_PNG)); 
	editButton->SetBackgroundColour(background);

	wordOfTheDay->SetBackgroundColour(background); 
	wordOfTheDay->SetBitmap(wxBitmap("assets/homepage/word-of-the-day" + s + ".png", wxBITMAP_TYPE_PNG));

	
	rightPanel->SetBackgroundColour(background); 
	leftPanel->SetBackgroundColour(background); 
	subPanel->SetBackgroundColour(background);
	wordPanel->SetBackgroundColour(background); 
	if (LIGHTMODE)
	{
		wordInfo->SetForegroundColour(*wxBLACK);
		defInfo->SetForegroundColour(*wxBLACK); 
	}
	else
	{
		wordInfo->SetForegroundColour(*wxWHITE);
		defInfo->SetForegroundColour(*wxWHITE);
	}
	this->Refresh();
}

