#include "game-setting-page.h"
#include "properties.h"
#include <wx/spinctrl.h>
GameSettingPage::GameSettingPage(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	wxPanel* logoPanel = new wxPanel(this, wxID_ANY); //1
	logoPanel->SetBackgroundColour(WHITE); 
	wxStaticBitmap* logo = new wxStaticBitmap(logoPanel, wxID_ANY, wxBitmap("assets/game/setting/logo.png", wxBITMAP_TYPE_PNG)); 
	wxBoxSizer* centerVert = new wxBoxSizer(wxVERTICAL); 
	centerVert->Add(logo, 0, wxALIGN_CENTER); 
	wxBoxSizer* centerHori = new wxBoxSizer(wxHORIZONTAL); 
	centerHori->Add(centerVert, 1, wxALIGN_CENTER); 
	logoPanel->SetSizerAndFit(centerHori); 

	wxPanel* chooseGamePanel = new wxPanel(this, wxID_ANY); //2
	chooseGamePanel->SetBackgroundColour(WHITE);
	wxStaticBitmap* chooseGameText = new wxStaticBitmap(chooseGamePanel, wxID_ANY, wxBitmap("assets/game/setting/choose-game-text.png", wxBITMAP_TYPE_PNG));
	
	
	wxBoxSizer* centerChooseGameHori = new wxBoxSizer(wxHORIZONTAL); 
	centerChooseGameHori->Add(chooseGameText, 1, wxALIGN_BOTTOM);
	wxBoxSizer* centerChooseGameVert = new wxBoxSizer(wxVERTICAL); 
	centerChooseGameVert->Add(centerChooseGameHori, 0, wxALIGN_LEFT);
	chooseGamePanel->SetSizerAndFit(centerChooseGameVert);

	wxPanel* choicePanelGame = new wxPanel(this, wxID_ANY); 
	choicePanelGame->SetBackgroundColour(WHITE); 
	
	chooseWord = new wxCheckBox(choicePanelGame, wxID_ANY, wxEmptyString); 
	wxStaticBitmap* chooseWordText = new wxStaticBitmap(choicePanelGame, wxID_ANY, wxBitmap("assets/game/setting/choose-word-text.png", wxBITMAP_TYPE_PNG)); 
	wxBoxSizer* chooseWordSizer = new wxBoxSizer(wxHORIZONTAL); 
	chooseWordSizer->Add(chooseWord, 0);
	chooseWordSizer->Add(chooseWordText, 0); 

	chooseDefi = new wxCheckBox(choicePanelGame, wxID_ANY, wxEmptyString);
	wxStaticBitmap* chooseDefiText = new wxStaticBitmap(choicePanelGame, wxID_ANY, wxBitmap("assets/game/setting/choose-defi-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* chooseDefiSizer = new wxBoxSizer(wxHORIZONTAL);
	chooseDefiSizer->Add(chooseDefi, 0);
	chooseDefiSizer->Add(chooseDefiText, 0);

	chooseWord->SetValue(true); 
	chooseWord->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseWordClicked, this);
	chooseDefi->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseDefiClicked, this);
	
	wxBoxSizer* adjustWord = new wxBoxSizer(wxVERTICAL); 
	adjustWord->Add(chooseWordSizer, 0, wxALIGN_CENTER);

	wxBoxSizer* adjustMeaning = new wxBoxSizer(wxVERTICAL); 
	adjustMeaning->Add(chooseDefiSizer, 0, wxALIGN_CENTER); 

	wxBoxSizer* chooseGameSizer = new wxBoxSizer(wxHORIZONTAL); //3
	chooseGameSizer->Add(adjustWord, 1, wxALIGN_CENTER); 
	chooseGameSizer->Add(adjustMeaning, 1, wxALIGN_CENTER); 
	choicePanelGame->SetSizerAndFit(chooseGameSizer); 
	

	wxPanel* chooseLangPanel = new wxPanel(this, wxID_ANY); //4
	chooseLangPanel->SetBackgroundColour(WHITE); 
	wxStaticBitmap* chooseLangText = new wxStaticBitmap(chooseLangPanel, wxID_ANY, wxBitmap("assets/game/setting/choose-lang-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* centerChooseLangHori = new wxBoxSizer(wxHORIZONTAL);
	centerChooseLangHori->Add(chooseLangText, 0);
	wxBoxSizer* centerChooseLangVert = new wxBoxSizer(wxVERTICAL);
	centerChooseLangVert->Add(centerChooseLangHori, 0, wxALIGN_LEFT);
	chooseLangPanel->SetSizerAndFit(centerChooseLangVert);

	wxPanel* choicePanelLang = new wxPanel(this, wxID_ANY); 
	choicePanelLang->SetBackgroundColour(WHITE); 

	chooseEngEng = new wxCheckBox(choicePanelLang, wxID_ANY, wxEmptyString);
	wxStaticBitmap* chooseEngEngText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-ee-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* chooseEngEngSizer = new wxBoxSizer(wxHORIZONTAL);
	chooseEngEngSizer->Add(chooseEngEng, 0);
	chooseEngEngSizer->Add(chooseEngEngText, 0);
	chooseEngEng->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseEEClicked, this); 

	chooseEngVie = new wxCheckBox(choicePanelLang, wxID_ANY, wxEmptyString);
	wxStaticBitmap* chooseEngVieText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-ev-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* chooseEngVieSizer = new wxBoxSizer(wxHORIZONTAL);
	chooseEngVieSizer->Add(chooseEngVie, 0);
	chooseEngVieSizer->Add(chooseEngVieText, 0);
	chooseEngVie->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseEVClicked, this); 

	chooseVieEng = new wxCheckBox(choicePanelLang, wxID_ANY, wxEmptyString);
	wxStaticBitmap* chooseVieEngText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-ve-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* chooseVieEngSizer = new wxBoxSizer(wxHORIZONTAL);
	chooseVieEngSizer->Add(chooseVieEng, 0);
	chooseVieEngSizer->Add(chooseVieEngText, 0);
	chooseVieEng->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseVEClicked, this); 

	chooseEmoticon = new wxCheckBox(choicePanelLang, wxID_ANY, wxEmptyString);
	wxStaticBitmap* chooseEmoticonText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-emo-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* chooseEmoticonSizer = new wxBoxSizer(wxHORIZONTAL);
	chooseEmoticonSizer->Add(chooseEmoticon, 0);
	chooseEmoticonSizer->Add(chooseEmoticonText, 0);
	chooseEmoticon->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseEmoticonClicked, this);

	chooseSlang = new wxCheckBox(choicePanelLang, wxID_ANY, wxEmptyString);
	wxStaticBitmap* chooseSlangText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-slang-text.png", wxBITMAP_TYPE_PNG));
	wxBoxSizer* chooseSlangSizer = new wxBoxSizer(wxHORIZONTAL);
	chooseSlangSizer->Add(chooseSlang, 0);
	chooseSlangSizer->Add(chooseSlangText, 0);
	chooseSlang->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnChooseSlangClicked, this);

	chooseEngEng->SetValue(true);

	wxBoxSizer* adjustEE = new wxBoxSizer(wxVERTICAL); 
	adjustEE->Add(chooseEngEngSizer, 0, wxALIGN_CENTER); 
	
	wxBoxSizer* adjustEV = new wxBoxSizer(wxVERTICAL); 
	adjustEV->Add(chooseEngVieSizer, 0, wxALIGN_CENTER); 

	wxBoxSizer* adjustVE = new wxBoxSizer(wxVERTICAL); 
	adjustVE->Add(chooseVieEngSizer, 0, wxALIGN_CENTER); 

	wxBoxSizer* chooseLangSizer1 = new wxBoxSizer(wxHORIZONTAL); //3
	chooseLangSizer1->Add(adjustEE, 1, wxALIGN_CENTER);
	chooseLangSizer1->Add(adjustEV, 1, wxALIGN_CENTER);
	chooseLangSizer1->Add(adjustVE, 1, wxALIGN_CENTER); 


	wxBoxSizer* adjustEmo = new wxBoxSizer(wxVERTICAL);
	adjustEmo->Add(chooseEmoticonSizer, 0, wxALIGN_CENTER);

	wxBoxSizer* adjustSlang = new wxBoxSizer(wxVERTICAL);
	adjustSlang->Add(chooseSlangSizer, 0, wxALIGN_CENTER);

	wxBoxSizer* chooseLangSizer2 = new wxBoxSizer(wxHORIZONTAL); 
	chooseLangSizer2->Add(adjustEmo, 1, wxALIGN_CENTER); 
	chooseLangSizer2->Add(adjustSlang, 1, wxALIGN_CENTER); 

	wxBoxSizer* totalChooseLangSizer = new wxBoxSizer(wxVERTICAL); 
	totalChooseLangSizer->Add(chooseLangSizer1, 1, wxEXPAND); 
	totalChooseLangSizer->Add(chooseLangSizer2, 0, wxEXPAND); 
	
	choicePanelLang->SetSizerAndFit(totalChooseLangSizer); 

	wxPanel* selectPlayPanel = new wxPanel(this, wxID_ANY); 
	selectPlayPanel->SetBackgroundColour(WHITE); 
	wxBitmapButton* selectPlay = new wxBitmapButton(selectPlayPanel, wxID_ANY, wxBitmap("assets/game/setting/select-play.png", wxBITMAP_TYPE_PNG)); 
	wxBoxSizer* centerPlaySizerHori = new wxBoxSizer(wxHORIZONTAL); 
	centerPlaySizerHori->Add(selectPlay, 0, wxALIGN_CENTER); 
	wxBoxSizer* centerPlaySizerVert = new wxBoxSizer(wxVERTICAL); 
	centerPlaySizerVert->Add(centerPlaySizerHori, 1, wxALIGN_CENTER); 
	selectPlayPanel->SetSizerAndFit(centerPlaySizerVert); 

	wxPanel* number = new wxPanel(this, wxID_ANY); 

	
	wxStaticBitmap* numberText = new wxStaticBitmap(number, wxID_ANY, wxBitmap("assets/game/setting/number-text.png", wxBITMAP_TYPE_PNG)); 
	
	finite = new wxCheckBox(number, wxID_ANY, "");
	value = new wxSpinCtrl(number, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 16384L, 1, 100, 1); 
	wxBoxSizer* finiteSizer = new wxBoxSizer(wxHORIZONTAL); 
	finiteSizer->Add(finite, 0);
	finiteSizer->Add(value, 1); 
	finite->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnFiniteClicked, this); 
	finite->SetValue(true); 

	infinite = new wxCheckBox(number, wxID_ANY, ""); 
	wxStaticBitmap* infiniteText = new wxStaticBitmap(number, wxID_ANY, wxBitmap("assets/game/setting/endlessly-text.png", wxBITMAP_TYPE_PNG)); 
	wxBoxSizer* infiniteSizer = new wxBoxSizer(wxHORIZONTAL); 
	infiniteSizer->Add(infinite, 0); 
	infiniteSizer->Add(infiniteText, 1); 
	infinite->Bind(wxEVT_CHECKBOX, &GameSettingPage::OnInfiniteClicked, this); 

	wxBoxSizer* adjustFiniteSizer = new wxBoxSizer(wxVERTICAL);
	adjustFiniteSizer->Add(finiteSizer, 1 ,wxALIGN_CENTER); 

	wxBoxSizer* adjustInfiniteSizer = new wxBoxSizer(wxVERTICAL); 
	adjustInfiniteSizer->Add(infiniteSizer, 1, wxALIGN_CENTER); 

	wxBoxSizer* mainNumberSizer = new wxBoxSizer(wxHORIZONTAL); 
	mainNumberSizer->Add(numberText, 0, wxALL, 20); 
	mainNumberSizer->Add(adjustFiniteSizer, 1, wxALL, 20); 
	mainNumberSizer->Add(adjustInfiniteSizer,1, wxALL, 20); 

	number->SetSizerAndFit(mainNumberSizer); 
	number->SetBackgroundColour(WHITE); 

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 
	mainSizer->Add(logoPanel, 1, wxEXPAND); 
	mainSizer->Add(chooseGamePanel, 0, wxEXPAND); 
	mainSizer->Add(choicePanelGame, 1, wxEXPAND); 
	mainSizer->Add(chooseLangPanel, 0, wxEXPAND); 
	mainSizer->Add(choicePanelLang, 1, wxEXPAND); 
	mainSizer->Add(number, 0, wxEXPAND); 
	mainSizer->Add(selectPlayPanel, 1, wxEXPAND); 

	this->SetSizerAndFit(mainSizer); 
}

void GameSettingPage::OnChooseWordClicked(wxCommandEvent&)
{
	chooseDefi->SetValue(false); 
}

void GameSettingPage::OnChooseDefiClicked(wxCommandEvent&)
{
	chooseWord->SetValue(false); 
}

void GameSettingPage::OnChooseEEClicked(wxCommandEvent&)
{
	chooseEngVie->SetValue(false);
	chooseVieEng->SetValue(false); 
	chooseSlang->SetValue(false); 
	chooseEmoticon->SetValue(false); 

}

void GameSettingPage::OnChooseEVClicked(wxCommandEvent&)
{
	chooseEngEng->SetValue(false);
	chooseVieEng->SetValue(false);
	chooseSlang->SetValue(false);
	chooseEmoticon->SetValue(false);
}

void GameSettingPage::OnChooseVEClicked(wxCommandEvent&)
{
	chooseEngVie->SetValue(false);
	chooseEngEng->SetValue(false);
	chooseSlang->SetValue(false);
	chooseEmoticon->SetValue(false);
}
void GameSettingPage::OnChooseEmoticonClicked(wxCommandEvent&)
{
	chooseEngVie->SetValue(false);
	chooseVieEng->SetValue(false);
	chooseSlang->SetValue(false);
	chooseEngEng->SetValue(false);
}

void GameSettingPage::OnChooseSlangClicked(wxCommandEvent&)
{
	chooseEngVie->SetValue(false);
	chooseVieEng->SetValue(false);
	chooseEngEng->SetValue(false);
	chooseEmoticon->SetValue(false);
}

void GameSettingPage::OnFiniteClicked(wxCommandEvent&)
{
	infinite->SetValue(false); 
}

void GameSettingPage::OnInfiniteClicked(wxCommandEvent&)
{
	finite->SetValue(false); 
}
