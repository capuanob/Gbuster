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
#include "constants.h"
#include "md5.h"
#endif // PANEL_INCLUDES

#include <functional> // Passing of hash function

using hashFuncSig = void(std::array<unsigned char, Constants::MAX_PASSWORD_LEN>&, std::array<unsigned char, 16>&, unsigned int);
class HashTestPanel: public wxPanel {
public:
    HashTestPanel(wxWindow* parent, const wxString& lbl, hashFuncSig fnc);

    void OnPress(wxCommandEvent& event);
    void OnTextDidChange(wxCommandEvent& event);

    auto getTextBoxValue() -> std::array<unsigned char, Constants::MAX_PASSWORD_LEN>;
private:
    wxTextCtrl* textBox;
    wxStaticText* charCount;
    wxStaticText* hashOutputLabel;
    wxButton* hashButton;
    std::function<hashFuncSig> hashFunc;

    DECLARE_EVENT_TABLE()
};


#endif //GBUSTER_HASHTESTPANEL_H
