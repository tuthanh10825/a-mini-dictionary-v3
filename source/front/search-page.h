#include "properties.h"
#include <wx/wx.h>
#include <wx/bmpcbox.h>
#include <wx/fontutil.h>

class searchBox : public wxWindow
{
public: 
	wxFont pala;
	wxBitmapComboBox* wordOrDefi= new wxBitmapComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	wxBitmapComboBox* language = new wxBitmapComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	wxTextCtrl* findBox = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH2); 
	wxBitmapButton* searchButton; 
	wxBitmapButton* randomButton; 
	wxBitmapButton* resetButton; 
	wxBitmapButton* addButton; 
	searchBox(wxWindow*); 
};

class resPage : public wxWindow
{
public: 
	wxBitmapButton* editButton; 
	wxBitmapButton* favorButton; 
	wxBitmapButton* removeButton;
	wxFont cas; 
	wxTextCtrl* resWord = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY); 
	resPage(wxWindow*); 

	void addingString(wxString); 
	void clearScreen(); 
	
};