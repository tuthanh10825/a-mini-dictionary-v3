#include <wx/wx.h>
#include "Globals.h"
class MoreWindow : public wxWindow
{
public:
	wxBitmapButton* darkmodeButton; 
	MoreWindow(wxWindow*);
	void OnUserManualClicked(wxCommandEvent&); 
	void OnDarkmodeClicked(wxCommandEvent&);
};