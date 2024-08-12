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
#include "HistoFavor-page.h"
#include "favorite-page.h"
class BaseFrame : public wxFrame {
public:
    BaseFrame(const wxString& title);
    wxSimplebook* workingPage; 
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); 
    HomePage* homePage;
    SearchPage* searchPage;
    MoreWindow* moreWindow; 
    GameSettingPage* gameSettingPage; 
    HistoFavorWindow* historyPage;
    HistoFavorWindow* favouritePage;
private:

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
};

#endif // BASEFRAME_H
