#include "game-definition-page.h"
DefGameWindow::DefGameWindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

    // Initialize all image handlers
    wxInitAllImageHandlers();

    // Panel to load image
    wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    wxPanel* topleftPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);

    // Load image for topPanel
    wxImage image(GUESSDEFINITION, wxBITMAP_TYPE_ANY);
    wxStaticBitmap* imageDisplay = new wxStaticBitmap(topPanel, wxID_ANY, wxBitmap(image), wxDefaultPosition);

    // Load image and text for topleftPanel
    wxImage image2(LINE_IMG, wxBITMAP_TYPE_ANY);
    wxStaticBitmap* imageDisplay2 = new wxStaticBitmap(topleftPanel, wxID_ANY, wxBitmap(image2), wxDefaultPosition);
    wxTextCtrl* word = new wxTextCtrl(topleftPanel, wxID_ANY, "Test",
        wxDefaultPosition, wxSize(487, 65), wxTE_READONLY | wxBORDER_NONE | wxTE_CENTER);
    word->SetBackgroundColour(wxColor(255, 255, 255));
    word->SetFont(wxFont(35, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL));

    // Sizer for the topleftPanel
    wxBoxSizer* topleftsizer = new wxBoxSizer(wxVERTICAL);
    topleftsizer->Add(word, 0, wxEXPAND);
    topleftsizer->Add(imageDisplay2, 0, wxEXPAND);
    topleftPanel->SetSizerAndFit(topleftsizer);

    // Sizer for the topPanel and topleftPanel
    wxBoxSizer* topsizer = new wxBoxSizer(wxHORIZONTAL);
    topsizer->Add(topPanel, 0, wxEXPAND | wxLEFT, 60);
    topsizer->Add(topleftPanel, 0, wxEXPAND | wxLEFT, 10);




    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    wxFont font = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRALIGHT);
    //option in wxradiobox and can be wrapped into many lines
    std::vector<wxString> questions;
    wxString s = "An examination of somebody’s knowledge or ability, consisting of questions for them to answer or activities for them to perform";
    questions.push_back(s);
    questions.push_back(s);
    questions.push_back(s);
    questions.push_back(s);
    for (size_t i = 0; i < questions.size(); ++i)
    {
        wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
        //set first option the first choice
        wxRadioButton* rb = new wxRadioButton(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, i == 0 ? wxRB_GROUP : 0);
        wxStaticText* staticText = new wxStaticText(panel, wxID_ANY, questions[i], wxDefaultPosition, wxDefaultSize);
        staticText->SetFont(font);
        staticText->Wrap(1286); // Wrap text at 400 pixels width

        hbox->Add(rb, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
        hbox->Add(staticText, 1, wxALIGN_CENTER_VERTICAL | wxALL, 5);

        vbox->Add(hbox, 0, wxEXPAND | wxLEFT, 60);
    }

    panel->SetSizer(vbox);


    //morequiz button
    wxBitmap morequiz(MOREQUIZ_IMG, wxBITMAP_TYPE_PNG);
    wxBitmapButton* morequiz_button = new wxBitmapButton(this, wxID_ANY, morequiz, wxPoint(599, 565), wxDefaultSize, wxBORDER_NONE);
    morequiz_button->SetBackgroundColour(wxColor(255, 250, 230));
    // Main sizer
    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(topsizer, 0, wxEXPAND | wxTOP, 100);
    mainsizer->Add(panel, 0, wxEXPAND | wxTOP, 30);

    // Set the main sizer for the frame
    this->SetSizerAndFit(mainsizer);
}
void DefGameWindow::LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel)
{
    wxImage image(imagePath, wxBITMAP_TYPE_PNG);
    if (image.IsOk())
    {
        wxBitmap bitmap(image);
        wxStaticBitmap* imageCtrl = new wxStaticBitmap(panel, wxID_ANY, bitmap);
        imageCtrl->SetPosition(position);
    }
    else {
        wxLogError("Failed to load image: %s", imagePath);
    }
}
void DefGameWindow::OnRadioButton(wxCommandEvent& event)
{
    wxRadioButton* selected = dynamic_cast<wxRadioButton*>(event.GetEventObject());
    if (selected)
    {
        wxLogMessage("Selected: %s", selected->GetLabel());
    }
}