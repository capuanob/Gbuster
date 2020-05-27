//
// Created by bailey on 5/18/20.
//

#include "mainPanel.h"

MainPanel::MainPanel(wxWindow *parent, HashModel&& model) : wxPanel(parent) {
    this->model = model;
    countLabel = new wxStaticText();

    SetUp();
}

void MainPanel::SetUp() {

    /// Setup label
    wxString lbl{std::to_string(model.size()) + " hashes successfully loaded"};
    countLabel = new wxStaticText(this, wxID_ANY, lbl);
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
    wxString workloadOptions[workloadVec.size()];
    std::copy(workloadVec.begin(), workloadVec.end(), workloadOptions);

    wxString temperatures[] = { "90", "85", "80", "75", "70" };
    int temperaturesSize = sizeof(temperatures) / sizeof(temperatures[0]);

    workloadBox = new wxLabelledComboBox(this, 150, workloadOptions,
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
    for (int i = 0; i < values.size(); ++i) {
        options.emplace_back(text[i] + " (" + std::to_string(values[i]) + ")");
    }

    return options;
}

BEGIN_EVENT_TABLE(MainPanel, wxPanel)
                EVT_BUTTON(ID_CRACK, MainPanel::OnCrackBtnPressed)
END_EVENT_TABLE()

void MainPanel::OnCrackBtnPressed(wxCommandEvent& event) {

    // Set up character set using radio boxes
    CharacterSet::buildCharacterSet(lowercaseLetters->GetValue(), capitalLetters->GetValue(),
            numeric->GetValue(), symbols->GetValue());
    NumberSystem::setBase(CharacterSet::getChars().size());

    // Clean password maximum length (input)
    int maxLen = wxAtoi(passwordLengthCtrl->str());
    unsigned int threadCount = MainPanel::getThreadCounts()[workloadBox->getIndex()];
    if (maxLen < 1 || maxLen > Constants::MAX_PASSWORD_LEN) {
        wxString lengthError = "Password length must be between 0 and " + std::to_string(Constants::MAX_PASSWORD_LEN);
        wxLogError(lengthError);
        return;
    }

    // Create scheduler and dispatch threads
    scheduler = std::make_unique<Scheduler>(threadCount, static_cast<unsigned int>(maxLen), std::move(model.getHashes())); // Deletes old value and assigns to new pointer
    scheduler->dispatchWorkers();
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
