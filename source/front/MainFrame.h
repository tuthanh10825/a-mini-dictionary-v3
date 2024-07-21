#pragma once
#include <wx/wx.h>
#include "tst.h"
#include <wx/splitter.h>
class mainFrame : public wxFrame
{
	wxTextCtrl* definition;
	wxListBox* wordsList;
	wxTextCtrl* searchBox;
	TST storing;

	void printWord(wxCommandEvent& evt);
	void showDefi(wxCommandEvent& evt);
public: 
	mainFrame(const wxString& title);

};