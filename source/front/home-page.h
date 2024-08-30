#ifndef HOMEFRAME_H
#define HOMEFRAME_H
#include <wx/wx.h>
#include <wx/statbmp.h>
#include "Globals.h"
#include "properties.h"
class HomePage : public wxWindow {
public:
    wxPanel* wordPanel;
    wxBitmapButton* quizButton;
    wxBitmapButton* favorButton;
    wxBitmapButton* randomButton;
    wxBitmapButton* editButton;
    HomePage(wxWindow *parent);

    void FlipColor(); 
private: 
    wxPanel* rightPanel; 
    wxPanel* leftPanel;
    wxPanel* subPanel;
    wxStaticBitmap* showLabel;
    wxStaticBitmap* wordOfTheDay; 
    wxStaticText* wordInfo;
    wxStaticText* defInfo;

};

#endif // HOMEFRAME_H
