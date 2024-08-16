#pragma once
#include <wx/wx.h>
#include <vector>
#include<wx/stc/stc.h>
#include <wx/tglbtn.h>
class DefiGameWindow : public wxWindow
{
public:
	DefiGameWindow(wxWindow*, wxString, std::vector<wxString>); 
	std::vector<wxString> answer; 
	std::vector<wxRadioButton*> choiceButton; 
	
	int correctAns = 0; 
	

};

class wordGameWindow : public wxWindow
{
public: 
	wordGameWindow(wxWindow*, wxString, std::vector<wxString>); 
	std::vector<wxToggleButton*> answer; 
	int correctAns = 0;
	wxBitmapButton* submitButton;
	wxColour colours[4] = {
	   wxColour(236, 178, 179),
	   wxColour(178, 236, 179),
	   wxColour(187, 188, 246),
	   wxColour(247, 247, 184)
	};
	void OnToggleButton(wxCommandEvent&); 
};
