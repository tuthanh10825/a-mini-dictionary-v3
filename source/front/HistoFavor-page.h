#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/scrolwin.h>
#include <vector>

struct word {
	std::string word;
	std::string type;
	std::string definition;
};

class HistoFavorWindow : public wxScrolledWindow {
private:
	std::vector<word> data;
public:
	HistoFavorWindow(wxWindow* parent);

	// Need to implement
	bool loadData(std::string path);
	//~HistoFavorWindow();
};