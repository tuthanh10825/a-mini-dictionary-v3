#include "favorite-page.h"


enum butID {
    del_id = wxID_LAST + 1,
    sel_id
};

//clang-format off

wxBEGIN_EVENT_TABLE(FavWindow, wxFrame)
EVT_BUTTON(del_id, FavWindow::onDelClick)
EVT_BUTTON(sel_id, FavWindow::onSelClick)
wxEND_EVENT_TABLE()


; //clang-format on


FavWindow::FavWindow(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* topPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 155));
    wxPanel* barPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 64));
    wxPanel* subwindow = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 631));
    subwindow->SetBackgroundColour(wxColour(255, 255, 255));

    wxInitAllImageHandlers();
    LoadImage(HEADER_IMG, wxPoint(0, 0), topPanel);
    LoadImage(NAVIGATIONBAR_IMG, wxPoint(0, 0), barPanel);
    //LoadImage("assets/favtool.png", wxPoint(1188, 50), subwindow);
    LoadImage(FAVOURITEBAR_IMG, wxPoint(43, 32), subwindow);


    m_item_list = new wxListCtrl(subwindow, wxID_ANY, wxPoint(43, 96), wxSize(1191, 502), wxLC_REPORT | wxLC_NO_HEADER);
    m_item_list->InsertColumn(0, "word", 0, 311);
    m_item_list->InsertColumn(1, "p.", 0, 80);
    m_item_list->InsertColumn(2, "definition", 0, 1500);
    //m_item_list->EnableCheckBoxes();
    wxFont font(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_THIN);
    m_item_list->SetFont(font);
    m_item_list->SetTextColour(wxColour(60, 60, 60));
    m_item_list->SetBackgroundColour(wxColour(255, 255, 255));

    loadFavListUnFinish();

    wxBitmap delbut(DELETEICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmapButton* delbutton = new wxBitmapButton(subwindow, del_id, delbut, wxPoint(1300, 220), wxSize(88, 107), wxBORDER_NONE);
    delbutton->SetBackgroundColour(wxColor(255, 255, 255));
    //dark mode button
    wxBitmap selbut(SELECTALLICON_IMG, wxBITMAP_TYPE_PNG);
    wxBitmapButton* selbutton = new wxBitmapButton(subwindow, sel_id, selbut, wxPoint(1300, 354), wxSize(88, 107), wxBORDER_NONE);
    selbutton->SetBackgroundColour(wxColor(255, 255, 255));

    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);

    mainsizer->Add(topPanel, 0, wxEXPAND);
    mainsizer->Add(barPanel, 0, wxEXPAND);
    mainsizer->Add(subwindow, 1, wxEXPAND);

    this->SetSizerAndFit(mainsizer);
}
void FavWindow::LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel)
{
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

void FavWindow::loadFavListUnFinish() {
    for (int i = 0; i < 30; ++i) {
        m_item_list->InsertItem(i, "huh");
        m_item_list->SetItem(i, 1, "p.");
        m_item_list->SetItem(i++, 2, "ajghkdjfskjfsgjkdhjskdfhskjdghjgkjvjtvyjtvkuyvkskdjfsdjfsldkslkjdflkjdhlskfjdhlkdjslkfhsgkfhslkdfglskdfgl?");
        m_item_list->InsertItem(i, "a");
        m_item_list->SetItem(i, 1, ".");
        m_item_list->SetItem(i, 2, "1");
    }
}

void FavWindow::deleteSelectedRows() {
    long itemIndex = -1;
    while ((itemIndex = m_item_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED)) != wxNOT_FOUND) {
        m_item_list->DeleteItem(itemIndex);
        itemIndex = -1;
    }
}

void FavWindow::SelectAllRows() {
    long itemIndex = -1;
    while ((itemIndex = m_item_list->GetNextItem(itemIndex, wxLIST_NEXT_ALL)) != wxNOT_FOUND) {
        m_item_list->SetItemState(itemIndex, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
}


void FavWindow::onDelClick(wxCommandEvent& e) {
    deleteSelectedRows();
}

void FavWindow::onSelClick(wxCommandEvent&) {
    SelectAllRows();
}

