#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/scrolwin.h>
#include <vector>
#include <wx/bmpbuttn.h>
#include "properties.h" 
#include <wx/editlbox.h>
#include <wx/bitmap.h>
#include <wx/statbmp.h>

struct word {
	std::string word;
	std::string type;
	std::string definition;
};

class ListWindow : public wxWindow {
	public:
		ListWindow(wxWindow* parent, int mode);
private:
	std::vector<word> data;
	wxGrid* grid;

	// Need to implement
	bool loadData(std::string path);

	// Finished
	void deleteSelectedRows();
	void SelectAllRows();
	void onDelClick(wxCommandEvent&);
	void onSelClick(wxCommandEvent&);
	void OnSizeChange(wxSizeEvent&);

};