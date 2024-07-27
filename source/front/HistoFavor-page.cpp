#include "HistoFavor-page.h"

HistoFavorWindow::HistoFavorWindow(wxWindow* parent) : wxScrolledWindow(parent, wxID_ANY) {
    wxFont cellFont;
    cellFont.SetNativeFontInfoUserDesc("Palatino Linotype 20 WINDOWS-1252");

    this->SetBackgroundColour(wxColour(255, 255, 255));

    wxGrid* grid = new wxGrid(this, wxID_ANY);
    grid->CreateGrid(20, 2);
    grid->SetFont(cellFont);
    grid->SetDefaultCellTextColour(wxColour(0, 0, 0)); 

    // Set column labels
    grid->SetColLabelValue(0, "Word");
    grid->SetColLabelValue(1, "Definition");

    // Set column label colors
    grid->SetLabelTextColour(wxColour(255, 255, 255));
    grid->SetLabelBackgroundColour(wxColour(33, 38, 79));
    grid->SetLabelFont(cellFont);


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
    int rowHeight = 40; // Desired row height in pixels
    for (int i = 0; i < 20; ++i) {
        grid->SetRowSize(i, rowHeight);
        grid->SetCellValue(i, 0, "  " + words[i] + " (" + types[i] + ")");
        grid->SetCellValue(i, 1, " " + definitions[i]);
        grid->SetCellFont(i, 0, cellFont);
        grid->SetCellFont(i, 1, cellFont);

        grid->SetCellBackgroundColour(i, 0, wxColour(255, 255, 200)); 
        grid->SetCellTextColour(i, 0, wxColour(4, 73, 153));

    }

    grid->AutoSizeColumns();

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Add grid with left and right margins
    wxBoxSizer* gridSizer = new wxBoxSizer(wxHORIZONTAL);
    gridSizer->AddSpacer(70); // Left margin
    gridSizer->Add(grid, 1, wxEXPAND);
    gridSizer->AddSpacer(20); // Right margin

    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);
    this->SetSizer(mainSizer);

    this->SetScrollRate(5, 5);
}
