//
// Created by bailey on 5/10/20.
//

#include "debugFrame.h"

DebugFrame::DebugFrame(wxWindow* parent, const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame(parent, wxID_ANY, title, pos, size)
{
    topSizer = new wxBoxSizer(wxVERTICAL);
    md5Panel = new hashTestPanel(this, "MD5", md5::getDigest);

    topSizer->Add(md5Panel);

    SetSizer(topSizer);
}
