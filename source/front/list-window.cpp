#include "list-window.h"


enum butID {
    del_id = wxID_LAST + 1,
    sel_id
};


ListWindow::ListWindow(wxWindow* parent, int isFavor) : wxWindow(parent, wxID_ANY) {
    if (!isFavor) isFav = isFavor;

    wxColour backgroundColor = LIGHTMODE_backgroundANDNaviColor, 
        textBlackColour = LIGHTMODE_blackTextColor, 
        blueTextColor = LIGHTMODE_blueTextColor, 
        labelColor = LIGHTMODE_labelANDHeaderColor, 
        backgroundYellowColor = LIGHTMODE_backgroundYellowColor, 
        selectionCorlor = LIGHTMODE_selectionGrayCorlor;
    if (!LIGHTMODE) {
        backgroundColor = DARKMODE_backgroundColor;
        textBlackColour = DARKMODE_whiteTextColor;
        labelColor = DARKMODE_labelANDNaviColor;
        backgroundYellowColor = DARKMODE_backgroundYellowColor;
        selectionCorlor = DARKMODE_selectionPurpleCorlor;
        blueTextColor = DARKMODE_whiteTextColor;
    }
    
    
    subPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0), wxSize(1451, 631));
    subPanel->SetBackgroundColour(backgroundColor);
    this->SetBackgroundColour(backgroundColor);
    wxInitAllImageHandlers();

    wxFont::AddPrivateFont("fonts/pala.ttf");
    wxFont cellFont(25, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_LIGHT, false, "Palatino Linotype");
    cellFont.Scale(0.85);
    int colWidth = 700;

    int numberOfWords = 0;

    if (isFavor) {
        if (!isLoaded) {
            loadData("data/favorite.txt", 1);
            numberOfWords = dataFav.size();
            isLoaded = true;
        }
    }
    else {
        if (!isLoaded) {
            loadData("data/history.txt", 0);
            isLoaded = true;
        }
        numberOfWords = dataHisto.size();
    }

    grid = new wxGrid(subPanel, wxID_ANY, wxDefaultPosition, wxSize(-1, -1));
    grid->CreateGrid(numberOfWords, 2, wxGrid::wxGridSelectRows);

    //Grid Properties
    grid->EnableEditing(false);
    grid->SetSelectionBackground(selectionCorlor);
    grid->DisableDragColSize();
    grid->DisableDragGridSize();
    grid->SetDefaultCellFont(cellFont);
    grid->SetDefaultCellTextColour(textBlackColour); 
    grid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_CENTER);
    grid->SetDefaultCellBackgroundColour(backgroundColor);

    // Set column labels
    grid->SetColLabelValue(0, "Word");
    grid->SetColLabelValue(1, "Definition");

    // Set column label colors
    grid->SetColLabelSize(70);
    grid->SetLabelTextColour(*wxWHITE);
    grid->SetLabelBackgroundColour(labelColor);
    grid->SetLabelFont(cellFont.Bold());


   
    //Set cell properties
    while (numberOfWords--) {
        std::string s = "";
        if (isFavor) {
            if (dataFav[numberOfWords].type != "") s = " (" + dataFav[numberOfWords].type + ")";
            grid->SetCellValue(numberOfWords, 0, wxString(una::utf8to16("  " + dataFav[numberOfWords].word + s)));
            grid->SetCellValue(numberOfWords, 1, wxString(una::utf8to16(" " + dataFav[numberOfWords].definition)));
            data.push_back(dataFav[numberOfWords]);
            dataFav.pop_back();
        }
        else {
            if (dataHisto[numberOfWords].type != "") s = " (" + dataHisto[numberOfWords].type + ")";
            grid->SetCellValue(numberOfWords, 0, wxString(una::utf8to16("  " + dataHisto[numberOfWords].word + s)));
            grid->SetCellValue(numberOfWords, 1, wxString(una::utf8to16(" " + dataHisto[numberOfWords].definition)));
            data.push_back(dataHisto[numberOfWords]);
            dataHisto.pop_back();
        }
        grid->SetCellRenderer(numberOfWords, 1, new wxGridCellAutoWrapStringRenderer());
        grid->SetCellBackgroundColour(numberOfWords, 0, backgroundYellowColor);
        grid->SetCellTextColour(numberOfWords, 0, blueTextColor);

    }

   
    

    grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
    grid->AutoSizeColumn(0);
    grid->SetColSize(1, 810);
    grid->AutoSizeRows();
   
    std::string s;

    if (LIGHTMODE) s = '0'; else s = '1';
    delbutton = new wxBitmapButton(subPanel, del_id, wxBitmap(DELETEICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 79), wxBORDER_NONE);
    delbutton->SetBackgroundColour(backgroundColor);
    delbutton->Bind(wxEVT_BUTTON, &ListWindow::onDelClick, this);
    delText = new wxStaticBitmap(subPanel, wxID_ANY, wxBitmap("assets/histofav/delete" + s + ".png", wxBITMAP_TYPE_PNG));


    selbutton = new wxBitmapButton(subPanel, sel_id, wxBitmap(SELECTALLICON_IMG, wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(79, 79), wxBORDER_NONE);
    selbutton->SetBackgroundColour(backgroundColor);
    selbutton->Bind(wxEVT_BUTTON, &ListWindow::onSelClick, this);
    selectText = new wxStaticBitmap(subPanel, wxID_ANY, wxBitmap("assets/histofav/selectall" + s + ".png", wxBITMAP_TYPE_PNG));


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
            data.erase(data.begin() + rows - i - 1);
            --i;
            --rows;
        }
    }
    if (isFav) {
        saveData2File("data/favorite.txt");
    }
    else saveData2File("data/history.txt");
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

/*

void ListWindow::AppendRows(vector<word>& words, int isFav) {
    if (!isLoaded) {
        if (isFav) {
            loadData("data/favorite.txt", 1);
            isLoaded = true;
        }
    }
    else {
        if (!isLoaded) {
            loadData("data/history.txt", 0);
            isLoaded = true;
        }
    }
    int size = words.size();

    grid->InsertRows(0,size);
    for (int i = size - 1; i >= 0; --i) {
        std::string s = "";
        if (words[i].type != "") s = " (" + words[i].type + ")";
        grid->SetCellValue(i, 0, wxString(una::utf8to16("  " + words[i].word + s)));
        grid->SetCellValue(i, 1, wxString(una::utf8to16(" " + words[i].definition)));
        grid->SetCellRenderer(i, 1, new wxGridCellAutoWrapStringRenderer());
        grid->SetCellBackgroundColour(i, 0, wxColour(255, 221, 173));
        grid->SetCellTextColour(i, 0, wxColour(4, 73, 153));
        data.push_back(words[i]);
    }
    words.clear();
    grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
    grid->AutoSizeColumn(0);
    grid->SetColSize(1, 810);
    grid->AutoSizeRows();
}








void ListWindow::AppendRows(vector<word>& words, int isFav) {
    if (!isLoaded) {
        if (isFav) {
            loadData("data/favorite.txt", 1);
            isLoaded = true;
        }
    }
    else {
        if (!isLoaded) {
            loadData("data/history.txt", 0);
            isLoaded = true;
        }
    }


    int size = words.size();
    int rows = data.size();
    for (int i = size - 1; i >=0; --i) {
        bool INFLAG = true;
        for (int j = 0; j < rows; ++j) {
            if (words[i].word == data[j].word) {
                INFLAG = false;
                break;
            }
        }

        if (INFLAG) {
            rows++;
            grid->InsertRows(0, 1);
            std::string s = "";
            if (words[i].type != "") s = " (" + words[i].type + ")";
            grid->SetCellValue(i, 0, wxString(una::utf8to16("  " + words[i].word + s)));
            grid->SetCellValue(i, 1, wxString(una::utf8to16(" " + words[i].definition)));
            grid->SetCellRenderer(i, 1, new wxGridCellAutoWrapStringRenderer());
            grid->SetCellBackgroundColour(i, 0, wxColour(255, 221, 173));
            grid->SetCellTextColour(i, 0, wxColour(4, 73, 153));
            data.push_back(words[i]);
        }
    }


    words.clear();
    grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
    grid->AutoSizeColumn(0);
    grid->SetColSize(1, 810);
    grid->AutoSizeRows();
}

*/



void ListWindow::AppendRows(vector<word>& words, int isFav) {
    if (!isLoaded) {
        if (isFav) {
            loadData("data/favorite.txt", 1);
            isLoaded = true;
        }
    }
    else {
        if (!isLoaded) {
            loadData("data/history.txt", 0);
            isLoaded = true;
        }
    }


    int size = words.size(), rows = data.size(), count = 0;
    for (int i = 0; i < size; ++i) {
        bool INFLAG = true;
        for (int j = rows - 1; j >= 0; --j) {
            if (words[i].word == data[j].word and words[i].type==data[j].type) {
                INFLAG = false;
                break;
            }
        }
        if (INFLAG) {
            rows++;
            data.push_back(words[i]);
            ++count;
        }
        
    }

    if (count != 0) {
        grid->InsertRows(0, count);
        for (int i = 0; i < count; ++i) {
            std::string s = "";
            if (data[rows - i - 1].type != "") s = " (" + data[rows - i - 1].type + ")";
            grid->SetCellValue(i, 0, wxString(una::utf8to16("  " + data[rows- i - 1].word + s)));
            grid->SetCellValue(i, 1, wxString(una::utf8to16(" " + data[rows - i - 1].definition)));
            grid->SetCellRenderer(i, 1, new wxGridCellAutoWrapStringRenderer());
            grid->SetCellBackgroundColour(i, 0, LIGHTMODE_backgroundYellowColor);   
            grid->SetCellTextColour(i, 0, wxColour(4, 73, 153));
            if (!LIGHTMODE) {
                grid->SetCellBackgroundColour(i, 0, DARKMODE_backgroundYellowColor);
                grid->SetCellTextColour(i, 0, DARKMODE_whiteTextColor);
            }
        }

        words.clear();
        grid->SetMargins(0 - wxSYS_VSCROLL_X, 0 - wxSYS_HSCROLL_Y);
        grid->AutoSizeColumn(0);
        grid->SetColSize(1, 810);
        grid->AutoSizeRows();
        if (isFav) {
            saveData2File("data/favorite.txt");
        }
        else saveData2File("data/history.txt");
    }
    
}

void ListWindow::FlipColor()
{
    wxColour backgroundColor = LIGHTMODE_backgroundANDNaviColor,
        textBlackColour = LIGHTMODE_blackTextColor,
        blueTextColor = LIGHTMODE_blueTextColor,
        labelColor = LIGHTMODE_labelANDHeaderColor,
        backgroundYellowColor = LIGHTMODE_backgroundYellowColor,
        selectionCorlor = LIGHTMODE_selectionGrayCorlor;
    if (!LIGHTMODE) {
        backgroundColor = DARKMODE_backgroundColor;
        textBlackColour = DARKMODE_whiteTextColor;
        labelColor = DARKMODE_labelANDNaviColor;
        backgroundYellowColor = DARKMODE_backgroundYellowColor;
        selectionCorlor = DARKMODE_selectionPurpleCorlor;
        blueTextColor = DARKMODE_whiteTextColor;
    }
    subPanel->SetBackgroundColour(backgroundColor);
    this->SetBackgroundColour(backgroundColor);

    std::string s;
    if (LIGHTMODE) s = '0'; else s = '1';
    delText->SetBitmap(wxBitmap("assets/histofav/delete" + s + ".png", wxBITMAP_TYPE_PNG));
    selectText->SetBitmap(wxBitmap("assets/histofav/selectall" + s + ".png", wxBITMAP_TYPE_PNG));
    delbutton->SetBackgroundColour(backgroundColor);
    selbutton->SetBackgroundColour(backgroundColor);
    grid->SetSelectionBackground(selectionCorlor);
    grid->SetDefaultCellTextColour(textBlackColour);
    grid->SetDefaultCellBackgroundColour(backgroundColor);
    for (int i = 0; i < grid->GetNumberRows(); ++i)
    {
        grid->SetCellBackgroundColour(i, 0, backgroundYellowColor);
        grid->SetCellTextColour(i, 0, blueTextColor);
    }
    this->Refresh();

}


bool ListWindow::loadData(std::string path, int isFav) {
    std::ifstream fin(path);
    if (fin.is_open()) {
        word aWord;
        getline(fin, aWord.word, '#');
        while (!fin.eof()) {
            getline(fin, aWord.type, '#');
            getline(fin, aWord.definition, '~');
            fin.get();
            while (aWord.definition[0] == ' ') aWord.definition.erase(0, 1);
            if (isFav) {
                dataFav.push_back(aWord);
            }
            else dataHisto.push_back(aWord);
            getline(fin, aWord.word, '#');
        }
        fin.close();
        return true;
    }
    fin.close();
    return false;
}

/*
* 
bool ListWindow::loadData(std::string path, int isFav) {
    std::ifstream fin(path);
    if (fin.is_open()) {
        word aWord;
        getline(fin, aWord.word, '#');
        while (!fin.eof()) {
            getline(fin, aWord.word, '#');
            getline(fin, aWord.type, '#');
            getline(fin, aWord.definition, '~');
            fin.get();
            while (aWord.definition[0] == ' ') aWord.definition.erase(0, 1);
            if (isFav) {
                dataFav.push_back(aWord);
            }
            else dataHisto.push_back(aWord);
            getline(fin, aWord.word, '#');
        }
        fin.close();
        return true;
    }
    fin.close();
    return false;
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
*/


bool ListWindow::saveData2File(std::string path) {
    std::ofstream fout(path);
    if (fout.is_open()) {
        int size = data.size();
        for (int i = size-1; i >=0; --i) {
            fout << data[i].word << "#" << data[i].type << "#" << data[i].definition << "~\n";
        }
        fout.close();
        return true;
    }
    fout.close();
    return false;
}