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
    /// Phil
    auto* philLbl = new wxStaticText(this, wxID_ANY, "Test");
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
    hashBox = new LabelledComboBox(this, wxID_ANY, 75,
                                         hashOptions, contentSize, "Hash type: ");
    configSizer->Add(hashBox, 0, wxEXPAND | wxALL, 10);

    // Set up device type

    wxString deviceOptions[] = { "i9 9900k (CPU) "};
    contentSize = sizeof(deviceOptions) / sizeof(deviceOptions[0]);
    deviceBox = new LabelledComboBox(this, wxID_ANY, 150,
            deviceOptions, contentSize, "Use device: ");
    configSizer->Add(deviceBox, 0, wxEXPAND | wxALL, 10);

    auto* workloadSizer = new wxBoxSizer(wxHORIZONTAL);
    auto workloadVec = LabelledComboBox::getWorkloadOptions();
    wxString workloadOptions[workloadVec.size()];
    std::copy(workloadVec.begin(), workloadVec.end(), workloadOptions);

    wxString temperatures[] = { "90", "85", "80", "75", "70" };
    int temperaturesSize = sizeof(temperatures) / sizeof(temperatures[0]);

    workloadBox = new LabelledComboBox(this, wxID_ANY, 150, workloadOptions,
            workloadVec.size(), "Workload profile: ");
    temperatureBox = new LabelledComboBox(this, wxID_ANY, 75, temperatures,
            temperaturesSize, "Abort (C): ");


    workloadSizer->Add(workloadBox, 0, wxEXPAND);
    workloadSizer->AddSpacer(10);
    workloadSizer->Add(temperatureBox, 0, wxEXPAND);
    configSizer->Add(workloadSizer, 0, wxEXPAND | wxALL, 10);
    configSizer->Add(philLbl, 0, wxEXPAND | wxALL, 10);

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

    charSetContainer->SetSizerAndFit(charSizer);
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

LabelledComboBox::LabelledComboBox(wxWindow *parent, wxWindowID ID, int width, const wxString *contents, int contentCount,
        const wxString& lbl)
: wxPanel(parent)
{
    szr = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(szr);

    this->lbl = new wxStaticText(this, ID, lbl);
    szr->Add(this->lbl, 0, wxEXPAND);

    wxSize customSize{width, wxDefaultSize.y};
    this->box = new wxComboBox(this, ID, *contents, wxDefaultPosition, customSize,
            contentCount, contents, wxCB_DROPDOWN);
    szr->Add(this->box, 0, wxEXPAND);
}

std::vector<wxString> LabelledComboBox::getWorkloadOptions() {
    //FIXME: This will look ugly when getMaximumThreads returns 0 or < 4
    unsigned int maxThreads = CpuHardware::getMaximumThreads() - 1;
    auto heavyThreads = static_cast<unsigned int>(maxThreads * 0.75);
    auto mediumThreads = static_cast<unsigned int>(maxThreads * 0.5);
    auto lightThreads = static_cast<unsigned int>(maxThreads * 0.25);

    std::vector<wxString> options;
    options.emplace_back("Unresponsive (" + std::to_string(maxThreads) + ") ");
    options.emplace_back("Heavy (" + std::to_string(heavyThreads) + ") ");
    options.emplace_back("Moderate (" + std::to_string(mediumThreads) + ") ");
    options.emplace_back("Light (" + std::to_string(lightThreads) + ") ");

    return options;
}

BEGIN_EVENT_TABLE(MainPanel, wxPanel)
                EVT_BUTTON(ID_CRACK, MainPanel::OnCrackBtnPressed)
END_EVENT_TABLE()

void MainPanel::OnCrackBtnPressed(wxCommandEvent& event) {
    CharacterSet cs(true, false, false, false); //TODO: Get these values from UI
    Scheduler sched(cs, 2, 3, model.getHashes());
    sched.dispatchWorkers();
}
