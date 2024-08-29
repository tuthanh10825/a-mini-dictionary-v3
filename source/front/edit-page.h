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
	wxColour background;
	wxColour textColor;
private:
	void OnEditBtnClicked(wxCommandEvent&); 
	void OnCancelBtnClicked(wxCommandEvent&);
	void FlipColor();
};
