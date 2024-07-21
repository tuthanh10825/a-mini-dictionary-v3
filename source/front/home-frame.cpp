#include "home-frame.h"

// Define an ID for the button

HomeFrame::HomeFrame(const wxString& title)
    : BaseFrame(title) 
{
    // Now you can ignore all header, footer, navigation and working as if you work on empty frame. 
    // However, remember to replace this, to this -> workingWindow; 
    // For example, if you want to define a panel, use: 
    wxPanel* panel = new wxPanel(this -> workingWindow, wxID_ANY); 
}
