//
// Created by bailey on 5/22/20.
//

#ifndef GBUSTER_WXLABELLEDWINDOW_H
#define GBUSTER_WXLABELLEDWINDOW_H
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/wx.h>

class wxLabelledWindow : public wxPanel {
public:
    wxLabelledWindow(wxWindow *parent, const wxString &lbl);
    void addLabelledWindow(wxWindow* win);
private:
    wxBoxSizer* szr = nullptr;
    wxStaticText* lbl = nullptr;
    wxWindow* window = nullptr;
};


class wxLabelledComboBox : public wxLabelledWindow {
public:
    wxLabelledComboBox(wxWindow* parent, int width, const wxString* contents, int contentCount,
                       const wxString& lbl = wxEmptyString);
    [[nodiscard]] auto getIndex() const -> unsigned int { return box->GetSelection(); }
private:
    wxComboBox* box = nullptr;
};

class wxLabelledTxtCtrl : public wxLabelledWindow {
public:
    wxLabelledTxtCtrl(wxWindow* parent, int width, wxTextValidatorStyle style, const wxString& lbl = wxEmptyString);
    inline auto str() -> wxString { return textCtrl->GetValue(); }
private:
    wxString m_str;
    wxTextCtrl* textCtrl;
};
#endif //GBUSTER_WXLABELLEDWINDOW_H
