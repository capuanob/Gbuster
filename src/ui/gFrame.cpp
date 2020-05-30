//
// Created by bailey on 5/8/20.
//

#include "gFrame.h"

void GFrame::OnAbout(wxCommandEvent & WXUNUSED(event)) {
    wxMessageBox("This software provides capabilities for rapid hash-cracking using the parallel power of a GPU.", "About Gbuster", wxOK | wxICON_INFORMATION);
}

void GFrame::OnExit(wxCommandEvent & WXUNUSED(event)) {
    Close(true);
}

void GFrame::OnLoad(wxCommandEvent & WXUNUSED(event)) {
    wxFileDialog openFileDialog(this, "Choose a hash list",
            "", "", "Text Files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() != wxID_OK) return;

    // Open file, save necessary information
    defaultDirectory = openFileDialog.GetDirectory().ToStdString();
    std::string fullFileName = openFileDialog.GetFilename().ToStdString();
    removeExtensionAndSave(fullFileName);

    wxTextFile hashList(openFileDialog.GetPath());
    if (!hashList.Open()) {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetFilename());
        return;
    }

    HashModel model;
    // Store hashes in program's model
    for (auto& str = hashList.GetFirstLine(); !hashList.Eof(); str = hashList.GetNextLine()) {
        model.addHash(std::string(str));
    }

    hashList.Close();
    loadMainUI(model);
}


GFrame::GFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    topSizer = new wxBoxSizer(wxVERTICAL);

    auto *menuFile = new wxMenu;
    menuFile->Append(ID_LOAD, "&Load from file...\tCtrl-L",
                     "Load a password hash dump from a file.");
    menuFile->Append(ID_SAVE, "&Save to file...\tCtrl-S", "Save resolved and unresolved hashes to a new file.");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    auto *menuDebug = new wxMenu;
    menuDebug->Append( ID_TEST_MD5, "&Test MD5\tCtrl-M", "Test MD5 hash");
    auto *menuBar = new wxMenuBar;

    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );
    menuBar->Append( menuDebug, "&Debug" );

    SetSizer(topSizer);
    SetMenuBar(menuBar);
    statusBar = CreateStatusBar(2);
    SetStatusText( "Welcome to Gbuster!" );

}

void GFrame::loadMainUI(HashModel& model) {
    Session s{}; // Get files here to avoid searching every time a crack is run
    CpuHardware::findTemperatureFilesAt(s.temperatureFilePaths); // Use default search path
    UniqueCreate(mainPanel, this, model, s);
    topSizer->Add(mainPanel, 0, wxEXPAND);

    Layout();
}

void GFrame::OnTestMD5(wxCommandEvent & WXUNUSED(event)) {
    UniqueCreate(debugFrame, this, "Admin Panel", wxDefaultPosition, wxSize(450, 600));
    debugFrame->Show();
}

void GFrame::OnSave(wxCommandEvent & WXUNUSED(event)) {
    // Get hash list and resolved hash list
    const wxString errorCaption = "Error Saving Hashing Results";

    if (loadedFileName.empty()) {
        // Nothing has been computed as of yet...
        wxMessageBox("Nothing to save.", errorCaption);
        return;
    }

    const auto& hashList = mainPanel->getHashList();
    const auto& resolved = mainPanel->getResolved();

    if (hashList.empty() || resolved.empty()) {
        // Something went wrong...
        wxMessageBox("Nothing to save.", errorCaption);
        return;
    }

    // Can safely save to file
    wxDirDialog dirChooser(this, "Choose save directory", defaultDirectory);

    if (dirChooser.ShowModal() != wxID_OK) return;
    std::string newFileName = loadedFileName + "_cracked.txt";
    std::string fullPath = dirChooser.GetPath().ToStdString() + "/" + newFileName;

    const auto& SESSION = mainPanel->getSessionData();
    std::ofstream out(fullPath, std::ofstream::out);

    // Write out meta-data
    const std::string divider = "==========\n";
    out << divider;

    out << "Hash type applied: ";
    switch(SESSION.hashUsed) {
        case HashType::MD5:
            out << "MD5\n";
            break;
        default:
            out << "Unknown\n";
    }

    out << "Threads used: " << SESSION.threadCount << "\n";
    out << "Search length: " << SESSION.chosenPasswordLen << " characters\n";
    out << "Prematurely terminated: " << (SESSION.terminatedEarly ? "True" : "False") << "\n";
    duration<double, std::milli> ms = SESSION.end - SESSION.start;
    out << "Time: " << std::to_string(ms.count() / 1000) << " seconds\n";

    out << "Character range: ";
    out << (SESSION.characterSets[0] ? "a-z" : "");
    out << (SESSION.characterSets[1] ? "A-Z" : "");
    out << (SESSION.characterSets[2] ? "0-9" : "");
    out << (SESSION.characterSets[3] ? "$" : "");
    out << "\n";

    out << divider;

    // Write out hashes
    for (const auto& hash : hashList) {
        std::string lineContents = hash;
        if (resolved.contains(hash)) {
            std::string clear = resolved.find(hash)->second;
            clear.erase(clear.find('\0'), std::string::npos); // Trim all null characters
            lineContents.append(" ---> " + clear);
        }
        out << lineContents << "\n";
    }
    out.close();

    wxMessageBox("File saved to " + fullPath, "Success!");
}

void GFrame::removeExtensionAndSave(std::string fullFileName) {
    // If fullFileName contains an extension, remove it and save it to loadedFileName
    auto dotIter = std::find(fullFileName.begin(), fullFileName.end(), '.');

    loadedFileName = (dotIter == fullFileName.end()) ? fullFileName : fullFileName.substr(0, dotIter - fullFileName.begin() - 1);
}