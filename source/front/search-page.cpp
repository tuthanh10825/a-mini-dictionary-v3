﻿#include "search-page.h"
#include <sstream>
searchBox::searchBox(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	wxFont::AddPrivateFont("fonts/pala.ttf"); 
	wxFont pala(25, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
	language->SetFont(pala);  wordOrDefi->SetFont(pala); 

	language->Append(wxString("ENG/ENG")); 
	language->Append(wxString("ENG/VIE")); 
	language->Append(wxString("VIE/ENG")); 
	language->Append(wxString("SLANG"));
	language->Append(wxString("EMOTICON"));

	language->SetSelection(1); 

	wordOrDefi->Append(wxString("KEYWORD")); 
	//wordOrDefi->Append(wxString("DEFINITION")); 
	wordOrDefi->SetSelection(0); 

	 
	findBox->SetFont(pala);
	
	searchButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/search-button.png", wxBITMAP_TYPE_PNG));
	randomButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/random-button.png", wxBITMAP_TYPE_PNG));
	addButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/add-button.png", wxBITMAP_TYPE_PNG)); 
	resetButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/reset-button.png", wxBITMAP_TYPE_PNG));

	

	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL); 
	mainSizer->Add(language, 1, wxEXPAND); 
	mainSizer->Add(wordOrDefi, 1, wxEXPAND);
	
	mainSizer->Add(findBox, 2, wxEXPAND); 

	wxBoxSizer* subSizer = new wxBoxSizer(wxHORIZONTAL); 
	subSizer->Add(searchButton, 1, wxEXPAND);
	subSizer->Add(randomButton, 1, wxEXPAND); 
	subSizer->Add(addButton, 1, wxEXPAND); 
	subSizer->Add(resetButton, 1, wxEXPAND);
	mainSizer->Add(subSizer, 1, wxEXPAND); 
	this->SetSizerAndFit(mainSizer); 

	
	return; 
}



resPage::resPage(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	wxFont::AddPrivateFont(wxString("./fonts/pala.ttf"));
	font.SetFaceName("Palatino Linotype"); font.SetPointSize(20); 
	resWord->SetFont(font); 
	editButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxString("assets/result/edit-button.png"), wxBITMAP_TYPE_PNG));
	favorButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxString("assets/result/favorite-button.png"), wxBITMAP_TYPE_PNG));
	favorButton->Bind(wxEVT_BUTTON, &resPage::OnFavouriteBtnClicked, this);
	removeButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxString("assets/result/remove-button.png"), wxBITMAP_TYPE_PNG));

	wxBoxSizer* subSizer = new wxBoxSizer(wxVERTICAL); 
	subSizer->Add(editButton, 1, wxEXPAND); 
	subSizer->Add(favorButton, 1, wxEXPAND); 
	subSizer->Add(removeButton, 1, wxEXPAND); 


	wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL); 
	mainSizer->Add(subSizer, 0, wxEXPAND); 
	mainSizer->Add(resWord, 1, wxEXPAND);
	this->SetSizerAndFit(mainSizer); 

}

void resPage::addingString(wxString total)
{
	resWord->SetValue(total);
}

void resPage::clearScreen()
{
	resWord->Clear();
}


void resPage::OnFavouriteBtnClicked(wxCommandEvent&) {
	vector<word> temp = dataHisto;
	dataFav.push_back(temp.back());
	temp.pop_back();
	while (!temp.empty()) {
		if (temp.back().word != dataFav.back().word) return;
		dataFav.push_back(temp.back());
		temp.pop_back();
	}
}

SearchPage::SearchPage(wxWindow* parent) : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT))
{
	// Load Eng-Viet dataset
	if (!EVtree->isLoaded())
		EVtree->loadWord(EVDATASET);

	list = EVtree;

	wxPanel* searchPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* searchBarSizer = new wxBoxSizer(wxHORIZONTAL);
	searchPanel->SetBackgroundColour(BLUEBLACK);

	box = new searchBox(searchPanel);
	searchBarSizer->Add(box, 1, wxEXPAND | wxALL, 15);
	searchPanel->SetSizerAndFit(searchBarSizer);
	box->findBox->Bind(wxEVT_COMBOBOX_DROPDOWN, [this](wxCommandEvent&)
		{
			this->box->isDropdown = true;
		});
	box->findBox->Bind(wxEVT_COMBOBOX_CLOSEUP, [this](wxCommandEvent&)
		{
			this->box->isDropdown = false;
		});
	box->findBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent& evt)
		{
			wxString ans = evt.GetString();

			this->box->findBox->ChangeValue(ans);
			this->box->findBox->SetInsertionPointEnd();
			this->box->findBox->SelectNone();
			this->box->findBox->ChangeValue(ans);
			this->box->findBox->Dismiss();
			this->box->findBox->ChangeValue(ans);
		});
	box->findBox->Bind(wxEVT_TEXT, &SearchPage::OnFindBoxEnter, this);
	box->language->Bind(wxEVT_COMBOBOX, &SearchPage::OnChooseLanguage, this); 
	box->wordOrDefi->Bind(wxEVT_COMBOBOX, &SearchPage::OnChooseWordOrDefi, this); 


	box->searchButton->Bind(wxEVT_BUTTON, &SearchPage::OnSearchBtnClicked, this);
	box->randomButton->Bind(wxEVT_BUTTON, &SearchPage::OnRandomBtnClicked, this);


	res = new resPage(this);
	this->res->removeButton->Bind(wxEVT_BUTTON, &SearchPage::OnRemoveBtnClicked, this);
	wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL);
	searchSizer->Add(searchPanel, 0, wxEXPAND);
	searchSizer->Add(res, 1, wxEXPAND);
	this->SetSizerAndFit(searchSizer);
}

void SearchPage::OnFindBoxEnter(wxCommandEvent& evt)
{

	std::u32string word = una::utf8to32u(evt.GetString().utf8_string());
	
	while (!this->box->findBox->IsListEmpty()) this->box->findBox->Delete(0); 


	if (word.empty())
	{
		this->box->findBox->Dismiss();
	}
	else
	{
		this->box->findBox->ChangeValue(wxString(una::utf32to16(word)));		
		this->box->findBox->Append(list->searchByPrefix(word));
		if (!this->box->isDropdown) 
			this->box->findBox->Popup();
				
		this->box->findBox->SelectNone();
		this->box->findBox->ChangeValue(wxString(una::utf32to16(word)));
 		this->box->findBox->SetInsertionPointEnd(); 
		
		
		
		
	}
	
}

void SearchPage::OnSearchBtnClicked(wxCommandEvent&)
{
	this->res->clearScreen();
	TST::TreeNode* ans = list->search(una::utf8to32u(this->box->findBox->GetValue().utf8_string()));
	if (ans)
	{
		word newWord;
		newWord.word = this->box->findBox->GetValue().utf8_string();
		std::string defi = ans->defi;
		std::stringstream ss(defi);
		if (currLang == "ENG/VIE" or currLang == "VIE/ENG") {
			defi.erase(0, 1);
			while (defi[0] == '*') {
				defi.erase(0, 1);
				auto pos = defi.find_first_of("\n");
				if (pos != std::string::npos) {
					newWord.type = defi.substr(0, pos);
					defi = defi.substr(pos+1);
					pos = defi.find_first_of("*");
					if (pos != std::string::npos) {
						newWord.definition = defi.substr(0, pos);
						defi = defi.substr(pos);
					}
					else {
						newWord.definition = defi;
						defi = "\0";
					}
					//word to be deleted
					deleted_word = una::utf8to32u(newWord.word);
					dataHisto.push_back(newWord);

					if (defi[0] == '\0') break;
				}
			}
		}
		else if (currLang == "EMOTICON") {
			auto pos = defi.find_first_of("(");
			defi = defi.substr(pos + 1);
			pos = defi.find_first_of(")");
			if (pos != std::string::npos ) newWord.type = defi.substr(0, pos);
			pos = defi.find_first_of("\t");
			defi = defi.substr(pos + 1);
			newWord.definition = defi;
			defi = '\0';
			//word to be deleted
			deleted_word = una::utf8to32u(newWord.word);
			dataHisto.push_back(newWord);
		}
		else {
			auto pos = defi.find_first_of("(");
			defi = defi.substr(pos + 1);
			pos = defi.find_first_of(")");
			if (pos != std::string::npos) newWord.type = defi.substr(0, pos);
			defi = defi.substr(pos + 1);
			newWord.definition = defi;
			defi = '\0';
			//word to be deleted
			deleted_word = una::utf8to32u(newWord.word);
			dataHisto.push_back(newWord);
		}
		this->res->addingString(wxString(una::utf8to16(this->box->findBox->GetValue().utf8_string())) + wxString(una::utf8to16(ans->defi)));
		
	}
	
}


void SearchPage::OnChooseLanguage(wxCommandEvent& evt)
{
	std::string type = evt.GetString().utf8_string();
	if (type == currLang) return; 
	
	if (box->wordOrDefi->GetValue() == "KEYWORD")
	{
		if (type == "ENG/VIE") {
			if (!EVtree->isLoaded())
				EVtree->loadWord(EVDATASET);

			list = EVtree;
		}
		else if (type == "VIE/ENG") {
				if (!VEtree->isLoaded())
					VEtree->loadWord(VEDATASET);

				list = VEtree;
			}
		else if (type == "ENG/ENG") {
			if (!EEtree->isLoaded())
				EEtree->loadWord(EEDATASET);

			list = EEtree;
		}
		else if (type == "EMOTICON") {
			if (!EMOtree->isLoaded())
				EMOtree->loadWord(EMODATASET);

			list = EMOtree;
		}
		else if (type == "SLANG") {
			if (!SLtree->isLoaded())
				SLtree->loadWord(SLDATASET);

			list = SLtree;
		}
	}
	else
	{
		return; 
	} 
	currLang = type; 
	return;
}

void SearchPage::OnChooseWordOrDefi(wxCommandEvent& evt)
{
	std::string type = evt.GetString().utf8_string(); 
	if (type == currType) return; 
	
	if (box->language->GetValue() == "ENG/VIE")
	{
		if (type == "DEFINTION") {
			if (!EVtree->isLoaded())
				EVtree->loadWord(EVDATASET);

			list = EVtree;
		
		}
		else {
			if (!EVtree->isLoaded())
				EVtree->loadWord(EVDATASET);

			list = EVtree;
		}
	}
	else if (box->language->GetValue() == "VIE/ENG")
	{
		if (type == "DEFINTION") {
			if (!VEtree->isLoaded())
				VEtree->loadWord(VEDATASET);

			list = VEtree;
		}
		else {
			if (!VEtree->isLoaded())
				VEtree->loadWord(VEDATASET);

			list = VEtree;
		}

	}
	currType = type; 
	return; 
}

void SearchPage::OnRandomBtnClicked(wxCommandEvent&)
{
	this->res->clearScreen(); 
	pair<std::u32string, std::string> ans = list->random();
	this->res->addingString(wxString(una::utf32to16(ans.first)) + wxString(una::utf8to16(ans.second))); 
	return; 
}

void SearchPage::OnRemoveBtnClicked(wxCommandEvent&)
{
	std::u32string str = deleted_word;
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	
	if (this->currLang == "ENG/VIE")
	{
		this->list->delete_word(list->root, str, "data/ev/delete.txt");
	}
	else if (this->currLang == "VIE/ENG")
	{
		this->list->delete_word(list->root, str, VEDELETE);
	}
	else if (this->currLang == "ENG/ENG")
	{
		this->list->delete_word(list->root, str, EEDELETE);
	}
	else if (this->currLang == "EMOTICON")
	{
		this->list->delete_word(list->root, str, EMODELETE);
	}
	else if (this->currLang == "SLANG")
	{
		this->list->delete_word(list->root, str, SLDELETE);
	}
	//wxMessageBox("Delete successfully","successfully", wxOK | wxICON_INFORMATION);
	return;
}