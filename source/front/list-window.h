#pragma once

#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <wx/bmpbuttn.h>
#include "properties.h" 
#include <wx/bitmap.h>
#include <wx/statbmp.h>
#include "fstream"
#include "Globals.h"

class ListWindow : public wxWindow {
	public:
		ListWindow(wxWindow* parent, int mode, int isFavor);
private:
	wxGrid* grid;

	// Need to implement
	// 
	// Finished
	bool loadDataToGrid(std::string path, int isFav);
	void deleteSelectedRows();
	void SelectAllRows();
	void onDelClick(wxCommandEvent&);
	void onSelClick(wxCommandEvent&);
	void OnSizeChange(wxSizeEvent&);

};