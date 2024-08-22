#include "gameplay-page.h"

DefiGameWindow::DefiGameWindow(wxWindow* parent, Question question)
	: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
	this->SetSizeHints(wxSize(WIDTH, HEIGHT));

	wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxStaticBitmap* guessTextLine = new wxStaticBitmap(topPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/guess-defi-line-text.png"), wxBITMAP_TYPE_PNG));
	topPanel->SetBackgroundColour(WHITE);

	wxFont topFont;
	topFont.SetNativeFontInfoUserDesc(Pala30);

	wxTextCtrl* guessWord = new wxTextCtrl(topPanel, wxID_ANY, question.detail, wxDefaultPosition, wxDefaultSize, wxBORDER_DEFAULT | wxTE_READONLY);
	guessWord->SetFont(topFont);
	guessWord->HideNativeCaret();
	guessWord->SetBackgroundColour(WHITE);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(guessTextLine, 0, wxLEFT | wxTOP | wxBOTTOM | wxALIGN_BOTTOM | wxALIGN_LEFT, 60);
	topSizer->Add(guessWord, 1, wxALIGN_LEFT | wxALL, 60);
	topPanel->SetSizerAndFit(topSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(topPanel, 0, wxEXPAND);

	wxPanel* answerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	answerPanel->SetBackgroundColour(WHITE);

	wxBoxSizer* totalAnswerSizer = new wxBoxSizer(wxVERTICAL);
	wxFont answerFont;
	answerFont.SetNativeFontInfoUserDesc(Pala15);

	std::vector<wxRadioButton*> choiceButton;

	for (int i = 0; i < question.choices.size(); ++i) {
		wxRadioButton* button = new wxRadioButton(answerPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, i == 0 ? wxRB_GROUP : 0);
		wxTextCtrl* answer = new wxTextCtrl(answerPanel, wxID_ANY, question.choices[i], wxDefaultPosition, wxSize(-1, 80), wxTE_READONLY | wxTE_MULTILINE | wxBORDER_NONE | wxTE_NO_VSCROLL);
		answer->SetFont(answerFont);

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

	// Event handling
	submitAnsButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
		int selectedAnswer = -1;
		for (int i = 0; i < choiceButton.size(); ++i) {
			if (choiceButton[i]->GetValue()) {
				selectedAnswer = i;
				break;
			}
		}

		wxString message = (selectedAnswer == question.answer) ? "Correct!" : "False";
		wxMessageBox(message, "Result", wxOK | wxICON_INFORMATION);

		// Close the frame after the result is shown
		this->Close(true);

		//if (this->GetParent()) {
		//	this->GetParent()->Destroy();
		//}
		});
}


wordGameWindow::wordGameWindow(wxWindow* parent, wxString question, std::vector<wxString> answer) : wxWindow(parent, wxID_ANY)
{
	// Panel to load image
	wxPanel* quizPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	wxPanel* answerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	quizPanel->SetBackgroundColour(WHITE); 
	answerPanel->SetBackgroundColour(WHITE); 


	// Load image for topPanel
	
	wxStaticBitmap* markDisplay = new wxStaticBitmap(quizPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/mark-image.png"), wxBITMAP_TYPE_PNG));

	wxStaticBitmap* guesswordDisplay = new wxStaticBitmap(quizPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/guess-word-text.png"), wxBITMAP_TYPE_PNG)
		, wxDefaultPosition);

	wxTextCtrl* word = new wxTextCtrl(quizPanel, wxID_ANY, question,
		wxDefaultPosition, wxSize(1100, 88), wxTE_READONLY | wxBORDER_NONE | wxTE_MULTILINE | wxTE_NO_VSCROLL);
	word->SetBackgroundColour(wxColor(255, 255, 255)); 
	wxFont defiQuizFont; defiQuizFont.SetNativeFontInfoUserDesc("Palatino Linotype 20 WINDOWS-1252"); 
	word->SetFont(defiQuizFont);
	wxBoxSizer* firstSizer = new wxBoxSizer(wxVERTICAL); 
	firstSizer->Add(guesswordDisplay, 0, wxALIGN_LEFT | wxBOTTOM, 10);
	firstSizer->Add(word, 1, wxEXPAND | wxTOP, 10); 

	wxBoxSizer* secondSizer = new wxBoxSizer(wxHORIZONTAL); 
	secondSizer->Add(markDisplay, 0, wxALL, 20);
	secondSizer->Add(firstSizer, 1, wxALL, 20); 
	quizPanel->SetSizerAndFit(secondSizer); 
	
	wxBoxSizer* leftAnswerSizer = new wxBoxSizer(wxVERTICAL); 
	wxBoxSizer* rightAnswerSizer = new wxBoxSizer(wxVERTICAL); 
	wxBoxSizer* totalAnswerSizer = new wxBoxSizer(wxHORIZONTAL); 

	wxFont answerFont; answerFont.SetNativeFontInfoUserDesc("Palatino Linotype 30 WINDOWS-1252"); 
	
	for (int i = 0; i < answer.size(); ++i)
	{
		wxToggleButton* choice = new wxToggleButton(answerPanel, wxID_ANY, answer[i], wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT); 
		choice->SetFont(answerFont); 
		choice->SetBackgroundColour(colours[i]); 
		this -> answer.push_back(choice); 
		if (i < 2) leftAnswerSizer->Add(choice, 1, wxEXPAND | wxTOP | wxBOTTOM, 10);
		else rightAnswerSizer->Add(choice, 1, wxEXPAND | wxTOP | wxBOTTOM, 10); 
	}
	for (int i = 0; i < answer.size(); ++i)
	{
		(this->answer)[i]->Bind(wxEVT_TOGGLEBUTTON, &wordGameWindow::OnToggleButton, this); 
	}
	totalAnswerSizer->Add(leftAnswerSizer, 1, wxEXPAND| wxRIGHT | wxLEFT, 60); 
	totalAnswerSizer->Add(rightAnswerSizer, 1, wxEXPAND | wxRIGHT| wxLEFT, 60); 
	
	submitButton = new wxBitmapButton(answerPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/answer-button.png"), wxBITMAP_TYPE_PNG)); 
	wxBoxSizer* centerButton1 = new wxBoxSizer(wxVERTICAL); 
	wxBoxSizer* centerButton2 = new wxBoxSizer(wxHORIZONTAL); 
	centerButton1->Add(submitButton, 0, wxALIGN_CENTER); 
	centerButton2->Add(centerButton1, 1, wxALIGN_CENTER); 
	wxBoxSizer* answerSizer = new wxBoxSizer(wxVERTICAL); 
	answerSizer->Add(totalAnswerSizer, 3, wxEXPAND); 
	answerSizer->Add(centerButton2, 1, wxEXPAND); 
	answerPanel->SetSizerAndFit(answerSizer); 
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(quizPanel, 1, wxEXPAND); 
	mainSizer->Add(answerPanel, 4, wxEXPAND); 
	this->SetSizerAndFit(mainSizer); 
	return;
}

void wordGameWindow::OnToggleButton(wxCommandEvent& event)
{
	for (int i = 0; i < answer.size(); ++i)
	{
		
		if (answer[i]->GetBackgroundColour() == wxColor(224, 238, 249))
		{
			answer[i]->SetBackgroundColour(this->colours[i]);
			answer[i]->SetValue(false);
		}
	}

	wxToggleButton* is_selected = dynamic_cast<wxToggleButton*>(event.GetEventObject());
	is_selected->SetBackgroundColour(wxColor(224, 238, 249));
}
