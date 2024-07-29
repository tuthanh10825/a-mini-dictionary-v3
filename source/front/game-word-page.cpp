#include "game-word-page.h"
#include "properties.h"
Wgamewindow::Wgamewindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{

    // Initialize all image handlers
    wxInitAllImageHandlers();

    // Panel to load image
    wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition);
    wxPanel* panel = new wxPanel(this, wxID_ANY, wxDefaultPosition);


    // Load image for topPanel
    wxImage mark(MARK_IMG, wxBITMAP_TYPE_ANY);
    wxStaticBitmap* markDisplay = new wxStaticBitmap(this, wxID_ANY, wxBitmap(mark), wxDefaultPosition);

    wxImage guessword(GUESSWORD_IMG, wxBITMAP_TYPE_ANY);
    wxStaticBitmap* guesswordDisplay = new wxStaticBitmap(this, wxID_ANY, wxBitmap(guessword), wxDefaultPosition);

    wxTextCtrl* word = new wxTextCtrl(this, wxID_ANY, "An examination of somebody’s knowledge or ability, consisting of questions for them to answer or activities for them to perform",
        wxDefaultPosition, wxSize(1100, 88), wxTE_READONLY | wxBORDER_NONE | wxTE_MULTILINE | wxTE_NO_VSCROLL);
    word->SetBackgroundColour(wxColor(255, 255, 255));
    word->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    wxBoxSizer* vboxtop = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* vboxbot = new wxBoxSizer(wxHORIZONTAL);

    wxString labels[] = { "Test", "Pink Pony Club", "Santa Monica", "Chappell Roan" };
    wxFont font = wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    wxColour colours[] = {
        wxColour(236, 178, 179),
        wxColour(178, 236, 179),
        wxColour(187, 188, 246),
        wxColour(247, 247, 184)
    };
    for (int i = 0; i < 4; ++i) {

        wxPanel* subPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(524, 94));
        wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);
        RoundButton* btn = new RoundButton(subPanel, wxID_ANY, labels[i], colours[i], *wxBLACK, wxSize(524, 94), 20);
        /*wxBitmapButton* btn = new wxBitmapButton(subPanel, wxID_ANY, bitmaps[i], wxDefaultPosition);
        wxStaticText* textCtrl = new wxStaticText(subPanel, wxID_ANY, labels[i], wxDefaultPosition, wxSize(280, 54), wxTE_READONLY | wxBORDER_NONE);

        // Set background color
        if (i == 0) textCtrl->SetBackgroundColour(wxColor(236, 178, 179));
        else if (i == 1) textCtrl->SetBackgroundColour(wxColor(178, 236, 179));  // Corrected color
        else if (i == 2) textCtrl->SetBackgroundColour(wxColor(187, 188, 246));
        else if (i == 3) textCtrl->SetBackgroundColour(wxColor(184, 185, 247));
        textCtrl->SetFont(font);
        */
        hbox->Add(btn, 0, wxEXPAND | wxLEFT, 100);
        subPanel->SetSizer(hbox);

        if (i < 2) vboxtop->Add(subPanel, 1, wxEXPAND | wxALL, 5);
        else vboxbot->Add(subPanel, 1, wxEXPAND | wxALL, 5);

    }
    wxBoxSizer* vo = new wxBoxSizer(wxVERTICAL);
    vo->Add(vboxtop, 0, wxEXPAND);
    vo->Add(vboxbot, 0, wxEXPAND);
    panel->SetSizerAndFit(vo);
    // Sizer for the topPanel and topleftPanel
    wxBoxSizer* toprightsizer = new wxBoxSizer(wxVERTICAL);
    toprightsizer->Add(guesswordDisplay, 0, wxALIGN_LEFT);
    toprightsizer->Add(word, 0, wxEXPAND | wxTOP, 21);
    wxBoxSizer* topsizer = new wxBoxSizer(wxHORIZONTAL);
    topsizer->Add(markDisplay, 0, wxEXPAND | wxLEFT, 82);
    topsizer->Add(toprightsizer, 1, wxEXPAND | wxLEFT, 64);

    wxBitmap morequiz(MOREQUIZ_IMG, wxBITMAP_TYPE_PNG);
    wxBitmapButton* morequiz_button = new wxBitmapButton(this, wxID_ANY, morequiz, wxPoint(599, 550), wxDefaultSize, wxBORDER_NONE);
    morequiz_button->SetBackgroundColour(wxColor(255, 250, 230));

    // Main sizer
    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(topsizer, 0, wxEXPAND | wxTOP, 100);
    mainsizer->Add(panel, 0, wxEXPAND | wxTOP, 30);

    // Set the main sizer for the frame
    this->SetSizerAndFit(mainsizer);
}