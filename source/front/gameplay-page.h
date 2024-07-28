#include <wx/wx.h>
#include <vector>
#include<wx/stc/stc.h>
class DefiGameWindow : public wxWindow
{
public:
	DefiGameWindow(wxWindow*, wxString, std::vector<wxString>); 
	std::vector<wxString> answer; 
	std::vector<wxRadioButton*> choiceButton; 
	
	int correctAns = 0; 
	

};