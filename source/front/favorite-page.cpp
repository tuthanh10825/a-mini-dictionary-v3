#include "favorite-page.h"
#include <wx/statbmp.h>
#include <wx/wx.h>
enum butID {
    del_id = wxID_LAST + 1,
    sel_id
};

//clang-format off



; //clang-format on


ListWindow::ListWindow(wxWindow* parent) : wxWindow(parent, wxID_ANY) {
   
    wxPanel* subwindow = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 631));
    subwindow->SetBackgroundColour(wxColour(255, 255, 255));

    wxInitAllImageHandlers();
   


    wxPanel* bar = new wxPanel(subwindow, wxID_ANY, wxDefaultPosition, wxSize(-1,-1)); 
    bar->SetBackgroundColour(wxColour(33, 37, 79));

    wxFont pala; pala.SetNativeFontInfoUserDesc("Palatino Linotype 20 WINDOWS-1252"); 
    wxStaticText* wordText = new wxStaticText(bar, wxID_ANY, wxString("Word"), wxDefaultPosition, wxSize(311, -1), wxALIGN_CENTRE_HORIZONTAL);
    wordText->SetFont(pala); wordText->SetForegroundColour(wxColor(240, 240, 240)); 
    wxStaticText* typeText = new wxStaticText(bar, wxID_ANY, wxString("Type"), wxDefaultPosition, wxSize(80, -1), wxALIGN_CENTRE_HORIZONTAL);
    typeText->SetFont(pala); typeText->SetForegroundColour(wxColor(240, 240, 240));
    wxStaticText* defiText = new wxStaticText(bar, wxID_ANY, wxString("Definition"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL); 
    defiText->SetFont(pala); defiText->SetForegroundColour(wxColor(240, 240, 240));
    wxBoxSizer* barSizer = new wxBoxSizer(wxHORIZONTAL); 
    barSizer->Add(wordText, 0); 
    barSizer->Add(typeText, 0); 
    barSizer->Add(defiText, 1); 
    bar->SetSizerAndFit(barSizer); 

    m_item_list = new wxListCtrl(subwindow, wxID_ANY, wxPoint(43, 96), wxSize(1191, 502), wxLC_REPORT | wxLC_VRULES | wxLC_NO_HEADER);
    m_item_list->InsertColumn(0, "word", 0, 311);
    m_item_list->InsertColumn(1, "p.", 0, 80);
    m_item_list->InsertColumn(2, "definition", 0, 1500);
    
    //m_item_list->EnableCheckBoxes();
    wxFont font(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN);
    m_item_list->SetFont(font);
    m_item_list->SetTextColour(wxColour(60, 60, 60));
    m_item_list->SetBackgroundColour(wxColour(255, 255, 255));
    
    //loadFavListUnFinish();


    
    wxBitmapButton* delbutton = new wxBitmapButton(subwindow, del_id, wxBitmap(DELETEICON_IMG, wxBITMAP_TYPE_PNG), wxPoint(1300, 220), wxSize(88, 107));
    delbutton->SetBackgroundColour(wxColor(255, 255, 255));
    delbutton->Bind(wxEVT_BUTTON, &ListWindow::onDelClick, this);
    //bind the delbutton with wxEVT_
    
    //dark mode button
    
    wxBitmapButton* selbutton = new wxBitmapButton(subwindow, sel_id, wxBitmap(SELECTALLICON_IMG, wxBITMAP_TYPE_PNG), wxPoint(1300, 354), wxSize(88, 107));
    selbutton->SetBackgroundColour(wxColor(255, 255, 255));
    selbutton->Bind(wxEVT_BUTTON, &ListWindow::onSelClick, this);

    wxBoxSizer* rightControlSizer = new wxBoxSizer(wxVERTICAL);
   
    wxBoxSizer* buttonCentering1 = new wxBoxSizer(wxHORIZONTAL); 
    buttonCentering1->Add(delbutton, 0, wxALIGN_BOTTOM |  wxBOTTOM, 20);

    wxBoxSizer* buttonCentering2 = new wxBoxSizer(wxHORIZONTAL);
    buttonCentering2->Add(selbutton, 0, wxALIGN_TOP | wxTOP, 20);
    rightControlSizer->Add(buttonCentering1, 1); 
    rightControlSizer->Add(buttonCentering2, 1);

    wxBoxSizer* leftControlSizer = new wxBoxSizer(wxVERTICAL); 
    leftControlSizer->Add(bar, 0, wxEXPAND | wxTOP, 60);
    leftControlSizer->Add(m_item_list, 1, wxEXPAND | wxBOTTOM, 60);
    wxBoxSizer* totalSubPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    totalSubPanelSizer->Add(leftControlSizer, 1, wxEXPAND | wxLEFT, 100);
    totalSubPanelSizer->Add(rightControlSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 30); 
    subwindow->SetSizerAndFit(totalSubPanelSizer); 
    
  
    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL); 
    mainsizer->Add(subwindow, 1, wxEXPAND);

    this->SetSizerAndFit(mainsizer);
}

void ListWindow::loadFavListUnFinish() {

    //upgrade this: instead of load here, load from file. 
    for (int i = 0; i < 30; ++i) {
        m_item_list->InsertItem(i, "huh");
        m_item_list->SetItem(i, 1, "p.");
        m_item_list->SetItem(i++, 2, "ajghkdjfskjfsgjkdhjskdfhskjdghjgkjvjtvyjtvkuyvkskdjfsdjfsldkslkjdflkjdhlskfjdhlkdjslkfhsgkfhslkdfglskdfgl?");
        m_item_list->InsertItem(i, "a");
        m_item_list->SetItem(i, 1, ".");
        m_item_list->SetItem(i, 2, "1");
    }
}

void ListWindow::deleteSelectedRows() {
    long itemIndex = -1;
    while ((itemIndex = m_item_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
        m_item_list->DeleteItem(itemIndex);
        itemIndex = -1;
    }
}

void ListWindow::SelectAllRows() {
    long itemIndex = -1;
    while ((itemIndex = m_item_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL)) != wxNOT_FOUND) {
        m_item_list->SetItemState(itemIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
}


void ListWindow::onDelClick(wxCommandEvent& e) {
    deleteSelectedRows();
}

void ListWindow::onSelClick(wxCommandEvent&) {
    SelectAllRows();
}

