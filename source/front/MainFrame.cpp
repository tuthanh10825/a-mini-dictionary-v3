
#include "MainFrame.h"
mainFrame::mainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	storing.loadAll("data/ee/data.csv"); //insert filename here. 
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

	wxPanel* appName = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 150));
	appName->SetBackgroundColour(wxColor(33, 38, 79));

	wxPanel* logo = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(200, 150));
	logo->SetBackgroundColour(wxColor(255, 255, 255));


	topSizer->Add(appName, 1, wxEXPAND);
	topSizer->Add(logo, 0, wxEXPAND);



	searchBox = new wxTextCtrl(this, wxID_ANY);



	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(searchBox, 1, wxEXPAND);


	wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);
	wordsList = new wxListBox(splitter, wxID_ANY);
	wordsList->Bind(wxEVT_LISTBOX_DCLICK, &mainFrame::showDefi, this);

	definition = new wxTextCtrl(splitter, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	splitter->SplitVertically(wordsList, definition);
	splitter->SetMinimumPaneSize(200);

	searchBox->Bind(wxEVT_TEXT, &mainFrame::printWord, this);

	mainSizer->Add(topSizer, 0, wxEXPAND);
	mainSizer->Add(boxSizer, 0, wxEXPAND);
	mainSizer->Add(splitter, 1, wxEXPAND);


	this->SetSizerAndFit(mainSizer);
}

void mainFrame::printWord(wxCommandEvent& evt)
{
	std::string word = evt.GetString().ToStdString();

	wordsList->Clear();


	if (word.size() < 2) return;

	wxArrayString list = storing.getByPrefix(word);
	if (list.empty()) return;


	wordsList->InsertItems(/*wxarraystring({ "found!" })*/list, 0);
	return;
}
void mainFrame::showDefi(wxCommandEvent& evt)
{
	definition->SetValue(evt.GetString());
	return;
}