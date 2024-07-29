#include <wx/wx.h>
#include <wx/dcbuffer.h>

class RoundButton : public wxPanel
{
public:
    RoundButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxColour& bgColour, const wxColour& textColour, const wxSize& size, int fontSize);

protected:
    void OnPaint(wxPaintEvent& event);

    void OnLeftDown(wxMouseEvent& event);

    void OnLeftUp(wxMouseEvent& event);

private:
    wxString m_label;
    wxColour m_bgColour;
    wxColour m_textColour;
    int m_fontSize;
};

