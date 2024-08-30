#include "edit-page.h"
EditWindow::EditWindow(wxWindow* parent) : wxFrame(parent, wxID_ANY, "Edit", wxDefaultPosition, wxDefaultSize)
{
	if (LIGHTMODE) {
		this->background = LIGHTMODE_backgroundANDNaviColor;
		this->textColor = LIGHTMODE_blackTextColor;
	}
	else {
		this->background = DARKMODE_backgroundColor;
		this->textColor = DARKMODE_whiteTextColor;
	}
	this->SetBackgroundColour(background);

	this->Refresh();

	wxInitAllImageHandlers();

	wxFont pala(19, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
	wxStaticText* key = new wxStaticText(this, wxID_ANY, "Keyword");
	key->SetFont(pala);
	key->SetForegroundColour(textColor);

	wxStaticText* def = new wxStaticText(this, wxID_ANY, "Definition");
	def->SetFont(pala);
	def->SetForegroundColour(textColor);

	keyword->SetFont(pala);

	defi->SetFont(pala);


	wxBitmap edit(EDIT_IMG, wxBITMAP_TYPE_PNG);
	editbutton = new wxBitmapButton(this, wxID_ANY, edit, wxDefaultPosition, wxSize(251, 57));

	wxBitmap cancel(CANCEL_IMG, wxBITMAP_TYPE_PNG);
	wxBitmapButton* cancelbutton = new wxBitmapButton(this, wxID_ANY, cancel, wxDefaultPosition, wxSize(251, 57));
	cancelbutton->Bind(wxEVT_BUTTON, &EditWindow::OnCancelBtnClicked, this);

	wxBoxSizer* rightbot = new wxBoxSizer(wxVERTICAL);

	rightbot->Add(editbutton, 0, wxEXPAND | wxTOP, 300);
	rightbot->Add(cancelbutton, 0, wxEXPAND | wxTOP, 15);

	wxBoxSizer* rightsizer = new wxBoxSizer(wxVERTICAL);
	rightsizer->Add(key, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	rightsizer->Add(keyword, 2, wxEXPAND);

	rightsizer->Add(def, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	rightsizer->Add(defi, 3, wxEXPAND);

	wxBoxSizer* mainsizer = new wxBoxSizer(wxHORIZONTAL);
	mainsizer->Add(rightsizer, 1, wxEXPAND | wxALL, 50);
	mainsizer->Add(rightbot, 0, wxEXPAND | wxALL, 20);
	this->SetSizerAndFit(mainsizer);
}
void EditWindow::OnCancelBtnClicked(wxCommandEvent&)
{
	this->Close(true);
}
