#include <wx/wx.h>
#include "Globals.h"
class MoreWindow : public wxWindow
{
public:
	MoreWindow(wxWindow*);
	wxBitmapButton* darkmodeButton;
	void FlipColor();

private:
	wxColour background;
	wxPanel* descriptionPanel = new wxPanel(this, wxID_ANY);
	wxBitmapButton* userManualButton = new wxBitmapButton(descriptionPanel, wxID_ANY, wxBitmap("assets/more/user-manual-button.png", wxBITMAP_TYPE_PNG));
	void OnUserManualClicked(wxCommandEvent&); 

};