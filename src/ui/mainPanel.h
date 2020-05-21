//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_MAINPANEL_H
#define GBUSTER_MAINPANEL_H

#ifndef PANEL_INCLUDES
#define PANEL_INCLUDES
#include <wx/panel.h> // Panel inheritance
#include <wx/sizer.h>
#include "IDs.h"
#include "hashModel.h" // Application's model
#include "scheduler.h"
#endif // PANEL_INCLUDES


#include <wx/combobox.h>
#include <wx/stattext.h> // labels
#include <wx/checkbox.h>
#include "CpuHardware.h" // Getting thread count
#include "../threading/cpu/scheduler.h" // Work allotment

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
    wxBoxSizer* szr = nullptr;
    wxStaticText* lbl = nullptr;
    wxComboBox* box = nullptr;
};

class MainPanel : public wxPanel {
public:
    explicit MainPanel(wxWindow* parent, HashModel&& model);
    ~MainPanel() override = default;

    // Event handling
    void OnCrackBtnPressed(wxCommandEvent& event); // Handles set-up and execution of a brute-force attack
private:

    void SetUp(); // Sets up the controls

    HashModel model;
    wxFont labelFont{15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD};
    wxFont btnFont{20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL};
    // Combo boxes
    wxStaticText* countLabel = nullptr;
    LabelledComboBox* hashBox = nullptr;
    LabelledComboBox* deviceBox = nullptr;
    LabelledComboBox* workloadBox = nullptr;
    LabelledComboBox* temperatureBox = nullptr;

    // Check boxes
    wxCheckBox* capitalLetters = nullptr;
    wxCheckBox* lowercaseLetters = nullptr;
    wxCheckBox* numeric = nullptr;
    wxCheckBox* symbols = nullptr;

    wxButton* crackButton = nullptr;

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxDECLARE_EVENT_TABLE();
};


#endif //GBUSTER_MAINPANEL_H