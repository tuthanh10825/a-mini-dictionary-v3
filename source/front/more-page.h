#include <wx/wx.h>

class MoreWindow : public wxWindow
{
public:
	wxBitmapButton* darkmodeButton; 
	MoreWindow(wxWindow*);
	void OnUserManualClicked(wxCommandEvent&); 
};