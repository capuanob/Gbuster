//
// Created by bailey on 5/22/20.
//

#include "wxLabelledWindow.h"

wxLabelledWindow::wxLabelledWindow(wxWindow *parent, const wxString &lbl) : wxPanel(parent)
{
    szr = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(szr);

    this->lbl = new wxStaticText(this, wxID_ANY, lbl);
    szr->Add(this->lbl, 0, wxEXPAND);
}

void wxLabelledWindow::addLabelledWindow(wxWindow *win) {
    this->window = win;
    szr->Add(window, 0, wxEXPAND);
}


wxLabelledComboBox::wxLabelledComboBox(wxWindow *parent,
                                        int width,
                                        const wxString *contents,
                                        int contentCount,
                                        const wxString& lbl)
        : wxLabelledWindow(parent, lbl)
{
    wxSize customSize{width, wxDefaultSize.y};
    box = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, customSize, contentCount, contents, wxCB_DROPDOWN);
    box->SetSelection(0);
    addLabelledWindow(box);
}

wxLabelledTxtCtrl::wxLabelledTxtCtrl(wxWindow *parent, int width, wxTextValidatorStyle style, const wxString& lbl)
: wxLabelledWindow(parent, lbl)
{
    wxSize customSize{width, wxDefaultSize.y};
    textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, customSize, 0, wxTextValidator(style, &m_str));
    addLabelledWindow(textCtrl);
}
