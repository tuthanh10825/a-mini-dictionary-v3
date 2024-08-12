
#include <wx/wx.h>
#include "properties.h" 
#include <string>
using namespace std;
#include <wx/bmpbuttn.h>
#include "wx/listctrl.h"
#include <wx/editlbox.h>


class ListWindow : public wxWindow
{
public:
    ListWindow(wxWindow* parent);
    void loadFavListUnFinish();
private:
    
    wxListCtrl* m_item_list;
  
    void deleteSelectedRows();
    void SelectAllRows();
    void onDelClick(wxCommandEvent&);
    void onSelClick(wxCommandEvent&);

    
};
