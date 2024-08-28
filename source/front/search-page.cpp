#include "search-page.h"
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

	language->SetSelection(0); 
	language->SetEditable(false);
	language->SetBackgroundColour(*wxWHITE);

	wordOrDefi->Append(wxString("KEYWORD")); 
	wordOrDefi->Append(wxString("DEFINITION")); 
	wordOrDefi->SetSelection(0); 
	wordOrDefi->SetEditable(false);
	wordOrDefi->SetBackgroundColour(*wxWHITE);
	 
	findBox->SetFont(pala);
	
	std::string s = LIGHTMODE ? "" : "1"; 
	searchButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/search-button.png", wxBITMAP_TYPE_PNG));
	randomButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/random-button" + s + ".png", wxBITMAP_TYPE_PNG));
	addButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/add-button" + s + ".png", wxBITMAP_TYPE_PNG)); 
	resetButton = new wxBitmapButton(this, wxID_ANY, wxBitmap("assets/search/reset-button" + s + ".png", wxBITMAP_TYPE_PNG));

	

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

	resetButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&)
		{
			removingEE.clear(); 
			removingEV.clear(); 
			removingVE.clear();
			removingSlang.clear(); 
			removingEmo.clear(); 
			addingEE.clear(); 
			addingEV.clear(); 
			addingVE.clear(); 
			addingEmo.clear(); 
			addingSlang.clear();
			EEtree->clear();
			EVtree->clear(); 
			VEtree->clear(); 
			SLtree->clear(); 
			EMOtree->clear();
		});
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
	if (!temp.empty()) {
		dataFav.push_back(temp.back());
		temp.pop_back();
		while (!temp.empty()) {
			if (temp.back().word != dataFav.back().word) return;
			dataFav.push_back(temp.back());
			temp.pop_back();
		}
	}

	wxString message = "Add success!";
	wxMessageBox(message, "Notification", wxOK | wxICON_INFORMATION);
}

SearchPage::SearchPage(wxWindow* parent) : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT))
{
	// Load Eng-Viet dataset
	if (!EEtree->isLoaded())
		EEtree->loadWord(EEDATASET);
	defi = nullptr;
	list = EEtree;

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

	box->searchButton->Bind(wxEVT_BUTTON, &SearchPage::OnSearchBtnClicked, this);
	box->randomButton->Bind(wxEVT_BUTTON, &SearchPage::OnRandomBtnClicked, this);


	res = new resPage(this);
	this->res->removeButton->Bind(wxEVT_BUTTON, &SearchPage::OnRemoveBtnClicked, this);
	this->res->editButton->Bind(wxEVT_BUTTON, &SearchPage::OnEditBtnClicked, this);
	wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL);
	searchSizer->Add(searchPanel, 0, wxEXPAND);
	searchSizer->Add(res, 1, wxEXPAND);
	this->SetSizerAndFit(searchSizer);
}


void SearchPage::OnFindBoxEnter(wxCommandEvent& evt)
{
	if (this->box->wordOrDefi->GetValue().utf8_string() == "KEYWORD")
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
	
}


void SearchPage::insertHistory(TST::TreeNode* ans) {
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
				defi = defi.substr(pos + 1);
				pos = defi.find_first_of("*");
				if (pos != std::string::npos) {
					newWord.definition = defi.substr(0, pos);
					defi = defi.substr(pos);
				}
				else {
					newWord.definition = defi;
					defi = "\0";

				}
				dataHisto.push_back(newWord);
				if (defi[0] == '\0') break;
			}
			//deleted_word = una::utf8to32u(newWord.word);
			dataHisto.push_back(newWord);
		}


	}
	else if (currLang == "EMOTICON") {
		auto pos = defi.find_first_of("(");
		defi = defi.substr(pos + 1);
		pos = defi.find_first_of(")");
		if (pos != std::string::npos) newWord.type = defi.substr(0, pos);
		pos = defi.find_first_of("\t");
		defi = defi.substr(pos + 1);
		newWord.definition = defi;
		defi = '\0';
    //deleted_word = una::utf8to32u(newWord.word);
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
    //deleted_word = una::utf8to32u(newWord.word);
		dataHisto.push_back(newWord);
	}
}

void SearchPage::OnSearchBtnClicked(wxCommandEvent&)
{
	if (this->box->wordOrDefi -> GetValue().utf8_string() == "KEYWORD")
	{
		this->res->clearScreen();
		TST::TreeNode* ans = list->search(una::utf8to32u(this->box->findBox->GetValue().utf8_string()));
		if (ans)
		{
			insertHistory(ans);
			this->res->addingString(wxString(una::utf8to16(this->box->findBox->GetValue().utf8_string())) + wxString(una::utf8to16(ans->defi)));
		}
	}
	else
	{
		std::string type = box->language->GetValue().utf8_string();
		if (type == "ENG/ENG")
		{
			if (EEDef.text.empty()) EEDef.loadFile(EEDATASET);
			this->defi = &EEDef;
		}
		else if (type == "ENG/VIE")
		{
			if (EVDef.text.empty()) EVDef.loadFile(EVDATASET);
			this->defi = &EVDef;
		}
		else if (type == "VIE/ENG")
		{
			if (VEDef.text.empty()) VEDef.loadFile(VEDATASET);
			this->defi = &VEDef;
		}
		else if (type == "SLANG")
		{
			if (SLDef.text.empty()) SLDef.loadFile(SLDATASET);
			this->defi = &SLDef;
		}
		else if (type == "EMOTICON")
		{
			if (EMODef.text.empty()) EMODef.loadFile(EMODATASET);
			this->defi = &EMODef;
		}
		vector<std::u32string> ans = this->defi->findSubtring(una::utf8to32u(this->box->findBox->GetValue().utf8_string()), currLang);
		if (type == "ENG/ENG")
		{
			for (auto iter = addingEE.begin(); iter != addingEE.end(); ++iter)
				if (una::utf8to32u((*iter).second).find(una::utf8to32u(this->box->findBox->GetValue().utf8_string())) != std::u32string::npos)
					ans.push_back((*iter).first); 
		}
		else if (type == "ENG/VIE")
		{
			for (auto iter = addingEV.begin(); iter != addingEV.end(); ++iter)
				if (una::utf8to32u((*iter).second).find(una::utf8to32u(this->box->findBox->GetValue().utf8_string())) != std::u32string::npos)
					ans.push_back((*iter).first);
		}
		else if (type == "VIE/ENG")
		{
			for (auto iter = addingVE.begin(); iter != addingVE.end(); ++iter)
				if (una::utf8to32u((*iter).second).find(una::utf8to32u(this->box->findBox->GetValue().utf8_string())) != std::u32string::npos)
					ans.push_back((*iter).first);

		}
		else if (type == "SLANG")
		{
			for (auto iter = addingSlang.begin(); iter != addingSlang.end(); ++iter)
				if (una::utf8to32u((*iter).second).find(una::utf8to32u(this->box->findBox->GetValue().utf8_string())) != std::u32string::npos)
					ans.push_back((*iter).first);

		}
		else if (type == "EMOTICON")
		{
			for (auto iter = addingEmo.begin(); iter != addingEmo.end(); ++iter)
				if (una::utf8to32u((*iter).second).find(una::utf8to32u(this->box->findBox->GetValue().utf8_string())) != std::u32string::npos)
					ans.push_back((*iter).first);
		}
		this->res->clearScreen();

		std::u32string total_ans; 
		for (const auto& val : ans)
			total_ans += (val + U"\n");

		this->res->addingString(wxString(una::utf32to16(total_ans))); 
	}
}


void SearchPage::OnChooseLanguage(wxCommandEvent& evt)
{
	std::string type = evt.GetString().utf8_string();
	if (type == currLang) return; 
	
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
	
	currLang = type; 
	return;
}


void SearchPage::OnRandomBtnClicked(wxCommandEvent&)
{
	this->res->clearScreen(); 
	pair<std::u32string, std::string> ans = list->random();


	this->box->findBox->ChangeValue(wxString(una::utf32to16(ans.first))); 
	this->res->addingString(wxString(una::utf32to16(ans.first)) + wxString(una::utf8to16(ans.second))); 
	insertHistory(list->search(ans.first)); 
	return; 
}

void SearchPage::OnRemoveBtnClicked(wxCommandEvent&)
{
	deleted_word = una::utf8to32u(this->box->findBox->GetValue().utf8_string());
	if (deleted_word.empty()) return;
	std::u32string str = deleted_word;
	wxMessageDialog confirmDialog(
		this,
		"Are you sure to delete this word?",  
		"Delete?",            
		wxYES_NO | wxNO_DEFAULT | wxICON_WARNING
	);
	if (confirmDialog.ShowModal() == wxID_YES)
	{
		if (this->currLang == "ENG/VIE")
		{
			addingEV[deleted_word] = "";
			this->list->delete_word(list->root, str, EVDELETE);
			removingEV.insert(deleted_word);
		}
		else if (this->currLang == "VIE/ENG")
		{
			addingVE[deleted_word] = "";
			this->list->delete_word(list->root, str, VEDELETE);
			removingVE.insert(deleted_word);
		}
		else if (this->currLang == "ENG/ENG")
		{
			addingEE[deleted_word] = "";
			this->list->delete_word(list->root, str, EEDELETE);
			removingEE.insert(deleted_word);
		}
		else if (this->currLang == "EMOTICON")
		{
			addingEmo[deleted_word] = "";
			this->list->delete_word(list->root, str, EMODELETE);
			removingEmo.insert(deleted_word);
		}
		else if (this->currLang == "SLANG")
		{
			addingSlang[deleted_word] = "";
			this->list->delete_word(list->root, str, SLDELETE);
			removingSlang.insert(deleted_word);
		}
		wxMessageBox("Delete successfully", "Successfully", wxOK | wxICON_INFORMATION);
		this->box->findBox->Clear();
		this->res->clearScreen();
		deleted_word.clear();
	}
	return;
}

void SearchPage::OnEditBtnClicked(wxCommandEvent&)
{
	editwin = new EditWindow(this->res);
	editwin->Show(true);
	editwin->editbutton->Bind(wxEVT_BUTTON, &SearchPage::OnEdit_WordBtnClicked, this);
	TST::TreeNode* ans = list->search(una::utf8to32u(this->box->findBox->GetValue().utf8_string()));
	if (ans)
	{
		std::u32string key = una::utf8to32u(this->box->findBox->GetValue().utf8_string());
		editwin->keyword->ChangeValue(wxString(una::utf32to16(key)));

		std::u32string definition = una::utf8to32u(ans->defi);
		editwin->defi->ChangeValue(wxString(una::utf32to16(definition)));
	}
}
void SearchPage::OnEdit_WordBtnClicked(wxCommandEvent&)
{
	TST::TreeNode* ans = list->search(una::utf8to32u(this->box->findBox->GetValue().utf8_string()));
	if (ans)
	{
		wxString s1 = editwin->keyword->GetValue().utf8_string();
		wxString s2 = editwin->defi->GetValue().utf8_string();
		std::string keystr = s1.ToStdString();
		std::string defistr = s2.ToStdString();
		size_t pos = defistr.find_first_not_of("\n");
		if (pos != std::string::npos) {
			defistr = defistr.substr(pos);
		}
		ans->defi = "\n"+ defistr;
		std::string def = "\n" + defistr;

		if (currLang == "ENG/VIE") addingEV[una::utf8to32u(keystr)] = def;
		else if (currLang == "VIE/ENG") addingVE[una::utf8to32u(keystr)] = def;
		else if (currLang == "ENG/ENG") addingEE[una::utf8to32u(keystr)] = def;
		else if (currLang == "SLANG") addingSlang[una::utf8to32u(keystr)] = def;
		else if (currLang == "EMOTICON") addingEmo[una::utf8to32u(keystr)] = def;

		wxMessageBox("Edit a word successfully", "Successfully", wxOK | wxICON_INFORMATION);
		editwin->Close(true);
		this->res->clearScreen();
	}
}


void SearchPage::FlipColor()
{
	box->FlipColor();
	res->FlipColor();
}

void resPage::FlipColor()
{
	std::string s;
	//TODO: remember to change the bitmap of the button. 
	if (LIGHTMODE)
	{
		editButton->SetBackgroundColour(*wxWHITE);
		favorButton->SetBackgroundColour(*wxWHITE);
		removeButton->SetBackgroundColour(*wxWHITE);
		resWord->SetBackgroundColour(*wxWHITE); 
		resWord->SetForegroundColour(*wxBLACK); 
		s = "";
	}
	else
	{
		editButton->SetBackgroundColour(*wxBLACK); 
		favorButton->SetBackgroundColour(*wxBLACK); 
		removeButton->SetBackgroundColour(*wxBLACK); 
		resWord->SetBackgroundColour(*wxBLACK); 
		resWord->SetForegroundColour(*wxWHITE);
		s = "1"; 
	}
	editButton->SetBitmap(wxBitmap("assets/result/edit-button" + s + ".png", wxBITMAP_TYPE_PNG)); 
	favorButton->SetBitmap(wxBitmap("assets/result/favorite-button" + s + ".png", wxBITMAP_TYPE_PNG));
	removeButton->SetBitmap(wxBitmap("assets/result/remove-button" + s + ".png", wxBITMAP_TYPE_PNG));
	this->Refresh();
}

void searchBox::FlipColor()
{
	std::string s; 
	//TODO: remember to change all bitmap of the button
	if (LIGHTMODE)
	{
		searchButton->SetBackgroundColour(*wxWHITE);
		randomButton->SetBackgroundColour(*wxWHITE);
		resetButton->SetBackgroundColour(*wxWHITE);
		addButton->SetBackgroundColour(*wxWHITE);

		wordOrDefi->SetBackgroundColour(*wxWHITE); 
		wordOrDefi->SetForegroundColour(*wxBLACK); 

		language->SetBackgroundColour(*wxWHITE); 
		language->SetForegroundColour(*wxBLACK); 
		
		findBox->SetBackgroundColour(*wxWHITE); 
		findBox->SetForegroundColour(*wxBLACK); 
		this->SetBackgroundColour(*wxWHITE);
		s = "";
	}
	else
	{
		searchButton->SetBackgroundColour(*wxBLACK);
		randomButton->SetBackgroundColour(*wxBLACK);
		resetButton->SetBackgroundColour(*wxBLACK);
		addButton->SetBackgroundColour(*wxBLACK);

	
		wordOrDefi->SetBackgroundColour(*wxBLACK);
		wordOrDefi->SetForegroundColour(*wxWHITE);

		language->SetBackgroundColour(*wxBLACK);
		language->SetForegroundColour(*wxWHITE);

		findBox->SetBackgroundColour(*wxBLACK);
		findBox->SetForegroundColour(*wxWHITE);
		this->SetBackgroundColour(*wxBLACK);
		s = "1";
	}
	randomButton->SetBitmapLabel(wxBitmap("assets/search/random-button" + s + ".png", wxBITMAP_TYPE_PNG));
	resetButton->SetBitmapLabel(wxBitmap("assets/search/reset-button" + s + ".png", wxBITMAP_TYPE_PNG));
	addButton->SetBitmapLabel(wxBitmap("assets/search/add-button" + s + ".png", wxBITMAP_TYPE_PNG));
	
	this->Refresh();
}
