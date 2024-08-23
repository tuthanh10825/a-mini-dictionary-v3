#pragma once
#include <wx/wx.h>
#include <vector>
#include<wx/stc/stc.h>
#include <wx/tglbtn.h>
#include "properties.h"
#include <codecvt>
#include <locale>
#include "tst.h"
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

class DefiGameWindow : public wxFrame
{
public:
	DefiGameWindow(wxWindow* parent, TST* clist);
	
	wxTextCtrl* answer[4]; 
	wxTextCtrl* guessWord; 
	std::vector<wxRadioButton*> choiceButton;
	bool IsCorrect = true; 

	int numberOfQues = 0;
	int currentNumber = 0;
	TST* list = nullptr;
	Question ques; 

	void OnSubmitButtonClicked(wxCommandEvent&); 
	void SetVal(Question ques);
};

class wordGameWindow : public wxFrame
{
public: 
	wordGameWindow(wxWindow*, TST* clist); 
	std::vector<wxToggleButton*> answer; 
	wxBitmapButton* submitButton;
	wxTextCtrl* word; 
	TST* list = nullptr; 
	Question ques; 
	int numberOfQues = 0; 
	int currentNumber = 0;
	wxColour colours[4] = {
	   wxColour(236, 178, 179),
	   wxColour(178, 236, 179),
	   wxColour(187, 188, 246),
	   wxColour(247, 247, 184)
	};
	void OnSubmitBtnClicked(wxCommandEvent&); 
	void OnToggleButton(wxCommandEvent&); 
	void SetVal(Question ques); 
};
