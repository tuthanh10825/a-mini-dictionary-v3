#pragma once
#include "wx/wx.h"
#include "gameplay-page.h"
#include "properties.h"
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
};