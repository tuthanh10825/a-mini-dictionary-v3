#ifndef BASEFRAME_H
#define BASEFRAME_H

#include <wx/statbmp.h>
#include "properties.h"
#include "MainFrame.h"

class BaseFrame : public wxFrame {
public:
    BaseFrame(const wxString& title, const wxSize& size);
    wxPanel* mainPanel;

private:

    void LoadHeaderFooter(wxPanel* panel);
    void LoadNavigation(wxPanel* panel);

    void LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel);

    void OnHomeBtnClicked(wxCommandEvent& event);
};

#endif // BASEFRAME_H
