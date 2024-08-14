#include "list-window.h"


enum butID {
    del_id = wxID_LAST + 1,
    sel_id
};



ListWindow::ListWindow(wxWindow* parent, int mode) : wxWindow(parent, wxID_ANY) {

    wxColour backgroundColour = wxColour(255, 255, 255), textColour = wxColour(0, 0, 0), nountext = wxColour(4, 73, 153), labelColour = wxColour(33, 38, 79), nounColour = wxColour(255, 221, 173), selectionCorlour = wxColour(166, 166, 166);
    if (mode) {
        backgroundColour = wxColour(16, 15, 28);
        textColour = wxColour(255, 255, 255);
        labelColour = wxColour(39, 37, 62);
        nounColour = wxColour(65, 64, 42);
        selectionCorlour = wxColour(37, 37, 48);
        nountext = wxColour(255, 255, 255);
    }
    
    
    wxPanel* subPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 631));
    subPanel->SetBackgroundColour(backgroundColour);
    this->SetBackgroundColour(backgroundColour);
    wxInitAllImageHandlers();

    wxFont cellFont;
    cellFont.SetNativeFontInfoUserDesc("Palatino Linotype 20 WINDOWS-1252");
    cellFont.Scale(0.85);
    int colWidth = 700;

    grid = new wxGrid(subPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));
    grid->CreateGrid(20, 2, wxGrid::wxGridSelectRows);

    //Grid Properties
    grid->EnableEditing(false);
    grid->SetSelectionBackground(selectionCorlour);
    grid->DisableDragColSize();
    grid->DisableDragGridSize();
    grid->SetDefaultCellFont(cellFont);
    grid->SetDefaultCellTextColour(textColour); 
    grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTER);
    grid->SetDefaultCellBackgroundColour(backgroundColour);

    // Set column labels
    grid->SetColLabelValue(0, "Word");
    grid->SetColLabelValue(1, "Definition");

    // Set column label colors
    grid->SetColLabelSize(70);
    grid->SetLabelTextColour(*wxWHITE);
    grid->SetLabelBackgroundColour(labelColour);
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
        
        grid->SetCellBackgroundColour(i, 0, nounColour); 
        grid->SetCellTextColour(i, 0, nountext);
      

    }
    
    grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
    grid->AutoSizeColumn(0);
    grid->SetColSize(1, 810);
    grid->AutoSizeRows();
   

    std::string s = std::to_string(mode);

    wxBitmapButton* delbutton = new wxBitmapButton(subPanel, del_id, wxBitmap(DELETEICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 79));
    delbutton->SetBackgroundColour(backgroundColour);
    delbutton->Bind(wxEVT_BUTTON, &ListWindow::onDelClick, this);
    wxStaticBitmap* delText = new wxStaticBitmap(subPanel, wxID_ANY, wxBitmap("assets/histofav/delete" + s + ".png", wxBITMAP_TYPE_PNG));


    wxBitmapButton* selbutton = new wxBitmapButton(subPanel, sel_id, wxBitmap(SELECTALLICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 79));
    selbutton->SetBackgroundColour(backgroundColour);
    selbutton->Bind(wxEVT_BUTTON, &ListWindow::onSelClick, this);
    wxStaticBitmap* selectText = new wxStaticBitmap(subPanel, wxID_ANY, wxBitmap("assets/histofav/selectall" + s + ".png", wxBITMAP_TYPE_PNG));


    wxBoxSizer* rightControlSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* buttonCentering1 = new wxBoxSizer(wxVERTICAL);
    buttonCentering1->Add(delbutton, 0, wxALIGN_CENTER);
    buttonCentering1->AddSpacer(5);
    buttonCentering1->Add(delText, 0, wxALIGN_CENTER);

    wxBoxSizer* buttonCentering2 = new wxBoxSizer(wxVERTICAL);
    buttonCentering2->Add(selbutton, 0, wxALIGN_CENTER);
    buttonCentering2->AddSpacer(5);
    buttonCentering2->Add(selectText, 0, wxALIGN_CENTER);

    rightControlSizer->AddStretchSpacer();
    rightControlSizer->Add(buttonCentering1, 1, wxEXPAND);
    rightControlSizer->Add(buttonCentering2, 1, wxEXPAND);
    rightControlSizer->AddStretchSpacer();


    wxBoxSizer* leftControlSizer = new wxBoxSizer(wxHORIZONTAL);
    leftControlSizer->Add(grid, 1, wxEXPAND | wxTOP | wxBOTTOM, 30);

    wxBoxSizer* totalSubPanelSizer = new wxBoxSizer(wxHORIZONTAL);
    totalSubPanelSizer->Add(leftControlSizer, 1, wxEXPAND | wxLEFT, 100);
    totalSubPanelSizer->Add(rightControlSizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 30);
    grid->Bind(wxEVT_SIZE, &ListWindow::OnSizeChange, this);
    subPanel->SetSizerAndFit(totalSubPanelSizer);
   

    wxBoxSizer* mainsizer = new wxBoxSizer(wxVERTICAL);
    mainsizer->Add(subPanel, 1, wxEXPAND);

    this->SetSizerAndFit(mainsizer);
   


    //this->SetScrollRate(5, 5);
}



bool ListWindow::loadData(std::string path)
{
    return false;
}

void ListWindow::deleteSelectedRows() {
    int rows = grid->GetNumberRows();
    for (int i = 0; i < rows; ++i) {
        if (grid->IsInSelection(i, 0)) {
            grid->DeleteRows(i, 1, false);
            --i;
            --rows;
        }
    }
}

void ListWindow::SelectAllRows() {
    grid->SelectAll();
}

void ListWindow::onDelClick(wxCommandEvent&) {
    deleteSelectedRows();
}

void ListWindow::onSelClick(wxCommandEvent&) {
    SelectAllRows();
}

void ListWindow::OnSizeChange(wxSizeEvent&)
{
    int trueSize = grid->GetVirtualSize().x - grid->GetColSize(0) - 85;
    grid->SetColSize(1, trueSize);
    grid->Refresh();
    return;
}
