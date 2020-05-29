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
#include "wxHelper.h"

#endif // PANEL_INCLUDES
#include "wxProgressPanel.h"
#include <wx/checkbox.h>
#include <wx/timer.h>
#include "CpuHardware.h" // Getting thread count

using namespace std::chrono;
class MainPanel : public wxPanel {
public:
    explicit MainPanel(wxWindow* parent, HashModel& model);
    ~MainPanel() override;
    // Event handling
    void OnCrackBtnPressed(wxCommandEvent& event); // Handles set-up and execution of a brute-force attack
    void OnPollThreads(wxTimerEvent& event); // Handles updating of progress bars to show thread progress
    void OnThreadDeletion(wxCommandEvent& event); // Handles deletion of threads via thread notification

    static auto getThreadCounts() -> std::vector<unsigned int>;
private:
    void SetUp(); // Sets up the controls
    void Reset(); // Prepare for next cracking
    void toggleWorking(); // Toggles button label between crack and save and quit
    static auto getCPUWorkloadOptions() -> std::vector<wxString>;

    HashModel model;
    std::unique_ptr<Scheduler> scheduler;
    bool isWorking{false}; // Track whether or not cracking is in progress

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
    wxTimer* progressTimer = nullptr;
    wxWeakRef<wxProgressPanel> progressPanel;
    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    time_point<high_resolution_clock> start;
    time_point<high_resolution_clock> end;
    wxDECLARE_EVENT_TABLE();
};


#endif //GBUSTER_MAINPANEL_H