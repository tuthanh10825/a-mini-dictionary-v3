#include "properties.h"
#include <wx/wx.h>
#include <wx/bmpcbox.h>
#include <wx/fontutil.h>
#include "tst.h"
class searchBox : public wxWindow
{
public: 
	wxFont pala;
	wxComboBox* wordOrDefi= new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	wxComboBox* language = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxCB_READONLY);
	wxComboBox* findBox = new wxComboBox(this, wxID_ANY);
	wxBitmapButton* searchButton; 
	wxBitmapButton* randomButton; 
	wxBitmapButton* resetButton; 
	wxBitmapButton* addButton; 
	searchBox(wxWindow*); 
	bool isDropdown = false; 
private: 
};

class resPage : public wxWindow
{
public: 
	wxBitmapButton* editButton; 
	wxBitmapButton* favorButton; 
	wxBitmapButton* removeButton;
	wxFont font; 
	wxTextCtrl* resWord = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY); 
	resPage(wxWindow*); 

	void addingString(wxString); 
	void clearScreen(); 
	
};

class SearchPage : public wxWindow
{
public: 
	searchBox* box; 
	resPage* res;
	SearchPage(wxWindow *parent);
	void OnRandomBtnClicked(wxCommandEvent&);

private:
	TST list = loadWord("data/ev/data.txt");
	void OnFindBoxEnter(wxCommandEvent& evt);
	void OnSearchBtnClicked(wxCommandEvent&); 
};