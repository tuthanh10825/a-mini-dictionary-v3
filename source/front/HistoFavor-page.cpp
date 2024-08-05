#include "HistoFavor-page.h"


enum butID {
    del_id = wxID_LAST + 1,
    sel_id
};



HistoFavorWindow::HistoFavorWindow(wxWindow* parent) : wxScrolledWindow(parent, wxID_ANY) {

    
    
    wxPanel* subPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 631));
    subPanel->SetBackgroundColour(wxColour(255, 255, 255));
    this->SetBackgroundColour(wxColour(255, 255, 255));
    wxInitAllImageHandlers();
    





    wxFont cellFont;
    cellFont.SetNativeFontInfoUserDesc("Palatino Linotype 20 WINDOWS-1252");
    int colWidth = 700;

    grid = new wxGrid(subPanel, wxID_ANY, wxDefaultPosition, wxSize(1090, 1200));
    grid->CreateGrid(20, 2, wxGrid::wxGridSelectRows);

    //Grid Properties
    grid->EnableEditing(false);
    grid->SetSelectionBackground(wxColour(150, 150, 150));
    grid->EnableDragGridSize(false);
    grid->SetDefaultCellFont(cellFont);
    grid->SetDefaultCellTextColour(wxColour(0, 0, 0)); 
    grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTER);


    // Set column labels
    grid->SetColLabelValue(0, "Word");
    grid->SetColLabelValue(1, "Definition");

    // Set column label colors
    grid->SetColLabelSize(70);
    grid->SetLabelTextColour(wxColour(255, 255, 255));
    grid->SetLabelBackgroundColour(wxColour(33, 38, 79));
    grid->SetLabelFont(cellFont.Bold());

    


    // Sample data
    wxString words[20] = {
        "agree", "bat", "boat", "cat", "cut", "desk", "egg", "food",
        "grape", "house", "ink", "jump", "kite", "lamp", "mouse", "notebook",
        "orange", "pencil", "queen", "rabbit"
    };
    wxString definitions[20] = {
        "to have the same opinion as somebody",
        "an animal like a mouse with wings that flies and feeds at night",
        "a vehicle (smaller than a ship) that travels on water",
        "a small animal with soft fur that people often keep as a pet",
        "to divide something into two or more pieces with a knife, etc",
        "a piece of furniture like a table, often with drawers",
        "a bird’s egg",
        "things that people or animals eat",
        "a small, round, purple or green fruit that you can eat or make into wine",
        "a building for human habitation",
        "a colored fluid used for writing, drawing, printing, or duplicating",
        "to push yourself off the ground and into the air using your legs",
        "a toy made of a light frame covered with colored paper or plastic, that you fly in the air at the end of one or more long strings",
        "a device that produces light",
        "a small rodent that typically has a pointed snout, relatively large ears and eyes, and a long tail",
        "a book of blank pages for writing notes in",
        "a round, sweet, juicy fruit with a tough bright reddish-yellow rind",
        "an instrument for writing or drawing with ink or a similar substance",
        "the female ruler of an independent state, especially one who inherits the position by right of birth",
        "a small herbivorous mammal with long ears, long hind legs, and a short fluffy tail"
    };
    wxString types[20] = {
        "verb", "noun", "noun", "noun", "verb", "noun", "noun", "noun",
        "noun", "noun", "noun", "verb", "noun", "noun", "noun", "noun",
        "noun", "noun", "noun", "noun"
    };

    // Set row height
    //int rowHeight = 50; // Desired row height in pixels

    for (int i = 0; i < 20; ++i) {
        //grid->SetRowSize(i, rowHeight);
        grid->SetCellValue(i, 0, "  " + words[i] + " (" + types[i] + ")");
        grid->SetCellValue(i, 1, " " + definitions[i]);

        grid->SetCellRenderer(i, 1, new wxGridCellAutoWrapStringRenderer());
        grid->SetCellBackgroundColour(i, 0, wxColour(255, 255, 200)); 
        grid->SetCellTextColour(i, 0, wxColour(4, 73, 153));

    }

    grid->AutoSizeColumn(0);
    grid->SetColSize(1, colWidth);
    grid->AutoSizeRows();

    wxBitmapButton* delbutton = new wxBitmapButton(subPanel, del_id, wxBitmap(DELETEICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 107));
    delbutton->SetBackgroundColour(wxColor(255, 255, 255));
    delbutton->Bind(wxEVT_BUTTON, &HistoFavorWindow::onDelClick, this);
    //bind the delbutton with wxEVT_


    wxBitmapButton* selbutton = new wxBitmapButton(subPanel, sel_id, wxBitmap(SELECTALLICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 107));
    selbutton->SetBackgroundColour(wxColor(255, 255, 255));
    selbutton->Bind(wxEVT_BUTTON, &HistoFavorWindow::onSelClick, this);


    wxBoxSizer* rightControlSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* buttonCentering1 = new wxBoxSizer(wxHORIZONTAL);
    buttonCentering1->Add(delbutton, 0, wxALIGN_BOTTOM | wxBOTTOM, 20);

    wxBoxSizer* buttonCentering2 = new wxBoxSizer(wxHORIZONTAL);
    buttonCentering2->Add(selbutton, 0, wxALIGN_TOP | wxTOP, 20);
    rightControlSizer->Add(buttonCentering1, 1, wxEXPAND);
    rightControlSizer->Add(buttonCentering2, 1, wxEXPAND);

    wxBoxSizer* leftControlSizer = new wxBoxSizer(wxHORIZONTAL);
    leftControlSizer->Add(grid, wxSizerFlags().Proportion(1).Center().Border(wxALL, 30));
    wxBoxSizer* totalSubPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    totalSubPanelSizer->Add(leftControlSizer, 1, wxEXPAND | wxLEFT, 100);
    totalSubPanelSizer->Add(rightControlSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 30);
    subPanel->SetSizer(totalSubPanelSizer);
    totalSubPanelSizer->SetSizeHints(this);

    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(subPanel, 1, wxALIGN_CENTER);

    this->SetSizerAndFit(mainsizer);
    


    //this->SetScrollRate(5, 5);
}



bool HistoFavorWindow::loadData(std::string path)
{
    return false;
}

void HistoFavorWindow::deleteSelectedRows() {
    int rows = grid->GetNumberRows();
    for (int i = 0; i < rows; ++i) {
        if (grid->IsInSelection(i, 0)) {
            grid->DeleteRows(i, 1, false);
            --i;
            --rows;
        }
    }
}

void HistoFavorWindow::SelectAllRows() {
    grid->SelectAll();
}

void HistoFavorWindow::onDelClick(wxCommandEvent&) {
    deleteSelectedRows();
}

void HistoFavorWindow::onSelClick(wxCommandEvent&) {
    SelectAllRows();
}
