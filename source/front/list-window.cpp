#include "list-window.h"


enum butID {
    del_id = wxID_LAST + 1,
    sel_id
};



ListWindow::ListWindow(wxWindow* parent, int mode, int isFavor) : wxWindow(parent, wxID_ANY) {


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

    wxFont::AddPrivateFont("fonts/pala.ttf");
    wxFont cellFont(25, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
    cellFont.Scale(0.85);
    int colWidth = 700;

    int numberOfWords = 0;

    if (isFavor) {
        if (dataFav.empty()) {
            loadData("data/favorite.txt", 1);
            numberOfWords = dataFav.size();
        }
    }
    else {
        if (dataHisto.empty()) {
            loadData("data/history.txt", 0);
        }
        numberOfWords = dataHisto.size();
    }

    grid = new wxGrid(subPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));
    grid->CreateGrid(numberOfWords, 2, wxGrid::wxGridSelectRows);

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


   
    //Set cell properties
    while (numberOfWords--) {
        std::string s = "";
        if (isFavor) {
            if (dataFav[numberOfWords].type != "") s = " (" + dataFav[numberOfWords].type + ")";

            grid->SetCellValue(numberOfWords, 0, wxString(una::utf8to16("  " + dataFav[numberOfWords].word + s)));
            grid->SetCellValue(numberOfWords, 1, wxString(una::utf8to16(" " + dataFav[numberOfWords].definition)));
            dataFav.pop_back();
        }
        else {
            if (dataHisto[numberOfWords].type != "") s = " (" + dataHisto[numberOfWords].type + ")";
            grid->SetCellValue(numberOfWords, 0, wxString(una::utf8to16("  " + dataHisto[numberOfWords].word + s)));
            grid->SetCellValue(numberOfWords, 1, wxString(una::utf8to16(" " + dataHisto[numberOfWords].definition)));
            dataHisto.pop_back();
        }
        grid->SetCellRenderer(numberOfWords, 1, new wxGridCellAutoWrapStringRenderer());
        grid->SetCellBackgroundColour(numberOfWords, 0, nounColour);
        grid->SetCellTextColour(numberOfWords, 0, nountext);

    }

   
    

    grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
    grid->AutoSizeColumn(0);
    grid->SetColSize(1, 810);
    grid->AutoSizeRows();
   

    std::string s = std::to_string(mode);

    wxBitmapButton* delbutton = new wxBitmapButton(subPanel, del_id, wxBitmap(DELETEICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 79), wxBORDER_NONE);
    delbutton->SetBackgroundColour(backgroundColour);
    delbutton->Bind(wxEVT_BUTTON, &ListWindow::onDelClick, this);
    wxStaticBitmap* delText = new wxStaticBitmap(subPanel, wxID_ANY, wxBitmap("assets/histofav/delete" + s + ".png", wxBITMAP_TYPE_PNG));


    wxBitmapButton* selbutton = new wxBitmapButton(subPanel, sel_id, wxBitmap(SELECTALLICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 79), wxBORDER_NONE);
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

void ListWindow::OnSizeChange(wxSizeEvent&) {
    int trueSize = grid->GetVirtualSize().x - grid->GetColSize(0) - 85;
    grid->SetColSize(1, trueSize);
    grid->Refresh();
    return;
}


void ListWindow::AppendRows(vector<word>& words) {
    int size = words.size();
    grid->InsertRows(0,size);
    for (int i = 0; i < size; ++i) {
        std::string s = "";
        if (words[i].type != "") s = " (" + words[i].type + ")";
        grid->SetCellValue(i, 0, wxString(una::utf8to16("  " + words[i].word + s)));
        grid->SetCellValue(i, 1, wxString(una::utf8to16(" " + words[i].definition)));
        grid->SetCellRenderer(i, 1, new wxGridCellAutoWrapStringRenderer());
        grid->SetCellBackgroundColour(i, 0, wxColour(255, 221, 173));
        grid->SetCellTextColour(i, 0, wxColour(4, 73, 153));
    }
    words.clear();
    grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
    grid->AutoSizeColumn(0);
    grid->SetColSize(1, 810);
    grid->AutoSizeRows();
}

bool ListWindow::loadData(std::string path, int isFav) {
    std::ifstream fin(path);
    if (fin.is_open()) {
        while (!fin.eof()) {
            word aWord;
            getline(fin, aWord.word, '(');
            getline(fin, aWord.type, ')');
            getline(fin, aWord.definition);
            while (aWord.definition[0] == ' ') aWord.definition.erase(0, 1);
            if (isFav) {
                dataFav.push_back(aWord);
            }
            else dataHisto.push_back(aWord);
        }
        fin.close();
        return true;
    }
    fin.close();
    return false;
}
