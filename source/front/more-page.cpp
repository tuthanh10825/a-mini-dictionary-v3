#include "more-page.h"
#include "properties.h" 
MoreWindow::MoreWindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    //header
    wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 155));
    //bar
    wxPanel* barPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 64));
    //green
    wxPanel* greenpanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 101));
    //yellow
    wxPanel* yellowpanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 631));
    yellowpanel->SetBackgroundColour(wxColour(255, 250, 230));

    wxInitAllImageHandlers();
    LoadHeaderFooter(topPanel);
    LoadImage(NAVIGATIONBAR_IMG, wxPoint(0, 0), barPanel);

    greenpanel->SetBackgroundColour(wxColor(101, 164, 165));
    //About us
    //wxStaticText* aboutus = new wxStaticText(greenpanel, wxID_ANY, "About us", wxPoint(267, 40), wxSize(262, 73));
    wxTextCtrl* aboutus = new wxTextCtrl(greenpanel, wxID_ANY, "About us", wxPoint(266, 28), wxSize(262, 73), wxTE_READONLY | wxBORDER_NONE);
    aboutus->SetBackgroundColour(wxColor(101, 164, 165));
    aboutus->SetOwnForegroundColour(wxColour(255, 255, 255));
    wxFont aboutus_font = wxFont(33, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
    aboutus->SetFont(aboutus_font);

    //first sentence on yellow panel
    wxTextCtrl* fstsen = new wxTextCtrl(yellowpanel, wxID_ANY, "Our dictionary aims to help people search words in English easily and fast",
        wxPoint(204, 91), wxSize(1111, 100), wxTE_READONLY | wxBORDER_NONE | wxTE_MULTILINE | wxTE_NO_VSCROLL);
    wxFont fstsen_font = wxFont(27, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);
    fstsen->SetFont(fstsen_font);
    fstsen->SetBackgroundColour(wxColor(255, 250, 230));
    fstsen->SetOwnForegroundColour(wxColour(102, 102, 102));

    //second sentence on yellow panel
    wxTextCtrl* sndsen = new wxTextCtrl(yellowpanel, wxID_ANY, "This dictionary was created by group 3",
        wxPoint(204, 200), wxSize(468, 31), wxTE_READONLY | wxBORDER_NONE | wxTE_MULTILINE | wxTE_NO_VSCROLL);
    wxFont sndsen_font = wxFont(13, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_EXTRALIGHT);
    sndsen->SetFont(sndsen_font);
    sndsen->SetBackgroundColour(wxColor(255, 250, 230));
    sndsen->SetOwnForegroundColour(wxColour(100, 100, 100));
    //sentence under user button
    wxTextCtrl* usersen = new wxTextCtrl(yellowpanel, wxID_ANY, "To discover more about our project",
        wxPoint(164, 421), wxSize(388, 29), wxTE_READONLY | wxBORDER_NONE);
    wxFont usersen_font = wxFont(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRALIGHT);
    usersen->SetFont(usersen_font);
    usersen->SetBackgroundColour(wxColor(255, 250, 230));
    usersen->SetOwnForegroundColour(wxColour(96, 96, 96));
    //sentence under dark mode button
    wxTextCtrl* darksen = new wxTextCtrl(yellowpanel, wxID_ANY, "To turn to dark mode",
        wxPoint(960, 421), wxSize(388, 29), wxTE_READONLY | wxBORDER_NONE);
    darksen->SetFont(usersen_font);
    darksen->SetBackgroundColour(wxColor(255, 250, 230));
    darksen->SetOwnForegroundColour(wxColour(96, 96, 96));
    //user button
    wxBitmap usermanual(USERMANUAL_IMG, wxBITMAP_TYPE_PNG);
    wxBitmapButton* userbutton = new wxBitmapButton(yellowpanel, wxID_ANY, usermanual, wxPoint(243, 339), wxDefaultSize, wxBORDER_NONE);
    userbutton->SetBackgroundColour(wxColor(255, 250, 230));
    //dark mode button
    wxBitmap darkmode(DARKMODE_IMG, wxBITMAP_TYPE_PNG);
    wxBitmapButton* darkmode_button = new wxBitmapButton(yellowpanel, wxID_ANY, darkmode, wxPoint(986, 339), wxDefaultSize, wxBORDER_NONE);
    darkmode_button->SetBackgroundColour(wxColor(255, 250, 230));

    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);

    mainsizer->Add(topPanel, 0, wxEXPAND);
    mainsizer->Add(barPanel, 0, wxEXPAND);
    mainsizer->Add(greenpanel, 0, wxEXPAND);
    mainsizer->Add(yellowpanel, 1, wxEXPAND);

    this->SetSizerAndFit(mainsizer);
}
void MoreWindow::LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel)
{
    wxImage image(imagePath, wxBITMAP_TYPE_PNG);
    if (image.IsOk())
    {
        //
        //wxSize panelSize = panel->GetSize();
        //image.Rescale(panelSize.GetWidth(), panelSize.GetHeight(), wxIMAGE_QUALITY_HIGH);
        //
        wxBitmap bitmap(image);
        wxStaticBitmap* imageCtrl = new wxStaticBitmap(panel, wxID_ANY, bitmap);
        imageCtrl->SetPosition(position);
    }
    else {
        wxLogError("Failed to load image: %s", imagePath);
    }
}
void MoreWindow::LoadHeaderFooter(wxPanel* panel)
{
    LoadImage(HEADER_IMG, wxPoint(0, 0), panel);
}