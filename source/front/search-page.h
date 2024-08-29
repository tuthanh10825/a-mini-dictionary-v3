#include "properties.h"
#include <wx/wx.h>
#include <wx/bmpcbox.h>
#include <wx/fontutil.h>
#include "Globals.h"
#include "edit-page.h"


class searchBox : public wxWindow
{
public: 
	wxFont pala;
	wxComboBox* wordOrDefi= new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr);
	wxComboBox* language = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, nullptr);
	wxComboBox* findBox = new wxComboBox(this, wxID_ANY);
	wxBitmapButton* searchButton; 
	wxBitmapButton* randomButton; 
	wxBitmapButton* resetButton; 
	wxBitmapButton* addButton; 
	searchBox(wxWindow*); 
	bool isDropdown = false; 
	void FlipColor(); 

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
	void OnFavouriteBtnClicked(wxCommandEvent&);
	resPage(wxWindow*); 
	void addingString(wxString); 
	void clearScreen(); 
	void FlipColor(); 

};

class SearchPage : public wxWindow
{
public: 
	searchBox* box; 
	resPage* res;
	EditWindow* editwin;
	SearchPage(wxWindow *parent);
	void OnRandomBtnClicked(wxCommandEvent&);
	void FlipColor();
	
private:
	TST* list; 
	suffixArr* defi; 
	std::string currLang = "ENG/ENG"; 
	std::string currType = "KEYWORD"; 

	
	void insertHistory(TST::TreeNode* ans);
	void OnFindBoxEnter(wxCommandEvent& evt);
	void OnSearchBtnClicked(wxCommandEvent&); 
	void OnChooseLanguage(wxCommandEvent& evt); 
	void OnRemoveBtnClicked(wxCommandEvent&);
	void OnEditBtnClicked(wxCommandEvent&);
	void OnEdit_WordBtnClicked(wxCommandEvent&);
	void OnResetBtnClicked(wxCommandEvent&);
};