#include "search-page.h"

searchBox::searchBox(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
 
	language->Append(wxString(""), wxBitmap("assets/search/ee.png", wxBITMAP_TYPE_PNG));
	language->Append(wxString(""), wxBitmap("assets/search/ev.png", wxBITMAP_TYPE_PNG));
	language->Append(wxString(""), wxBitmap("assets/search/ve.png", wxBITMAP_TYPE_PNG));
	language->Append(wxString(""), wxBitmap("assets/search/emo.png", wxBITMAP_TYPE_PNG));
	language->Append(wxString(""), wxBitmap("assets/search/sla.png", wxBITMAP_TYPE_PNG));
	language->SetSelection(0); 
	

	wordOrDefi->Append(wxString(""), wxBitmap("assets/search/keyword.png", wxBITMAP_TYPE_PNG));
	wordOrDefi->Append(wxString(""), wxBitmap("assets/search/definition.png", wxBITMAP_TYPE_PNG));
	wordOrDefi->SetSelection(0); 

	
	 
	// (!wxFont::AddPrivateFont(wxString("./fonts/pala.ttf"))) throw;

	//some cheating to use palatino linotype
	wxFont pala; pala.SetNativeFontInfoUserDesc("Palatino Linotype 25 WINDOWS-1252"); 
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
	cas.SetNativeFontInfoUserDesc("Cascadia Code 30 WINDOWS-1252"); 
	resWord->SetFont(cas); 


	editButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxString("assets/result/edit-button.png"), wxBITMAP_TYPE_PNG));
	favorButton = new wxBitmapButton(this, wxID_ANY, wxBitmap(wxString("assets/result/favorite-button.png"), wxBITMAP_TYPE_PNG));
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

SearchPage::SearchPage(wxWindow* parent) : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT))
{
	wxPanel* searchPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* searchBarSizer = new wxBoxSizer(wxHORIZONTAL);
	searchPanel->SetBackgroundColour(BLUEBLACK);

	box = new searchBox(searchPanel);
	searchBarSizer->Add(box, 1, wxEXPAND | wxALL, 15);
	searchPanel->SetSizerAndFit(searchBarSizer);
	box->findBox->Bind(wxEVT_TEXT,&SearchPage::OnFindBoxEnter, this);
	
	 res = new resPage(this);
	res->addingString(wxString("Hello\n\tnoun\n\ttesting"));
	wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL);
	searchSizer->Add(searchPanel, 0, wxEXPAND);
	searchSizer->Add(res, 1, wxEXPAND);
	this->SetSizerAndFit(searchSizer);
}
void SearchPage::OnFindBoxEnter(wxCommandEvent& evt)
{
	std::string word = evt.GetString().utf8_string();

	while (!this->box->findBox->IsListEmpty()) this->box->findBox->Delete(0); 
	if (word.empty())
	{
		this->box->findBox->Dismiss();
	}
	else
	{
		this->box->findBox->Append(list.searchByPrefix(word));
		this->box->findBox->Popup();
		this->box->findBox->SelectNone();
		this->box->findBox->ChangeValue(word);
		this->box->findBox->SetInsertionPointEnd(); 
		
		
	}
	this->box->findBox->Refresh(); 
	
}