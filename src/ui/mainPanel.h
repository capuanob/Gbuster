//
// Created by bailey on 5/18/20.
//

#ifndef GBUSTER_MAINPANEL_H
#define GBUSTER_MAINPANEL_H

#ifndef PANEL_INCLUDES
#define PANEL_INCLUDES
#include "wxLabelledWindow.h"
#include "IDs.h"
#include "hashModel.h" // Application's model
#include "scheduler.h"
#include <memory>
#endif // PANEL_INCLUDES

#include <wx/checkbox.h>
#include "CpuHardware.h" // Getting thread count
#include "../threading/cpu/scheduler.h" // Work allotment

class MainPanel : public wxPanel {
public:
    explicit MainPanel(wxWindow* parent, HashModel&& model);
    ~MainPanel() override = default;

    // Event handling
    void OnCrackBtnPressed(wxCommandEvent& event); // Handles set-up and execution of a brute-force attack
    static auto getThreadCounts() -> std::vector<unsigned int>;
private:
    void SetUp(); // Sets up the controls

    static auto getCPUWorkloadOptions() -> std::vector<wxString>;

    HashModel model;
    std::unique_ptr<Scheduler> scheduler;
    wxFont labelFont{15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD};
    wxFont btnFont{20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL};

    // Combo boxes
    wxStaticText* countLabel = nullptr;
    wxLabelledComboBox* hashBox = nullptr;
    wxLabelledComboBox* deviceBox = nullptr;
    wxLabelledComboBox* workloadBox = nullptr;
    wxLabelledComboBox* temperatureBox = nullptr;
    wxLabelledTxtCtrl* passwordLengthCtrl = nullptr;

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