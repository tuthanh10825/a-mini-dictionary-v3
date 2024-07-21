#ifndef BASEFRAME_H
#define BASEFRAME_H
#include <wx/wx.h>

#include <wx/statbmp.h>
#include "properties.h"

class BaseFrame : public wxFrame {
public:
    BaseFrame(const wxString& title = wxString(""));
    wxWindow* workingWindow;
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 

private:

    void LoadHeader();
    void loadFooter(); 
    void LoadNavigation();

    void LoadImage(const wxString& imagePath, wxPanel* panel);

    void OnHomeBtnClicked(wxCommandEvent& event);
};

#endif // BASEFRAME_H
