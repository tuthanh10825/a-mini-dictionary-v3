#include <wx/wx.h>
#include "Globals.h"
class MoreWindow : public wxWindow
{
public:
	MoreWindow(wxWindow*);
private:
	wxBitmapButton* darkmodeButton; 
	void OnUserManualClicked(wxCommandEvent&); 
	void OnDarkmodeClicked(wxCommandEvent&);
	//void refreshAllPage();
};