#include <wx/wx.h>
#include "properties.h"
#include <wx/wrapsizer.h>
#include <wx/statbmp.h> 
class DefGameWindow : public wxFrame
{
public:
	DefGameWindow(const wxString& title);
private:
	void LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel);
	void OnRadioButton(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

