#include "base-frame.h"


BaseFrame::BaseFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition) {

    wxInitAllImageHandlers();
    LoadHeader();
    workingPage = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT));
    
    
    homePage = new HomePage(workingPage); 
    workingPage->AddPage(homePage, wxString("Homepage")); 
    

    searchPage = new wxWindow(workingPage, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT)); 
    wxPanel* searchPanel = new wxPanel(searchPage, wxID_ANY); 

    wxBoxSizer* searchBarSizer = new wxBoxSizer(wxHORIZONTAL); 
    searchPanel->SetBackgroundColour(BLUEBLACK); 

    searchBox* box = new searchBox(searchPanel);
    searchBarSizer->Add(box, 1, wxEXPAND | wxALL, 15); 
    searchPanel->SetSizerAndFit(searchBarSizer); 

    resPage* res = new resPage(searchPage); 
    res->addingString(wxString("Hello\n\tnoun\n\ttesting"));
    wxBoxSizer* searchSizer = new wxBoxSizer(wxVERTICAL); 
    searchSizer->Add(searchPanel, 0, wxEXPAND); 
    searchSizer->Add(res, 1, wxEXPAND); 
    searchPage->SetSizerAndFit(searchSizer); 

    workingPage->AddPage(searchPage, wxString("Searchpage"));


    gameSettingPage = new GameSettingPage(workingPage); 
    workingPage->AddPage(gameSettingPage, wxString("GameSettingpage"));

    moreWindow = new MoreWindow(workingPage);
    workingPage->AddPage(moreWindow, wxString("more")); 

    historyPage = new HistoFavorWindow(workingPage, 0);
    workingPage->AddPage(historyPage, wxString("History"));

    favouritePage = new HistoFavorWindow(workingPage, 0);
    workingPage->AddPage(favouritePage, wxString("Favourite"));

    LoadNavigation(); 
    mainSizer->Add(workingPage, 1, wxEXPAND); 
    loadFooter();
  
    this->SetSizerAndFit(mainSizer); 
    // 155 x 37
}

void BaseFrame::LoadHeader()
{

    wxPanel* leftHeaderPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1156.5, 154.5));
    LoadImage(NAME_IMG, leftHeaderPanel);
    leftHeaderPanel->SetBackgroundColour(BLUEBLACK);

    wxPanel* rightHeaderPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 1156.5), wxSize(1451.25 - 1156.5, 154.5));
    LoadImage(LOGO_IMG, rightHeaderPanel);
    rightHeaderPanel->SetBackgroundColour(WHITE);

    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    headerSizer->Add(leftHeaderPanel, 1, wxEXPAND | wxALL);
    headerSizer->Add(rightHeaderPanel, 0, wxEXPAND | wxALL);
 
    mainSizer->Add(headerSizer, 0, wxALL | wxEXPAND);
}

void BaseFrame::loadFooter()
{
    wxPanel* footer = new wxPanel(this, wxID_ANY, wxPoint(0, 849.75), wxSize(1451.25, 30));
    footer->SetBackgroundColour(BLUEBLACK);
    LoadImage(FOOTER_IMG, footer);

    mainSizer->Add(footer, 0, wxALL | wxEXPAND); 
}
void BaseFrame::LoadNavigation()
{
    wxPanel* naviPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 156), wxSize(1451.25, 63.13), wxBORDER_SIMPLE);
    naviPanel->SetBackgroundColour(WHITE); 

    
    wxBitmap homeBtnBitmap(HOMEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap dictionaryBtnBitmap(SEARCHICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap gameBtnBitmap(GAMEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap historyBtnBitmap(HISTORYICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap favoriteBtnBitmap(FAVORITEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmap moreBtnBitmap(MOREICON_IMG, wxBITMAP_TYPE_PNG);
    //wxBitmap homeBtnBitmap(HOMEICON_IMG, wxBITMAP_TYPE_PNG);


    // Create the bitmap button

    //wxBitmapButton* homeBtn = new wxBitmapButton(parent, wxID_ANY, homeBtnBitmap, wxDefaultPosition, wxSize(width, height));

    
    double distance = (1451.25 / 6); 
    wxBitmapButton* homeBtn = new wxBitmapButton(naviPanel, wxID_ANY, homeBtnBitmap, wxDefaultPosition, wxSize((1451.25 / 6), 63.13));
    wxBitmapButton* dictionaryBtn = new wxBitmapButton(naviPanel, wxID_ANY, dictionaryBtnBitmap, wxPoint(distance,0), wxSize((1451.25 / 6), 63.13));
    wxBitmapButton* gameBtn = new wxBitmapButton(naviPanel, wxID_ANY, gameBtnBitmap, wxPoint(2 * distance, 0), wxSize(1451.25 /6, 63.13));
    wxBitmapButton* historyBtn = new wxBitmapButton(naviPanel, wxID_ANY, historyBtnBitmap, wxPoint(3 * distance, 0), wxSize(1451.25 / 6, 63.13));
    wxBitmapButton* favoriteBtn = new wxBitmapButton(naviPanel, wxID_ANY, favoriteBtnBitmap, wxPoint(4 * distance, 0), wxSize(1451.25 / 6, 63.13));
    wxBitmapButton* moreBtn = new wxBitmapButton(naviPanel, wxID_ANY, moreBtnBitmap, wxPoint(5 * distance, 0), wxSize(1451.25 / 6, 63.13));

    wxBoxSizer* horiNaviPanel = new wxBoxSizer(wxHORIZONTAL);

    horiNaviPanel->Add(homeBtn, 1);
    horiNaviPanel->Add(dictionaryBtn,1);
    horiNaviPanel->Add(gameBtn,1);
    horiNaviPanel->Add(historyBtn, 1);
    horiNaviPanel->Add(favoriteBtn, 1);
    horiNaviPanel->Add(moreBtn, 1);
   
    naviPanel->SetSizerAndFit(horiNaviPanel);
    /*wxPanel* upperLine = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1451.25, 1));
    upperLine->SetBackgroundColour(BLACK); 

    wxPanel* lowerLine = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1451.25, 1));
    lowerLine->SetBackgroundColour(BLACK);
    wxBoxSizer* vertNaviPanel = new wxBoxSizer(wxVERTICAL);
    vertNaviPanel->Add(horiNaviPanel, 0); 
   */
    //mainSizer->Add(upperLine, 0, wxALL | wxEXPAND);
    mainSizer->Add(naviPanel, 0, wxALL | wxEXPAND);
    //mainSizer->Add(lowerLine, 0, wxALL | wxEXPAND);


    // Bind the click event to the handler
    homeBtn -> Bind(wxEVT_BUTTON, &BaseFrame::OnHomeBtnClicked, this);
    dictionaryBtn->Bind(wxEVT_BUTTON, &BaseFrame::OnDictionaryBtnClicked, this);
    gameBtn->Bind(wxEVT_BUTTON, &BaseFrame::OnGameBtnClicked, this); 
    moreBtn->Bind(wxEVT_BUTTON, &BaseFrame::OnMoreBtnClicked, this); 
    historyBtn->Bind(wxEVT_BUTTON, &BaseFrame::OnHistoryBtnClicked, this); 
    favoriteBtn->Bind(wxEVT_BUTTON, &BaseFrame::OnFavouriteBtnClicked, this);
}


void BaseFrame::LoadImage(const wxString& imagePath, wxPanel* panel) {
    wxImage image(imagePath, wxBITMAP_TYPE_PNG);
    if (image.IsOk()) {
        wxBitmap bitmap(image);
        wxStaticBitmap* imageCtrl = new wxStaticBitmap(panel, wxID_ANY, bitmap);

        wxBoxSizer* vertSizer = new wxBoxSizer(wxVERTICAL); 
        vertSizer->Add(imageCtrl, 0, wxALIGN_CENTER|wxTOP,4); 

        wxBoxSizer* horiSizer = new wxBoxSizer(wxHORIZONTAL); 
        horiSizer->Add(vertSizer, 1, wxALIGN_CENTER); 
        panel->SetSizerAndFit(horiSizer); 
    }
    else {
        wxLogError("Failed to load image: %s", imagePath);
    }
}

void BaseFrame::OnHomeBtnClicked(wxCommandEvent& event)
{
    workingPage->ChangeSelection(0); 
}

void BaseFrame::OnDictionaryBtnClicked(wxCommandEvent&)
{
    workingPage->ChangeSelection(1); 
}

void BaseFrame::OnGameBtnClicked(wxCommandEvent&)
{
    workingPage->ChangeSelection(2); 
}

void BaseFrame::OnMoreBtnClicked(wxCommandEvent&)
{
    workingPage->ChangeSelection(3); 
}

void BaseFrame::OnHistoryBtnClicked(wxCommandEvent&) {
    workingPage->ChangeSelection(4);
}

void BaseFrame::OnFavouriteBtnClicked(wxCommandEvent&) {
    workingPage->ChangeSelection(5);
}