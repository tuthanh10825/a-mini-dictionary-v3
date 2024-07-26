#include <wx/wx.h>

class MoreWindow : public wxFrame
{
public:
	MoreWindow(const wxString& title);
private:
	void LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel);
	void LoadHeaderFooter(wxPanel* panel);
};
