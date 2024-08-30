#include "base-frame.h"


BaseFrame::BaseFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition) {

    wxInitAllImageHandlers();
    LoadHeader();
    workingPage = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxSize(WIDTH, HEIGHT));
    
    
    homePage = new HomePage(workingPage); 
    workingPage->AddPage(homePage, wxString("Homepage")); 
    

    searchPage = new SearchPage(workingPage);
    workingPage->AddPage(searchPage, wxString("Searchpage"));

    gameSettingPage = new GameSettingPage(workingPage); 
    workingPage->AddPage(gameSettingPage, wxString("GameSettingpage"));

    moreWindow = new MoreWindow(workingPage);
    workingPage->AddPage(moreWindow, wxString("more")); 

    historyPage = new ListWindow(workingPage, 0);
    workingPage->AddPage(historyPage, wxString("History"));

    favouritePage = new ListWindow(workingPage, 1);
    workingPage->AddPage(favouritePage, wxString("Favourite"));

    addpage = new AddWindow(workingPage);
    workingPage->AddPage(addpage, wxString("Add"));
    addpage->cancelbutton->Bind(wxEVT_BUTTON, &BaseFrame::OnCancelBtnClicked, this);

    LoadNavigation(); 
    mainSizer->Add(workingPage, 1, wxEXPAND); 
    loadFooter();
  
    this->homePage->quizButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {this->workingPage->ChangeSelection(2); });
    this->homePage->favorButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent&) {this->workingPage->ChangeSelection(5); });
    this->homePage->randomButton->Bind(wxEVT_BUTTON, [this](wxCommandEvent& evt)
        {
            this->searchPage->OnRandomBtnClicked(evt);
            this->workingPage->ChangeSelection(1);
        });
    this->searchPage->box->addButton->Bind(wxEVT_BUTTON, &BaseFrame::OnAddBtnClicked, this);
    this->moreWindow->darkmodeButton->Bind(wxEVT_BUTTON, &BaseFrame::OnFlipColor, this);
    this->Bind(wxEVT_CLOSE_WINDOW, [=](wxCloseEvent&)
        {
            historyPage->AppendRows(dataHisto, 0);
            favouritePage->AppendRows(dataFav, 1);
            historyPage->saveData2File(HISTOFILE);
            favouritePage->saveData2File(FAVFILE);
            this->Destroy();
        });
    this->SetSizerAndFit(mainSizer); 
    // 155 x 37
   
}

void BaseFrame::LoadHeader()
{

    leftHeaderPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1156.5, 154.5));
    LoadImage(NAME_IMG, leftHeaderPanel);
   
    if (LIGHTMODE) {
        leftHeaderPanel->SetBackgroundColour(LIGHTMODE_labelANDHeaderColor);
    }
    else leftHeaderPanel->SetBackgroundColour(DARKMODE_HeaderColor);

    rightHeaderPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 1156.5), wxSize(1451.25 - 1156.5, 154.5));
    std::string s = LIGHTMODE ? "" : "1";
    logoBitmap = new wxStaticBitmap(rightHeaderPanel, wxID_ANY, wxBitmap("assets/logo" + s + ".png", wxBITMAP_TYPE_PNG), wxDefaultPosition, wxDefaultSize);

    if (LIGHTMODE) {

        rightHeaderPanel->SetBackgroundColour(LIGHTMODE_backgroundANDNaviColor);
    } else rightHeaderPanel->SetBackgroundColour(DARKMODE_backgroundColor);
    

    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    headerSizer->Add(leftHeaderPanel, 1, wxEXPAND | wxALL);
    headerSizer->Add(rightHeaderPanel, 0, wxEXPAND | wxALL);
 
    mainSizer->Add(headerSizer, 0, wxALL | wxEXPAND);

}

void BaseFrame::loadFooter()
{
    wxPanel* footer = new wxPanel(this, wxID_ANY, wxPoint(0, 849.75), wxSize(1451.25, 30));
    footer->SetBackgroundColour(LIGHTMODE_labelANDHeaderColor);
    LoadImage(FOOTER_IMG, footer);

    mainSizer->Add(footer, 0, wxALL | wxEXPAND); 
}
void BaseFrame::LoadNavigation()
{
    naviPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 156), wxSize(1451.25, 63.13), wxBORDER_SIMPLE);
    
    wxColour background; 

    if (LIGHTMODE) {
        background = LIGHTMODE_backgroundANDNaviColor;
    }
    else background = (DARKMODE_backgroundColor);
    naviPanel->SetBackgroundColour(background);
   
    std::string s;
    if (LIGHTMODE) s = ""; else s = '1';
    wxBitmap homeBtnBitmap("assets/icons/home-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap dictionaryBtnBitmap("assets/icons/search-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap gameBtnBitmap("assets/icons/game-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap historyBtnBitmap("assets/icons/history-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap favoriteBtnBitmap("assets/icons/favourite-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap moreBtnBitmap("assets/icons/more-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    //wxBitmap homeBtnBitmap(HOMEICON_IMG, wxBITMAP_TYPE_PNG);


    // Create the bitmap button

    //wxBitmapButton* homeBtn = new wxBitmapButton(parent, wxID_ANY, homeBtnBitmap, wxDefaultPosition, wxSize(width, height));
    
    double distance = (1451.25 / 6); 
    homeBtn = new wxBitmapButton(naviPanel, wxID_ANY, homeBtnBitmap, wxDefaultPosition, wxSize((1451.25 / 6), 63.13));
    dictionaryBtn = new wxBitmapButton(naviPanel, wxID_ANY, dictionaryBtnBitmap, wxPoint(distance,0), wxSize((1451.25 / 6), 63.13));
    gameBtn = new wxBitmapButton(naviPanel, wxID_ANY, gameBtnBitmap, wxPoint(2 * distance, 0), wxSize(1451.25 /6, 63.13));
    historyBtn = new wxBitmapButton(naviPanel, wxID_ANY, historyBtnBitmap, wxPoint(3 * distance, 0), wxSize(1451.25 / 6, 63.13));
    favoriteBtn = new wxBitmapButton(naviPanel, wxID_ANY, favoriteBtnBitmap, wxPoint(4 * distance, 0), wxSize(1451.25 / 6, 63.13));
    moreBtn = new wxBitmapButton(naviPanel, wxID_ANY, moreBtnBitmap, wxPoint(5 * distance, 0), wxSize(1451.25 / 6, 63.13));

    homeBtn->SetBackgroundColour(background);
    dictionaryBtn->SetBackgroundColour(background);
    gameBtn->SetBackgroundColour(background);
    historyBtn->SetBackgroundColour(background);
    favoriteBtn->SetBackgroundColour(background);
    moreBtn->SetBackgroundColour(background);

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
    searchPage->res->clearScreen();
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

void BaseFrame::OnHistoryBtnClicked(wxCommandEvent& evt) {
    historyPage->AppendRows(dataHisto, 0);
    favouritePage->AppendRows(dataFav, 1);
    int trueSize = historyPage -> grid->GetVirtualSize().x - historyPage -> grid->GetColSize(0) - 85;
    historyPage -> grid->SetColSize(1, trueSize);
    historyPage -> grid->ForceRefresh();
    workingPage->ChangeSelection(4);
}

void BaseFrame::OnFavouriteBtnClicked(wxCommandEvent&) {
    favouritePage->AppendRows(dataFav, 1);
    historyPage->AppendRows(dataHisto, 0);
    int trueSize = favouritePage->grid->GetVirtualSize().x - favouritePage->grid->GetColSize(0) - 85;
    favouritePage->grid->SetColSize(1, trueSize);
    favouritePage->grid->ForceRefresh();
    workingPage->ChangeSelection(5);
}
void BaseFrame::OnAddBtnClicked(wxCommandEvent&)
{
    workingPage->ChangeSelection(6);
}
void BaseFrame::OnCancelBtnClicked(wxCommandEvent&)
{
    searchPage->res->clearScreen();
    workingPage->ChangeSelection(1);
}
void BaseFrame::OnFlipColor(wxCommandEvent&)
{
    LIGHTMODE = !LIGHTMODE; 
    this -> FlipColor(); 
    this->homePage->FlipColor(); 
    this -> moreWindow->FlipColor(); 
    this->favouritePage->FlipColor(); 
    this->historyPage->FlipColor(); 
    this->searchPage->FlipColor();
    this->gameSettingPage->FlipColor();
    this->addpage->FlipColor();

   
}

void BaseFrame::FlipColor()
{
    wxColour background;

    if (LIGHTMODE) {
        background = LIGHTMODE_backgroundANDNaviColor;
    }
    else background = (DARKMODE_backgroundColor);

    if (LIGHTMODE) {
        leftHeaderPanel->SetBackgroundColour(LIGHTMODE_labelANDHeaderColor);
    }
    else leftHeaderPanel->SetBackgroundColour(DARKMODE_HeaderColor);
    leftHeaderPanel->Refresh();
    rightHeaderPanel->SetBackgroundColour(background);
    rightHeaderPanel->Refresh();

    naviPanel->SetBackgroundColour(background);
    naviPanel->Refresh();

    std::string s;
    if (LIGHTMODE) s = ""; else s = '1';
    wxBitmap homeBtnBitmap("assets/icons/home-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap dictionaryBtnBitmap("assets/icons/search-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap gameBtnBitmap("assets/icons/game-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap historyBtnBitmap("assets/icons/history-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap favoriteBtnBitmap("assets/icons/favourite-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    wxBitmap moreBtnBitmap("assets/icons/more-icon" + s + ".png", wxBITMAP_TYPE_PNG);
    
    logoBitmap->SetBitmap(wxBitmap("assets/logo" + s + ".png", wxBITMAP_TYPE_PNG));

    homeBtn->SetBitmapLabel(homeBtnBitmap);
    homeBtn->SetBackgroundColour(background);
    homeBtn->Refresh();

    dictionaryBtn->SetBitmapLabel(dictionaryBtnBitmap);
    dictionaryBtn->SetBackgroundColour(background);
    dictionaryBtn->Refresh();


    gameBtn->SetBitmapLabel(gameBtnBitmap);
    gameBtn->SetBackgroundColour(background);
    gameBtn->Refresh();

    historyBtn->SetBitmapLabel(historyBtnBitmap);
    historyBtn->SetBackgroundColour(background);
    historyBtn->Refresh();

    favoriteBtn->SetBitmapLabel(favoriteBtnBitmap);
    favoriteBtn->SetBackgroundColour(background);
    favoriteBtn->Refresh();

    moreBtn->SetBitmapLabel(moreBtnBitmap);
    moreBtn->SetBackgroundColour(background);
    moreBtn->Refresh();
}
