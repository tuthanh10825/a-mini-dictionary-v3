#include <wx/wx.h>
#include "Globals.h"
#include "properties.h"
class AddWindow : public wxWindow
{
public:
	AddWindow(wxWindow*);
	wxTextCtrl* keyword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxTextCtrl* type = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxTextCtrl* defi = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxComboBox* language = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize((1451.25 / 6), 63.13), 0, nullptr, wxCB_READONLY);
	bool isDropdown = false;
private:
	TST* list;
	std::string currLang = "ENG/ENG";
	void OnChooseLanguage(wxCommandEvent& evt);
	void OnAddBtnClicked(wxCommandEvent&);
	void OnCancelBtnClicked(wxCommandEvent&);
};