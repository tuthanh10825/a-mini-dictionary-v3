#pragma once
#include <wx/wx.h>
#include <vector>
#include<wx/stc/stc.h>
#include <wx/tglbtn.h>
#include "properties.h"
#include <codecvt>
#include <locale>

struct Question {
	wxString detail;
	std::vector<wxString> choices;
	int answer;

	Question() {
		choices.clear();
		answer = 0;
	}

	Question(wxString detail, wxString ans) {
		this->detail = detail;
		choices.push_back(ans);
		this->answer = 0;
	}

	Question(wxString detail, wxString ans1, wxString ans2, wxString ans3, wxString ans4, int answer) {
		this->detail = detail;
		this->choices.push_back(ans1);
		this->choices.push_back(ans2);
		this->choices.push_back(ans3);
		this->choices.push_back(ans4);
		this->answer = 0;

		shuffle();
	}

	int random(int l, int r)
	{

		if (l > r) {
			std::swap(l, r);
		}
		return l + rand() % (r - l + 1);
	}

	void shuffle() {
		int randomPos = random(0, 3);
		this->answer = randomPos;

		std::swap(choices[0], choices[randomPos]);
	}
};

class DefiGameWindow : public wxWindow
{
public:
	DefiGameWindow(wxWindow* parent, Question question);
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
