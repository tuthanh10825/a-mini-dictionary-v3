#include "add-page.h"
AddWindow::AddWindow(wxWindow* parent) : wxWindow(parent, wxID_ANY)
{
	FlipColor();

	if (!EEtree->isLoaded())
		EEtree->loadWord(EEDATASET);
	list = EEtree;

	wxInitAllImageHandlers();
	this->SetBackgroundColour(*wxWHITE);
	//wxPanel* right = new wxPanel(this);
	wxFont pala(19, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
	key->SetFont(pala);

	ty->SetFont(pala);
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

	language->Bind(wxEVT_TEXT, &AddWindow::OnChooseLanguage, this);

	wxBitmap add(ADD_IMG, wxBITMAP_TYPE_PNG);
	wxBitmapButton* addbutton = new wxBitmapButton(this, wxID_ANY, add, wxDefaultPosition, wxSize(251, 57));
	addbutton->Bind(wxEVT_BUTTON, &AddWindow::OnAddBtnClicked, this);

	wxBitmap cancel(CANCEL_IMG, wxBITMAP_TYPE_PNG);
    cancelbutton = new wxBitmapButton(this, wxID_ANY, cancel, wxDefaultPosition, wxSize(251, 57));

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
void AddWindow::FlipColor()
{

	if (LIGHTMODE) {
		this->SetBackgroundColour(LIGHTMODE_backgroundANDNaviColor);

		this->key->SetForegroundColour(BLACK);
		this->ty->SetForegroundColour(BLACK);
		this->def->SetForegroundColour(BLACK);
	}
	else {

		this->SetBackgroundColour(DARKMODE_backgroundColor);
		this->key->SetForegroundColour(WHITE);
		this->ty->SetForegroundColour(WHITE);
		this->def->SetForegroundColour(WHITE);
	}
}
void AddWindow::OnChooseLanguage(wxCommandEvent& evt)
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
void AddWindow::OnAddBtnClicked(wxCommandEvent&)
{
	wxString s1 = keyword->GetValue().utf8_string();
	wxString s2 = type->GetValue().utf8_string();
	wxString s3 = defi->GetValue().utf8_string();

	std::string keystr = s1.ToStdString();
	std::string typestr = s2.ToStdString();
	std::string defistr = s3.ToStdString();

	defistr = "\n* " + typestr + "\n- " + defistr;

	this->list->insert(keystr, defistr);
	wxMessageBox("Add a new word successfully", "Successfully", wxOK | wxICON_INFORMATION);
	if (currLang == "ENG/VIE")
	{
		addingEV[una::utf8to32u(keystr)] = defistr;
		isRebuildEV = true; 
	}
	else if (currLang == "VIE/ENG")
	{
		addingVE[una::utf8to32u(keystr)] = defistr;
		isRebuildVE = true;
	}
	else if (currLang == "ENG/ENG")
	{
		addingEE[una::utf8to32u(keystr)] = defistr;
		isRebuildEE = true;
	}
	else if (currLang == "SLANG")
	{
		addingSlang[una::utf8to32u(keystr)] = defistr;
		isRebuildSlang = true;
	}
	else if (currLang == "EMOTICON")
	{
		addingEmo[una::utf8to32u(keystr)] = defistr;
		isRebuildEmo = true;
	}
	keyword->ChangeValue(wxEmptyString);
	type->ChangeValue(wxEmptyString); 
	defi->ChangeValue(wxEmptyString);
	this->Refresh();
}