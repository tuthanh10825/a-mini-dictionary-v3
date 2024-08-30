#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <wx/bmpbuttn.h>
#include "properties.h" 
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include "fstream"
#include <string>
#include "Globals.h"

class ListWindow : public wxWindow {
public:
	ListWindow(wxWindow* parent, int isFavor);
	void AppendRows(vector<word>& words, int isFav);
	wxGrid* grid;
	void FlipColor();
	bool saveData2File(std::string path);
private:
	bool isLoaded = false, isFav = true;
	// Need to implement
	vector<word> data;
	// Finished
	bool loadData(std::string path, int isFav);
	void deleteSelectedRows();
	void SelectAllRows();
	void onDelClick(wxCommandEvent&);
	void onSelClick(wxCommandEvent&);
	void OnSizeChange(wxSizeEvent&);

	wxPanel* subPanel; 
	wxBitmapButton* delbutton;
	wxBitmapButton* selbutton; 
	wxStaticBitmap* delText; 
	wxStaticBitmap* selectText;
};