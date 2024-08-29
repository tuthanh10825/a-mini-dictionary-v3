#include <wx/wx.h>
#include "Globals.h"
#include "properties.h"
#include "red-black-tree.h"

class AddWindow : public wxWindow
{
public:
	AddWindow(wxWindow*);
	wxTextCtrl* keyword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxTextCtrl* type = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxTextCtrl* defi = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxComboBox* language = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize((1451.25 / 6), 63.13), 0, nullptr, wxCB_READONLY);
	bool isDropdown = false;
	wxBitmapButton* cancelbutton;
	wxStaticText* key = new wxStaticText(this, wxID_ANY, "Keyword");
	wxStaticText* ty = new wxStaticText(this, wxID_ANY, "Type");
	wxStaticText* def = new wxStaticText(this, wxID_ANY, "Definition");

	void FlipColor();
private:
	TST* list;
	std::string currLang = "ENG/ENG";
	void OnChooseLanguage(wxCommandEvent& evt);
	void OnAddBtnClicked(wxCommandEvent&);
};