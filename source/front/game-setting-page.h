#include "wx/wx.h"


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

	void OnChooseWordClicked(wxCommandEvent&); 
	void OnChooseDefiClicked(wxCommandEvent&); 
	void OnChooseEEClicked(wxCommandEvent&); 
	void OnChooseEVClicked(wxCommandEvent&);
	void OnChooseVEClicked(wxCommandEvent&);
	void OnChooseEmoticonClicked(wxCommandEvent&);
	void OnChooseSlangClicked(wxCommandEvent&);
	void OnFiniteClicked(wxCommandEvent&); 
	void OnInfiniteClicked(wxCommandEvent&); 

};