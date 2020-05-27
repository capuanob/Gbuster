////
//// Created by bailey on 5/10/20.
////
//
//#ifndef GBUSTER_HASHTESTPANEL_H
//#define GBUSTER_HASHTESTPANEL_H
//
//#ifndef PANEL_INCLUDES
//#define PANEL_INCLUDES
//#include <wx/panel.h> // Panel inheritance
//#include <wx/sizer.h>
//#include "IDs.h"
//#endif // PANEL_INCLUDES
//
//#include <functional> // Passing of hash function
//
//
//class hashTestPanel: public wxPanel {
//public:
//    hashTestPanel(wxWindow* parent, const wxString& lbl, const std::function<void(std::array<unsigned char, max_len> input, std::array<unsigned char, WORDS_IN_BLOCK> digest, unsigned int inputLen = max_len)>& fnc);
//    ~hashTestPanel() override = default;
//
//    void OnPress(wxCommandEvent& event);
//    void OnTextDidChange(wxCommandEvent& event);
//
//    std::string getTextBoxValue();
//private:
//    wxTextCtrl* textBox;
//    wxStaticText* charCount;
//    wxStaticText* hashOutputLabel;
//    wxButton* hashButton;
//    std::function<void(const std::string&, std::string&)> hashFunc;
//
//    DECLARE_EVENT_TABLE();
//};
//
//
//#endif //GBUSTER_HASHTESTPANEL_H
