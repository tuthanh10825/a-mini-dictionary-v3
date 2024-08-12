#include "home-page.h"
#include "wx/wx.h"
#include "properties.h"


HomePage::HomePage(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{

	
	//for rightpanel. 
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL); 
	wxPanel* rightPanel = new wxPanel(this, wxID_ANY); 
	rightPanel->SetBackgroundColour(WHITE);
	
	wxBitmap* label = new wxBitmap("assets/homepage/label.png", wxBITMAP_TYPE_PNG);
	wxStaticBitmap* showLabel = new wxStaticBitmap(rightPanel, wxID_ANY, *label);
	showLabel->SetBackgroundColour(WHITE); 
	rightSizer->Add(showLabel, 1, wxEXPAND); 

	wxBoxSizer* quizSizer = new wxBoxSizer(wxVERTICAL); 
	wxBitmap* quizBitmap = new wxBitmap("assets/homepage/quiz-button.png", wxBITMAP_TYPE_PNG); 
	quizButton = new wxBitmapButton(rightPanel, wxID_ANY, *quizBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	quizSizer->Add(quizButton, 0); 
	rightSizer->Add(quizSizer, 1, wxLEFT, 60); 
	
	wxBoxSizer* favorSizer = new wxBoxSizer(wxVERTICAL);
	wxBitmap* favorBitmap = new wxBitmap("assets/homepage/favor-button.png", wxBITMAP_TYPE_PNG); 
	favorButton = new wxBitmapButton(rightPanel, wxID_ANY, *favorBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	favorSizer->Add(favorButton, 0); 
	rightSizer->Add(favorSizer, 1, wxALIGN_RIGHT | wxRIGHT, 60);

	wxBoxSizer* randomSizer = new wxBoxSizer(wxVERTICAL); 
	wxBitmap* randomBitmap = new wxBitmap("assets/homepage/random-button.png", wxBITMAP_TYPE_PNG);
	randomButton = new wxBitmapButton(rightPanel, wxID_ANY, *randomBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	randomSizer->Add(randomButton, 0); 
	rightSizer->Add(randomSizer, 1, wxLEFT, 60);

	wxBoxSizer* editSizer = new wxBoxSizer(wxVERTICAL);
	wxBitmap* editBitmap = new wxBitmap("assets/homepage/edit-button.png", wxBITMAP_TYPE_PNG); 
	editButton = new wxBitmapButton(rightPanel, wxID_ANY, *editBitmap, wxDefaultPosition, wxDefaultSize, wxBU_LEFT | wxBU_RIGHT | wxBU_BOTTOM | wxBU_TOP);
	editSizer->Add(editButton, 0); 
	rightSizer->Add(editSizer, 1, wxALIGN_RIGHT | wxRIGHT, 60);
	
	rightPanel->SetSizerAndFit(rightSizer); 
	
	//for left panel. 
	wxPanel* leftPanel = new wxPanel(this, wxID_ANY);
	leftPanel->SetBackgroundColour(WHITE); 

	wxBoxSizer* centeringSizer = new wxBoxSizer(wxVERTICAL); 

	wxPanel* subPanel = new wxPanel(leftPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	subPanel->SetBackgroundColour(WHITE); 
	
	centeringSizer->Add(subPanel, 1, wxALL | wxEXPAND, 100);
	leftPanel->SetSizerAndFit(centeringSizer);

	wxBoxSizer* wotdSizer = new wxBoxSizer(wxVERTICAL); 

	wxBitmap* wotdBitmap = new wxBitmap("assets/homepage/word-of-the-day.png", wxBITMAP_TYPE_PNG); 
	wxStaticBitmap* wordOfTheDay = new wxStaticBitmap(subPanel, wxID_ANY, *wotdBitmap); 
	wotdSizer->Add(wordOfTheDay, 1); 

	wordPanel = new wxPanel(subPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER); 

	wotdSizer->Add(wordPanel, 3, wxEXPAND); 
	subPanel->SetSizerAndFit(wotdSizer);
	
	
	
	
	//handle left & right.
	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL); 
	mainSizer->Add(leftPanel, 1, wxEXPAND); 
	mainSizer->Add(rightPanel, 1, wxEXPAND);

	this->SetSizerAndFit(mainSizer); 
	return; 
}