#include "BaseFrame.h"

BaseFrame::BaseFrame(const wxString& title, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
    SetSize(wxSize(WIDTH, HEIGHT));

    mainPanel = new wxPanel(this);
    mainPanel->SetBackgroundColour(WHITE);
    wxInitAllImageHandlers();

    LoadNavigation(mainPanel);
    LoadHeaderFooter(mainPanel);
   
    mainPanel->Layout();

    // 155 x 37
}

void BaseFrame::LoadHeaderFooter(wxPanel* panel) {
    LoadImage(HEADER_IMG, wxPoint(0, 0), panel);
    LoadImage(FOOTER_IMG, wxPoint(0, 811), panel);  // Adjust Y-coordinate as needed


}

void BaseFrame::LoadNavigation(wxPanel* panel)
{
    wxBitmap homeBtnBitmap(HOMEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap dictionaryBtnBitmap(SEARCHICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap gameBtnBitmap(GAMEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap historyBtnBitmap(HISTORYICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap favoriteBtnBitmap(FAVORITEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap moreBtnBitmap(MOREICON_IMG, wxBITMAP_TYPE_PNG);
    //wxBitmap homeBtnBitmap(HOMEICON_IMG, wxBITMAP_TYPE_PNG);


    // Create the bitmap button

    //wxBitmapButton* homeBtn = new wxBitmapButton(parent, wxID_ANY, homeBtnBitmap, wxDefaultPosition, wxSize(width, height));

    wxBitmapButton* homeBtn = new wxBitmapButton(panel, wxID_ANY, homeBtnBitmap, wxPoint(25, 170), wxSize(155, 45));
    wxBitmapButton* dictionaryBtn = new wxBitmapButton(panel, wxID_ANY, dictionaryBtnBitmap, wxPoint(260, 170));
    wxBitmapButton* gameBtn = new wxBitmapButton(panel, wxID_ANY, gameBtnBitmap, wxPoint(560, 170));
    wxBitmapButton* historyBtn = new wxBitmapButton(panel, wxID_ANY, historyBtnBitmap, wxPoint(805, 170));
    wxBitmapButton* favoriteBtn = new wxBitmapButton(panel, wxID_ANY, favoriteBtnBitmap, wxPoint(1022, 170), wxSize(180, 45));
    wxBitmapButton* moreBtn = new wxBitmapButton(panel, wxID_ANY, moreBtnBitmap, wxPoint(1275, 170), wxSize(155, 45));


    // Bind the click event to the handler
    homeBtn->Bind(wxEVT_BUTTON, &BaseFrame::OnHomeBtnClicked, this);

    LoadImage(LINE_IMG, wxPoint(0, 220), panel);
}

void BaseFrame::LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel) {
    wxImage image(imagePath, wxBITMAP_TYPE_PNG);
    if (image.IsOk()) {
        wxBitmap bitmap(image);
        wxStaticBitmap* imageCtrl = new wxStaticBitmap(panel, wxID_ANY, bitmap);
        imageCtrl->SetPosition(position);
    }
    else {
        wxLogError("Failed to load image: %s", imagePath);
    }
}

void BaseFrame::OnHomeBtnClicked(wxCommandEvent& event)
{
    //mainFrame* newFrame = new mainFrame("New Frame Title");
    //newFrame->Show();

    //// Optionally, hide the current frame
    //this->Hide();
}

