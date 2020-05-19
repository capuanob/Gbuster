//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_MAINPANEL_H
#define GBUSTER_MAINPANEL_H

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h> // Labels
#include <wx/font.h> // Styling
#include <wx/combobox.h> // Dropdown boxes
#include <wx/checkbox.h> // character set selection
#include <wx/statbox.h>
#include <wx/button.h>
#include <memory> // unique ptr
#include "hashModel.h"
#include "CpuHardware.h"

class LabelledComboBox : public wxPanel {
public:
    LabelledComboBox(wxWindow* parent, wxWindowID ID, int width, const wxString* contents, int contentCount,
                     const wxString& lbl = wxEmptyString);

    /**
     *
     * @return An array of workload options for the combo box to display
     */
    static std::vector<wxString> getWorkloadOptions();
private:
    wxBoxSizer* szr;
    wxStaticText* lbl;
    wxComboBox* box;

};

class MainPanel : public wxPanel {
public:
    explicit MainPanel(wxWindow* parent, HashModel&& model);
    ~MainPanel() override = default;

private:

    void SetUp(); // Sets up the controls

    HashModel model;
    wxFont labelFont{15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD};
    wxFont btnFont{20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL};
    // Combo boxes
    wxStaticText* countLabel;
    LabelledComboBox* hashBox;
    LabelledComboBox* deviceBox;
    LabelledComboBox* workloadBox;
    LabelledComboBox* temperatureBox;

    // Check boxes
    wxCheckBox* capitalLetters;
    wxCheckBox* lowercaseLetters;
    wxCheckBox* numeric;
    wxCheckBox* symbols;

    wxButton* crackButton;

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
};


#endif //GBUSTER_MAINPANEL_H