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
#include "session.h"
#include <wx/statusbr.h>

#endif // PANEL_INCLUDES
#include "wxProgressPanel.h"
#include <wx/checkbox.h>
#include <wx/timer.h>
#include "CpuHardware.h" // Getting thread count

class MainPanel : public wxPanel {
public:
    // Constructors and destructors
    explicit MainPanel(wxWindow* parent, HashModel& model, Session& s);
    ~MainPanel() override;

    // Event handling
    void OnCrackBtnPressed(wxCommandEvent& event); // Handles set-up and execution of a brute-force attack
    void OnPollThreads(wxTimerEvent& event); // Handles updating of progress bars to show thread progress
    void OnPollCoreTemps(wxTimerEvent& event); // Handles premature stopping of cracking to ensure maximum temperature threshold is not surpassed
    void OnThreadDeletion(wxCommandEvent& event); // Handles deletion of threads via thread notification

    static auto getThreadCounts() -> std::vector<unsigned int>;

    // Public member functions
    inline auto getResolved() -> const std::unordered_map<std::string, std::string>& { return HashThread::getCracked(); }
    inline auto getHashList() -> const std::unordered_set<std::string> { return HashThread::getHashList(); }
    inline auto getSessionData() -> const Session& { return SESSION; }

private:
    void SetUp(); // Sets up the controls
    void UpdateCoreTempUI(const std::vector<double>& newTemperatures);
    void Reset(); // Prepare for next cracking
    void toggleWorking(); // Toggles button label between crack and save and quit
    static auto getCPUWorkloadOptions() -> std::vector<wxString>;
    inline bool shouldContinueExecution() { return temperatureTimer.IsRunning() && !scheduler->completed(); }

    HashModel model;
    std::unique_ptr<Scheduler> scheduler;
    Session SESSION;

    // UI Design Constants
    wxFont labelFont{15, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD};
    wxFont btnFont{20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL};
    wxColor tempRed{224u, 53u, 49u};
    wxColor tempOrange{240u, 189u, 39u};
    wxColor tempGreen{81u, 179u, 100u};

    // Labels
    std::vector<wxStaticText*> tempLabels;

    // Combo boxes
    wxStaticText* countLabel{};
    wxLabelledComboBox* hashBox{};
    wxLabelledComboBox* deviceBox{};
    wxLabelledComboBox* workloadBox{};
    wxLabelledComboBox* temperatureBox{};
    wxLabelledTxtCtrl* passwordLengthCtrl{};

    // Check boxes
    wxCheckBox* capitalLetters{};
    wxCheckBox* lowercaseLetters{};
    wxCheckBox* numeric{};
    wxCheckBox* symbols{};
    wxButton* crackButton{};
    wxTimer progressTimer{};
    wxTimer temperatureTimer{};
    wxWeakRef<wxProgressPanel> progressPanel{};

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxDECLARE_EVENT_TABLE();
};


#endif //GBUSTER_MAINPANEL_H