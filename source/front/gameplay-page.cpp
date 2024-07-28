#include "gameplay-page.h"
#include "properties.h"

DefiGameWindow::DefiGameWindow(wxWindow* parent, wxString word, std::vector<wxString> answerList) : wxWindow(parent, wxID_ANY)
{
	
	this->answer = answerList; 
	SetSizeHints(wxSize(WIDTH, -1));
	wxPanel* topPanel = new wxPanel(this, wxID_ANY); 
	wxStaticBitmap* guessTextLine = new wxStaticBitmap(topPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/guess-defi-line-text.png"), wxBITMAP_TYPE_PNG)); 
	topPanel->SetBackgroundColour(WHITE); 
	wxFont topFont;
	topFont.SetNativeFontInfoUserDesc("Palatino Linotype 30 WINDOWS-1252");
	wxTextCtrl* guessWord = new wxTextCtrl(topPanel, wxID_ANY, word, wxDefaultPosition, wxDefaultSize, wxBORDER_DEFAULT | wxTE_READONLY); 
	guessWord->SetFont(topFont); 
	guessWord->HideNativeCaret(); 
	guessWord->SetBackgroundColour(WHITE); 
	wxBoxSizer * topSizer = new wxBoxSizer(wxHORIZONTAL); 
	topSizer->Add(guessTextLine, 0, wxLEFT | wxTOP | wxBOTTOM | wxALIGN_BOTTOM | wxALIGN_LEFT, 60); 
	topSizer->Add(guessWord, 1, wxALIGN_LEFT | wxALL, 60); 
	topPanel->SetSizerAndFit(topSizer); 
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 
	mainSizer->Add(topPanel, 0, wxEXPAND);

	wxPanel* answerPanel = new wxPanel(this, wxID_ANY); 
	answerPanel->SetBackgroundColour(WHITE); 
	wxBoxSizer* totalAnswerSizer = new wxBoxSizer(wxVERTICAL); 
	wxFont answerFont; answerFont.SetNativeFontInfoUserDesc("Palatino Linotype 15 WINDOWS-1252");
	for (int i = 0; i < answerList.size(); ++i)
	{
		wxRadioButton* button = new wxRadioButton(answerPanel, wxID_ANY, wxString(""), wxDefaultPosition, wxDefaultSize, i == 0 ? wxRB_GROUP : 0);
		wxTextCtrl* answer = new wxTextCtrl(answerPanel, wxID_ANY, wxString(answerList[i]), wxDefaultPosition, wxSize(-1, 80), wxTE_READONLY | wxTE_MULTILINE | wxBORDER_NONE| wxTE_NO_VSCROLL); 
		answer->SetFont(answerFont);
		answer->Layout();
		wxBoxSizer* answerSizer = new wxBoxSizer(wxHORIZONTAL); 
		answerSizer->Add(button, 0, wxLEFT, 60); 
		answerSizer->Add(answer, 1, wxRIGHT, 60); 
		totalAnswerSizer->Add(answerSizer, 1, wxEXPAND);
		choiceButton.push_back(button); 
	}
	wxBitmapButton* submitAnsButton = new wxBitmapButton(answerPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/answer-button.png"), wxBITMAP_TYPE_PNG)); 
	
	wxBoxSizer* submitSizer = new wxBoxSizer(wxHORIZONTAL); 
	submitSizer->Add(submitAnsButton, 0, wxALIGN_CENTER); 
	wxBoxSizer* centeringSubmitSizer = new wxBoxSizer(wxVERTICAL); 
	centeringSubmitSizer->Add(submitSizer, 1, wxALIGN_CENTER); 
	totalAnswerSizer->Add(centeringSubmitSizer, 1, wxEXPAND);
	answerPanel->SetSizerAndFit(totalAnswerSizer);
	
	
	mainSizer->Add(answerPanel, 1, wxEXPAND); 
	this->SetSizerAndFit(mainSizer); 
}
