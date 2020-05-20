//
// Created by bailey on 5/10/20.
//

#ifndef GBUSTER_HASHTESTPANEL_H
#define GBUSTER_HASHTESTPANEL_H

#ifndef PANEL_INCLUDES
#define PANEL_INCLUDES
#include <wx/panel.h> // Panel inheritance
#include <wx/sizer.h>
#include "IDs.h"
#endif // PANEL_INCLUDES

#include <functional> // Passing of hash function


class hashTestPanel: public wxPanel {
public:
    hashTestPanel(wxWindow* parent, const wxString& lbl, std::function<std::string(std::string)> fnc);
    ~hashTestPanel() override = default;

    void OnPress(wxCommandEvent& event);
    void OnTextDidChange(wxCommandEvent& event);

    std::string getTextBoxValue();
private:
    wxTextCtrl* textBox;
    wxStaticText* charCount;
    wxStaticText* hashOutputLabel;
    wxButton* hashButton;
    std::function<std::string(std::string)> hashFunc;

    DECLARE_EVENT_TABLE();
};


#endif //GBUSTER_HASHTESTPANEL_H
