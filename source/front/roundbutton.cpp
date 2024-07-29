#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include "roundbutton.h" 

RoundButton::RoundButton(wxWindow* parent, wxWindowID id, const wxString& label, const wxColour& bgColour, const wxColour& textColour, const wxSize& size, int fontSize)
    : wxPanel(parent, id, wxDefaultPosition, size, wxTAB_TRAVERSAL | wxBORDER_NONE)
    , m_label(label), m_bgColour(bgColour), m_textColour(textColour), m_fontSize(fontSize)
{
    SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &RoundButton::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &RoundButton::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &RoundButton::OnLeftUp, this);
}


void RoundButton::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(wxBrush(GetBackgroundColour()));
    dc.Clear();

    wxSize size = GetSize();
    int width = size.GetWidth();
    int height = size.GetHeight();

    // Draw rounded rectangle
    dc.SetBrush(wxBrush(m_bgColour));
    dc.SetPen(wxPen(m_bgColour));
    dc.DrawRoundedRectangle(0, 0, width, height, 20);

    // Draw label
    wxFont font(m_fontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    dc.SetFont(font);
    dc.SetTextForeground(m_textColour);
    wxSize textSize = dc.GetTextExtent(m_label);
    int textX = (width - textSize.GetWidth()) / 2;
    int textY = (height - textSize.GetHeight()) / 2;
    dc.DrawText(m_label, textX, textY);
}

void RoundButton::OnLeftDown(wxMouseEvent& event)
{
    // Handle button press
    wxLogMessage("Button %s pressed", m_label);
    Refresh(); // Optionally refresh to give visual feedback
}

void RoundButton::OnLeftUp(wxMouseEvent& event)
{
    // Handle button release
    wxLogMessage("Button %s released", m_label);
    Refresh(); // Optionally refresh to give visual feedback
}
