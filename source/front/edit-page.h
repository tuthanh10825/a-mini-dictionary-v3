#include <wx/wx.h>
#include "Globals.h"
#include "properties.h"
class EditWindow : public wxFrame
{
public:
	EditWindow(wxWindow*);
	wxTextCtrl* keyword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY);
	wxTextCtrl* defi = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	wxBitmapButton* editbutton;
private:
	void OnChooseLanguage(wxCommandEvent& evt);
	void OnAddBtnClicked(wxCommandEvent&);
	void OnCancelBtnClicked(wxCommandEvent&);
};
