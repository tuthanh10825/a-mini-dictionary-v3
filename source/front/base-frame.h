#ifndef BASEFRAME_H
#define BASEFRAME_H
#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/simplebook.h>
#include "properties.h"
#include "home-page.h"
#include "search-page.h"
#include "game-setting-page.h"
#include "more-page.h"
#include "list-window.h"
#include "add-page.h"
class BaseFrame : public wxFrame {
public:
    BaseFrame(const wxString& title);
    wxSimplebook* workingPage; 
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 
    HomePage* homePage;
    SearchPage* searchPage;
    MoreWindow* moreWindow; 
    GameSettingPage* gameSettingPage; 
    ListWindow* historyPage;
    ListWindow* favouritePage;
    AddWindow* addpage;
private:

    wxBitmapButton* homeBtn; 
    wxBitmapButton* dictionaryBtn;
    wxBitmapButton* gameBtn;
    wxBitmapButton* historyBtn;
    wxBitmapButton* favoriteBtn;
    wxBitmapButton* moreBtn;
    wxPanel* leftHeaderPanel; 
    wxPanel* rightHeaderPanel; 
    wxPanel* naviPanel; 
    wxStaticBitmap* logoBitmap; 
 
    void LoadHeader();
    void loadFooter(); 
    void LoadNavigation();
    void LoadImage(const wxString& imagePath, wxPanel* panel);

    void OnHomeBtnClicked(wxCommandEvent& event);
    void OnDictionaryBtnClicked(wxCommandEvent&); 
    void OnGameBtnClicked(wxCommandEvent&); 
    void OnMoreBtnClicked(wxCommandEvent&);

    void OnHistoryBtnClicked(wxCommandEvent&);
    void OnFavouriteBtnClicked(wxCommandEvent&);

    void OnAddBtnClicked(wxCommandEvent&);
    void OnFlipColor(wxCommandEvent&); 
    void FlipColor();
    
    void OnCancelBtnClicked(wxCommandEvent&);
};

#endif // BASEFRAME_H
