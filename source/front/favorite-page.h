
#include <wx/wx.h>
#include "properties.h" 
#include <string>
using namespace std;
#include <wx/bmpbuttn.h>
#include "wx/listctrl.h"
#include <wx/editlbox.h>


class FavWindow : public wxFrame
{
public:
    FavWindow(const wxString& title);
private:
    void LoadImage(const wxString& imagePath, const wxPoint& position, wxPanel* panel);
    wxListCtrl* m_item_list;
    void loadFavListUnFinish();
    void deleteSelectedRows();
    void SelectAllRows();
    void onDelClick(wxCommandEvent&);
    void onSelClick(wxCommandEvent&);

    wxDECLARE_EVENT_TABLE();
};
