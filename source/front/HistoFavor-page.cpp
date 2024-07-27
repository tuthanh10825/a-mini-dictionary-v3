#include "HistoFavor-page.h"
#include "more-page.h"
#include "properties.h"

HistoFavorWindow::HistoFavorWindow(wxWindow* parent) : wxWindow(parent, wxID_ANY) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizerAndFit(mainSizer);
}
