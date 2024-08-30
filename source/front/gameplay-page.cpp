#include "gameplay-page.h"
#include "uni_algo/all.h"
#include "TST.h"
#include "Globals.h"
DefiGameWindow::DefiGameWindow(wxWindow* parent, TST* clist)
	: wxFrame(parent, wxID_ANY, "Play!", wxDefaultPosition, wxDefaultSize), list(clist)
{
	std::string s = LIGHTMODE ? "" : "1"; 
	this->SetSizeHints(wxSize(WIDTH, HEIGHT));

	wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	wxStaticBitmap* guessTextLine = new wxStaticBitmap(topPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/guess-defi-line-text" + s +".png"), wxBITMAP_TYPE_PNG));
	topPanel->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);

	wxFont topFont;
	topFont.SetNativeFontInfoUserDesc(Pala30);

	guessWord = new wxTextCtrl(topPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBORDER_DEFAULT | wxTE_READONLY);
	guessWord->SetFont(topFont);
	guessWord->HideNativeCaret();
	guessWord->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);
	guessWord->SetForegroundColour(LIGHTMODE ? BLACK : WHITE);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(guessTextLine, 0, wxLEFT | wxTOP | wxBOTTOM | wxALIGN_BOTTOM | wxALIGN_LEFT, 60);
	topSizer->Add(guessWord, 1, wxALIGN_LEFT | wxALL, 60);
	topPanel->SetSizerAndFit(topSizer);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(topPanel, 0, wxEXPAND);

	wxPanel* answerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	answerPanel->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);

	wxBoxSizer* totalAnswerSizer = new wxBoxSizer(wxVERTICAL);
	wxFont answerFont;
	answerFont.SetNativeFontInfoUserDesc(Pala15);
	for (int i = 0; i < 4; ++i) {
		wxRadioButton* button = new wxRadioButton(answerPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, i == 0 ? wxRB_GROUP : 0);
		answer[i] = new wxTextCtrl(answerPanel, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 175), wxTE_READONLY | wxTE_MULTILINE);
		answer[i]->SetFont(answerFont);
		answer[i]->SetForegroundColour(LIGHTMODE ? WHITE : BLACK);
		answer[i]->SetBackgroundColour(LIGHTMODE ? BLACK : WHITE);
		wxBoxSizer* answerSizer = new wxBoxSizer(wxHORIZONTAL);
		answerSizer->Add(button, 0, wxLEFT, 60);
		answerSizer->Add(answer[i], 1, wxRIGHT, 60);


		totalAnswerSizer->Add(answerSizer, 1, wxEXPAND);
		choiceButton.push_back(button);
	}

	wxBitmapButton* submitAnsButton = new wxBitmapButton(answerPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/answer-button.png"), wxBITMAP_TYPE_PNG));

	submitAnsButton->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);
	wxBoxSizer* submitSizer = new wxBoxSizer(wxHORIZONTAL);
	submitSizer->Add(submitAnsButton, 0, wxALIGN_CENTER);
	wxBoxSizer* centeringSubmitSizer = new wxBoxSizer(wxVERTICAL);
	centeringSubmitSizer->Add(submitSizer, 1, wxALIGN_CENTER);
	totalAnswerSizer->Add(centeringSubmitSizer, 1, wxEXPAND);
	answerPanel->SetSizerAndFit(totalAnswerSizer);

	mainSizer->Add(answerPanel, 1, wxEXPAND);
	this->SetSizerAndFit(mainSizer);
	submitAnsButton->Bind(wxEVT_BUTTON, &DefiGameWindow::OnSubmitButtonClicked, this); 
	std::pair<std::u32string, std::string> ans = list->random();
	wxString ques = wxString(una::utf32to16(ans.first));
	wxString ans1 = wxString::FromUTF8(ans.second);
	wxString ans2 = wxString::FromUTF8(list->random().second);
	wxString ans3 = wxString::FromUTF8(list->random().second);
	wxString ans4 = wxString::FromUTF8(list->random().second);
	this->SetVal(Question(ques, ans1, ans2, ans3, ans4, 1));

}
void DefiGameWindow::OnSubmitButtonClicked(wxCommandEvent&)
{
	for (int i = 0; i < 4; ++i)
	{
		if (choiceButton[i]->GetValue())
			this->IsCorrect = (i == ques.answer);
	}
	if (!this->IsCorrect)
	{
		wxMessageBox("You lose!!!");
		this->Close(true);
	}
	else if (numberOfQues >= 0)
	{
		if (++currentNumber == numberOfQues)
		{
			wxMessageBox("You win!!!");
			this->Close(true);
			return;
		}
		else
		{
			std::pair<std::u32string, std::string> ans = list->random();
			wxString ques = wxString(una::utf32to16(ans.first));
			wxString ans1 = wxString::FromUTF8(ans.second);
			wxString ans2 = wxString::FromUTF8(list->random().second);
			wxString ans3 = wxString::FromUTF8(list->random().second);
			wxString ans4 = wxString::FromUTF8(list->random().second);
			this->SetVal(Question(ques, ans1, ans2, ans3, ans4, 1));
			
		}
	}
	else
	{
		std::pair<std::u32string, std::string> ans = list->random();
		wxString ques = wxString(una::utf32to16(ans.first));
		wxString ans1 = wxString::FromUTF8(ans.second);
		wxString ans2 = wxString::FromUTF8(list->random().second);
		wxString ans3 = wxString::FromUTF8(list->random().second);
		wxString ans4 = wxString::FromUTF8(list->random().second);
		this->SetVal(Question(ques, ans1, ans2, ans3, ans4, 1));
	}
	
}
void DefiGameWindow::SetVal(Question ques)
{
	this->ques = ques; 
	for (int i = 0; i < 4; ++i)
	{
		answer[i]->SetValue(ques.choices[i]);
		answer[i]->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);
		answer[i]->SetForegroundColour(LIGHTMODE ? BLACK : WHITE);
	}

	guessWord->SetValue(ques.detail);
}

wordGameWindow::wordGameWindow(wxWindow* parent, TST* clist) : wxFrame(parent, wxID_ANY, "Play"), list(clist)
{
	// Panel to load image
	wxPanel* quizPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	wxPanel* answerPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
	quizPanel->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);
	answerPanel->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);


	// Load image for topPanel
	std::string s = LIGHTMODE ? "" : "1";
	wxStaticBitmap* markDisplay = new wxStaticBitmap(quizPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/mark-image" + s  +  ".png"), wxBITMAP_TYPE_PNG));

	wxStaticBitmap* guesswordDisplay = new wxStaticBitmap(quizPanel, wxID_ANY, wxBitmap(wxString("assets/game/play/guess-word-text" + s + ".png"), wxBITMAP_TYPE_PNG)
		, wxDefaultPosition);

	word = new wxTextCtrl(quizPanel, wxID_ANY, "",
		wxDefaultPosition, wxSize(1100, 88), wxTE_READONLY | wxBORDER_NONE | wxTE_MULTILINE | wxTE_NO_VSCROLL);
	word->SetBackgroundColour(LIGHTMODE ? WHITE : BLACK);
	word->SetForegroundColour(LIGHTMODE ? BLACK : WHITE); 
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
	
	for (int i = 0; i < 4; ++i)
	{
		wxToggleButton* choice = new wxToggleButton(answerPanel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
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
	submitButton->Bind(wxEVT_BUTTON, &wordGameWindow::OnSubmitBtnClicked, this); 

	std::pair<std::u32string, std::string> ans = list->random();
	wxString ques = wxString(una::utf8to16(ans.second));
	wxString ans1 = wxString(una::utf32to16(ans.first));
	wxString ans2 = wxString(una::utf32to16(list->random().first));
	wxString ans3 = wxString(una::utf32to16(list->random().first));
	wxString ans4 = wxString(una::utf32to16(list->random().first));
	this->SetVal(Question(ques, ans1, ans2, ans3, ans4, 1));

	return;
	
}
/*
BaseFrame::BaseFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition) {

	wxInitAllImageHandlers();
	LoadHeader();
	workingPage = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT));


	homePage = new HomePage(workingPage);
	workingPage->AddPage(homePage, wxString("Homepage"));


	searchPage = new SearchPage(workingPage);
	workingPage->AddPage(searchPage, wxString("Searchpage"));

	gameSettingPage = new GameSettingPage(workingPage);
	workingPage->AddPage(gameSettingPage, wxString("GameSettingpage"));

	moreWindow = new MoreWindow(workingPage);
	workingPage->AddPage(moreWindow, wxString("more"));

	historyPage = new ListWindow(workingPage, 0);
	workingPage->AddPage(historyPage, wxString("History"));

	favouritePage = new ListWindow(workingPage, 1);
	workingPage->AddPage(favouritePage, wxString("Favourite"));

	addpage = new AddWindow(workingPage);
	workingPage->AddPage(addpage, wxString("Add"));
	addpage->cancelbutton->Bind(wxEVT_BUTTON, &BaseFrame::OnCancelBtnClicked, this);

	LoadNavigation();
	mainSizer->Add(workingPage, 1, wxEXPAND);
	loadFooter();

	this->homePage->quizButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {this->workingPage->ChangeSelection(2); });
	this->homePage->favorButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {this->workingPage->ChangeSelection(5); });
	this->homePage->randomButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& evt)
		{
			this->searchPage->OnRandomBtnClicked(evt);
			this->workingPage->ChangeSelection(1);
		});
	this->searchPage->box->addButton->Bind(wxEVT_BUTTON, &BaseFrame::OnAddBtnClicked, this);
	this->moreWindow->darkmodeButton->Bind(wxEVT_BUTTON, &BaseFrame::OnFlipColor, this);
	this->SetSizerAndFit(mainSizer);
	// 155 x 37

}

*/
void wordGameWindow::OnSubmitBtnClicked(wxCommandEvent&)
{
	bool isCorrect = false; 
	for (int i = 0; i < 4; ++i)
	{
		if (answer[i]->GetValue())
		{
			isCorrect = (ques.answer == i); 
		}
	}
	if (!isCorrect)
	{

		wxMessageBox("You lose!!!");
		this->Close(true);
		return; 

	}
	else if (numberOfQues >= 0)
	{
		if (++currentNumber == numberOfQues)
		{
			wxMessageBox("You win!!!");
			this->Close(true);
			return;
		}
		else
		{
			std::pair<std::u32string, std::string> ans = list->random();
			wxString ques = wxString(una::utf8to16(ans.second));
			wxString ans1 = wxString(una::utf32to16(ans.first));
			wxString ans2 = wxString(una::utf32to16(list->random().first));
			wxString ans3 = wxString(una::utf32to16(list->random().first));
			wxString ans4 = wxString(una::utf32to16(list->random().first));
			this->SetVal(Question(ques, ans1, ans2, ans3, ans4, 1));

		}
	}
	else
	{
		std::pair<std::u32string, std::string> ans = list->random();
		wxString ques = wxString(una::utf8to16(ans.second));
		wxString ans1 = wxString(una::utf32to16(ans.first));
		wxString ans2 = wxString(una::utf32to16(list->random().first));
		wxString ans3 = wxString(una::utf32to16(list->random().first));
		wxString ans4 = wxString(una::utf32to16(list->random().first));
		this->SetVal(Question(ques, ans1, ans2, ans3, ans4, 1));

	}
	
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

void wordGameWindow::SetVal(Question ques)
{
	for (int i = 0; i < 4; ++i)
	{
		answer[i]->SetLabelText(ques.choices[i]); 
	}

	ques.detail.erase(ques.detail.begin()); 
	word->SetValue(ques.detail); 
	this->ques = ques; 

}
