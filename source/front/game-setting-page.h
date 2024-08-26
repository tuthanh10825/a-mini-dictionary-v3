#pragma once
#include "wx/wx.h"
#include "gameplay-page.h"
#include <wx/spinctrl.h>
#include "Globals.h"

class GameSettingPage : public wxWindow
{
public: 
	GameSettingPage(wxWindow*);
	wxCheckBox* chooseWord; 
	wxCheckBox* chooseDefi; 
	wxCheckBox* chooseEngEng;
	wxCheckBox* chooseEngVie;
	wxCheckBox* chooseVieEng;
	wxCheckBox* chooseEmoticon;
	wxCheckBox* chooseSlang;
	wxCheckBox* finite;
	wxSpinCtrl* value;
	wxCheckBox* infinite;

	TST* list;

	void OnChooseWordClicked(wxCommandEvent&); 
	void OnChooseDefiClicked(wxCommandEvent&); 
	void OnChooseEEClicked(wxCommandEvent&); 
	void OnChooseEVClicked(wxCommandEvent&);
	void OnChooseVEClicked(wxCommandEvent&);
	void OnChooseEmoticonClicked(wxCommandEvent&);
	void OnChooseSlangClicked(wxCommandEvent&);
	void OnFiniteClicked(wxCommandEvent&); 
	void OnInfiniteClicked(wxCommandEvent&); 

	void OnPlayButtonClicked(wxCommandEvent&); 

	void FlipColor(); 
private: 
	
	wxPanel* logoPanel = new wxPanel(this, wxID_ANY);
	wxStaticBitmap* logo = new wxStaticBitmap(logoPanel, wxID_ANY, wxBitmap("assets/game/setting/logo.png", wxBITMAP_TYPE_PNG)); 

	wxPanel* chooseGamePanel = new wxPanel(this, wxID_ANY); 
	wxPanel* choicePanelGame = new wxPanel(this, wxID_ANY);
	wxStaticBitmap* chooseGameText = new wxStaticBitmap(chooseGamePanel, wxID_ANY, wxBitmap("assets/game/setting/choose-game-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseWordText = new wxStaticBitmap(choicePanelGame, wxID_ANY, wxBitmap("assets/game/setting/choose-word-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseDefiText = new wxStaticBitmap(choicePanelGame, wxID_ANY, wxBitmap("assets/game/setting/choose-defi-text.png", wxBITMAP_TYPE_PNG));
	
	wxPanel* chooseLangPanel = new wxPanel(this, wxID_ANY); //4
	wxPanel* choicePanelLang = new wxPanel(this, wxID_ANY);
	wxStaticBitmap* chooseLangText = new wxStaticBitmap(chooseLangPanel, wxID_ANY, wxBitmap("assets/game/setting/choose-lang-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseEngEngText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-ee-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseEngVieText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-ev-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseVieEngText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-ve-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseEmoticonText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-emo-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* chooseSlangText = new wxStaticBitmap(choicePanelLang, wxID_ANY, wxBitmap("assets/game/setting/choose-slang-text.png", wxBITMAP_TYPE_PNG));
	
	wxPanel* number = new wxPanel(this, wxID_ANY);
	wxStaticBitmap* numberText = new wxStaticBitmap(number, wxID_ANY, wxBitmap("assets/game/setting/number-text.png", wxBITMAP_TYPE_PNG));
	wxStaticBitmap* infiniteText = new wxStaticBitmap(number, wxID_ANY, wxBitmap("assets/game/setting/endlessly-text.png", wxBITMAP_TYPE_PNG));

	wxPanel* selectPlayPanel = new wxPanel(this, wxID_ANY);
	wxBitmapButton* selectPlay = new wxBitmapButton(selectPlayPanel, wxID_ANY, wxBitmap("assets/game/setting/select-play.png", wxBITMAP_TYPE_PNG));

};