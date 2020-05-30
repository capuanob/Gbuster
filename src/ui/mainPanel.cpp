//
// Created by bailey on 5/18/20.
//

#include "mainPanel.h"

MainPanel::MainPanel(wxWindow *parent, HashModel& model, Session& s) : wxPanel(parent), SESSION(s) {
    std::move(model);
    this->model = model;

    temperatureTimer.SetOwner(this, ID_TEMP_TIMER);
    temperatureTimer.Start(2000);
    SetUp();
}

void MainPanel::SetUp() {
    /// Set up temperature label
    auto* labelSizer = new wxBoxSizer(wxHORIZONTAL);
    auto* leadingLabel = new wxStaticText(this, wxID_ANY, "Thermal Zones (C): ");
    labelSizer->Add(leadingLabel);

    int labelCount = SESSION.temperatureFilePaths.size();
    tempLabels.reserve(labelCount); // Create as many labels as there are thermal zones
    for (int i = 0; i < labelCount; ++i) {
        tempLabels.push_back(new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(20, -1)));
        labelSizer->Add(tempLabels.back(), 0, wxALIGN_RIGHT);
    }
    topSizer->AddSpacer(10);
    topSizer->Add(labelSizer, 0, wxALIGN_LEFT);

    /// Setup label
    wxString lbl{std::to_string(model.size()) + " hashes successfully loaded"};
    countLabel = new wxStaticText(this, wxID_ANY, lbl, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER | wxST_NO_AUTORESIZE);
    countLabel->SetFont(labelFont);

    topSizer->Add(countLabel, 0, wxALIGN_CENTER_HORIZONTAL);


    auto* horizSizer = new wxBoxSizer(wxHORIZONTAL);

    /// Setup config box
    auto* configSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Configure");

    // Set up hash type
    wxString hashOptions[] = { "MD5" };
    int contentSize = sizeof(hashOptions) / sizeof(hashOptions[0]);
    hashBox = new wxLabelledComboBox(this, 75,
                                         hashOptions, contentSize, "Hash type: ");
    configSizer->Add(hashBox, 0, wxEXPAND | wxALL, 10);

    // Set up device type
    wxString deviceOptions[] = { "CPU", "CUDA-Compatible Nvidia GPU" };
    contentSize = sizeof(deviceOptions) / sizeof(deviceOptions[0]);
    deviceBox = new wxLabelledComboBox(this, 150,
            deviceOptions, contentSize, "Use device: ");
    configSizer->Add(deviceBox, 0, wxEXPAND | wxALL, 10);

    auto* workloadSizer = new wxBoxSizer(wxHORIZONTAL);
    auto workloadVec = MainPanel::getCPUWorkloadOptions();

    wxString temperatures[] = { "90", "85", "80", "75", "70" };
    int temperaturesSize = sizeof(temperatures) / sizeof(temperatures[0]);

    workloadBox = new wxLabelledComboBox(this, 150, &workloadVec.front(),
            workloadVec.size(), "Workload profile: ");
    temperatureBox = new wxLabelledComboBox(this, 75, temperatures,
            temperaturesSize, "Abort (C): ");

    workloadSizer->Add(workloadBox, 0, wxEXPAND);
    workloadSizer->AddSpacer(10);
    workloadSizer->Add(temperatureBox, 0, wxEXPAND);
    configSizer->Add(workloadSizer, 0, wxEXPAND | wxALL, 10);

    horizSizer->Add(configSizer, 0);

    /// Set up character set
    auto* charSetContainer = new wxStaticBox(this, wxID_ANY, "Character Set");

    auto* charSizer = new wxGridSizer(3, 2, 0, 0);

    capitalLetters = new wxCheckBox(charSetContainer, wxID_ANY, "A-Z");
    lowercaseLetters = new wxCheckBox(charSetContainer, wxID_ANY, "a-z");
    lowercaseLetters->SetValue(true); // Default selection
    numeric = new wxCheckBox(charSetContainer, wxID_ANY, "0-9");
    symbols = new wxCheckBox(charSetContainer, wxID_ANY, R"("!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~")");

    charSizer->Add(capitalLetters, 0);
    charSizer->Add(numeric, 0);
    charSizer->Add(lowercaseLetters, 0);
    charSizer->Add(symbols, 0);
    charSizer->AddStretchSpacer();

    auto *charSetContainerSizer = new wxBoxSizer(wxVERTICAL);
    charSetContainerSizer->Add(charSizer, 0);

    // Set up password length
    passwordLengthCtrl = new wxLabelledTxtCtrl(charSetContainer, 50, wxFILTER_NUMERIC, "Password length: ");

    charSetContainerSizer->Add(passwordLengthCtrl, 0);
    charSetContainer->SetSizer(charSetContainerSizer);
    horizSizer->Add(charSetContainer, 0, wxEXPAND | wxLEFT, 10);

    topSizer->AddSpacer(20);
    topSizer->Add(horizSizer, 0,wxLEFT, 20);

    /// Set up button
    crackButton = new wxButton(this, ID_CRACK, "CRACK", wxDefaultPosition, wxSize(200, 50));
    crackButton->SetFont(btnFont);
    topSizer->AddSpacer(5);
    topSizer->Add(crackButton, 0, wxALIGN_RIGHT | wxRIGHT, 20);

    SetSizerAndFit(topSizer);
    Layout();
}

auto MainPanel::getCPUWorkloadOptions() -> std::vector<wxString> {
    std::vector<unsigned int> values = getThreadCounts();
    std::vector<wxString> options;

    std::vector<wxString> text = { "Unresponsive", "Heavy", "Moderate", "Light" };
    for (unsigned long int i = 0; i < values.size(); ++i) {
        options.emplace_back(text[i] + " (" + std::to_string(values[i]) + ")");
    }

    return options;
}

BEGIN_EVENT_TABLE(MainPanel, wxPanel)
                EVT_BUTTON(ID_CRACK, MainPanel::OnCrackBtnPressed)
                EVT_TIMER(ID_PROG_TIMER, MainPanel::OnPollThreads)
                EVT_TIMER(ID_TEMP_TIMER, MainPanel::OnPollCoreTemps)
                EVT_COMMAND(THREAD_DELETE_ID, wxEVT_THREAD, MainPanel::OnThreadDeletion)
END_EVENT_TABLE()

void MainPanel::OnCrackBtnPressed(wxCommandEvent& WXUNUSED(event)) {
    Reset();
    toggleWorking();

    UniqueCreate(progressPanel, this);

    topSizer->Add(progressPanel, 0, wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALL, 15);
    topSizer->AddStretchSpacer();
    Fit();

    // Set up character set using radio boxes
    CharacterSet::buildCharacterSet(lowercaseLetters->GetValue(), capitalLetters->GetValue(),
            numeric->GetValue(), symbols->GetValue());
    NumberSystem::setBase(CharacterSet::getBase());

    // Clean password maximum length (input)
    int maxLen = wxAtoi(passwordLengthCtrl->str());
    unsigned int threadCount = MainPanel::getThreadCounts()[workloadBox->getIndex()];
    if (maxLen < 1 || maxLen > Constants::MAX_PASSWORD_LEN) {
        wxString lengthError = "Password length must be between 0 and " + std::to_string(Constants::MAX_PASSWORD_LEN);
        wxLogError(lengthError);
        return;
    }

    // Set up session
    SESSION.maxCoreTemp = static_cast<double>(std::stoi(temperatureBox->getSelection()));
    SESSION.characterSets = {
            lowercaseLetters->GetValue(), capitalLetters->GetValue(),
            numeric->GetValue(), symbols->GetValue()
    };
    SESSION.chosenPasswordLen = maxLen;
    SESSION.threadCount = threadCount;
    SESSION.hashUsed = static_cast<HashType>(hashBox->getIndex());

    // Create scheduler
    scheduler = std::make_unique<Scheduler>(threadCount, static_cast<unsigned int>(maxLen), std::move(model.getHashes()), this); // Deletes old value and assigns to new pointer

    // Set up progress bar gauges
    progressPanel->SetGauges(scheduler->getDistribution());

    Fit();
    Layout();

    // Dispatch threads
    SESSION.start = high_resolution_clock::now();
    scheduler->dispatchWorkers();


    temperatureTimer.SetOwner(this, ID_TEMP_TIMER);
}

auto MainPanel::getThreadCounts() -> std::vector<unsigned int> {
    unsigned int maxThreads = CpuHardware::getMaximumThreads() - 1;
    auto heavyThreads = static_cast<unsigned int>(maxThreads * 0.75);
    auto mediumThreads = static_cast<unsigned int>(maxThreads * 0.5);
    auto lightThreads = static_cast<unsigned int>(maxThreads * 0.25);

    std::vector<unsigned int> values;

    values.push_back(maxThreads);
    if (maxThreads >= 4)
        values.push_back(heavyThreads);
    if (maxThreads >= 2)
        values.emplace_back(mediumThreads);
    if (maxThreads >= 4)
        values.emplace_back(lightThreads);

    return values;
}

void MainPanel::OnPollThreads(wxTimerEvent & WXUNUSED(event)) {
    if (shouldContinueExecution()) {
        const auto &threads = scheduler->getThreads();
        const unsigned int len = threads.size();
        for (unsigned int i = 0; i < len; ++i) {
            if (threads.at(i) != nullptr) {
                progressPanel->UpdateGauge(i, threads.at(i)->getCount());
            }
        }
    } else {
        SESSION.end = high_resolution_clock::now();
        duration<double, std::milli> ms = SESSION.end - SESSION.start;
        std::cout << "This operation took " + std::to_string(ms.count() / 1000) +  " seconds\n";
        for (const auto& pair : HashThread::getCracked()) {
            std::cout << pair.first + "-->" + pair.second << "\n";
        }
        toggleWorking();
        InvalidateBestSize();
        Layout();
    }
}

void MainPanel::OnThreadDeletion(wxCommandEvent &event) {
    int deletionIdx = event.GetInt();
    if (progressPanel != nullptr) progressPanel->FillProgressBar(deletionIdx); // Ensure UI had time to catch up, fill it to 100%
    if (scheduler != nullptr) scheduler->deleteThread(deletionIdx);
}

MainPanel::~MainPanel() {
    Reset();
}

void MainPanel::Reset() {
    // If timer exists, stop it.
    if (progressTimer.IsRunning()) progressTimer.Stop();
    if (progressPanel) progressPanel->Destroy();
    scheduler = nullptr;
}

void MainPanel::toggleWorking() {
    if (!progressTimer.IsRunning()) { // Starting...
        progressTimer.SetOwner(this, ID_PROG_TIMER);
        progressTimer.Start(500);
        crackButton->SetLabel("SAVE/QUIT");
    } else { // Stopping...
        crackButton->SetLabel("CRACK");
        Reset();
    }
    Layout();
}

void MainPanel::OnPollCoreTemps(wxTimerEvent & WXUNUSED(event)) {
    const auto& coreTemperatures = CpuHardware::getCoreTemperatures(SESSION.temperatureFilePaths);

    UpdateCoreTempUI(coreTemperatures);

    if (SESSION.maxCoreTemp == DEFAULT_TEMP) return;

    if (coreTemperatures.empty()) {
        wxMessageBox("Unable to locate CPU core temperatures for excess-heat termination", "Error", wxICON_ERROR);
        temperatureTimer.Stop(); // Won't be needing this
        return;
    }

    for (const auto& temp : coreTemperatures) {
        if (temp >= SESSION.maxCoreTemp) {
            temperatureTimer.Stop();
            wxMessageBox("You can still write out any resolved hashes.",
                    "WARNING: Core temperatures reached " + std::to_string(temp), wxICON_WARNING);
            return;
        }
    }
}

void MainPanel::UpdateCoreTempUI(const std::vector<double>& newTemperatures) {
    std::ostringstream ss;

    int len = newTemperatures.size();
    for (int i = 0; i < len; ++i) {
        wxColor c;
        const auto& temp = newTemperatures.at(i);
        if (SESSION.maxCoreTemp < temp || SESSION.maxCoreTemp - temp < 5) c = tempRed;
        else if (SESSION.maxCoreTemp - temp < 10) c = tempOrange;
        else c = tempGreen;

        ss << std::setprecision(2) << temp;
        tempLabels.at(i)->SetLabel(ss.str());
        tempLabels.at(i)->SetForegroundColour(c);
        ss.str("");
    }


}
