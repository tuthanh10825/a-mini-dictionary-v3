#include "add-page.h"
AddWindow::AddWindow(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	wxInitAllImageHandlers();
	//wxPanel* right = new wxPanel(this);
	wxFont pala(19, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
	wxStaticText* key = new wxStaticText(this, wxID_ANY, "Keyword");
	key->SetFont(pala);
	wxStaticText* ty = new wxStaticText(this, wxID_ANY, "Type");
	ty->SetFont(pala);
	wxStaticText* def = new wxStaticText(this, wxID_ANY, "Definition");
	def->SetFont(pala);

	keyword->SetFont(pala);
	type->SetFont(pala);
	defi->SetFont(pala);


	language->SetFont(pala);
	language->Append(wxString("ENG/ENG"));
	language->Append(wxString("ENG/VIE"));
	language->Append(wxString("VIE/ENG"));
	language->Append(wxString("SLANG"));
	language->Append(wxString("EMOTICON"));

	language->SetSelection(0);

	wxBitmap add(ADD_IMG, wxBITMAP_TYPE_PNG);
	wxBitmapButton* addbutton = new wxBitmapButton(this, wxID_ANY, add, wxDefaultPosition, wxSize(251, 57));

	wxBitmap cancel(CANCEL_IMG, wxBITMAP_TYPE_PNG);
	wxBitmapButton* cancelbutton = new wxBitmapButton(this, wxID_ANY, cancel, wxDefaultPosition, wxSize(251, 57));

	wxBoxSizer* rightbot = new wxBoxSizer(wxVERTICAL);
	
	rightbot->Add(language, 0, wxEXPAND | wxTOP,80);
	rightbot->Add(addbutton, 0, wxEXPAND | wxTOP, 300);
	rightbot->Add(cancelbutton, 0, wxEXPAND | wxTOP, 15);

	wxBoxSizer* rightsizer = new wxBoxSizer(wxVERTICAL);
	rightsizer->Add(key, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	rightsizer->Add(keyword, 2, wxEXPAND);
	rightsizer->Add(ty, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	rightsizer->Add(type, 1, wxEXPAND);
	rightsizer->Add(def, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	rightsizer->Add(defi, 3, wxEXPAND);

	wxBoxSizer* mainsizer = new wxBoxSizer(wxHORIZONTAL);
	mainsizer->Add(rightsizer, 1, wxEXPAND | wxALL, 50);
	mainsizer->Add(rightbot, 0, wxEXPAND | wxALL, 20);
	this->SetSizerAndFit(mainsizer);
}