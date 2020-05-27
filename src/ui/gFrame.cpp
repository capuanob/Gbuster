//
// Created by bailey on 5/8/20.
//

#include "gFrame.h"

void GFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This software provides capabilities for rapid hash-cracking using the parallel power of a GPU.", "About Gbuster", wxOK | wxICON_INFORMATION);
}

void GFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void GFrame::OnLoad(wxCommandEvent &event) {
    wxFileDialog openFileDialog(this, "Choose a hash list",
            "", "", "Text Files (*.txt)|*.txt", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() != wxID_OK) return;

    // Open file
    wxTextFile hashList(openFileDialog.GetPath());
    if (!hashList.Open()) {
        wxLogError("Cannot open file '%s'.", openFileDialog.GetFilename());
        return;
    }

    HashModel model;
    // Store hashes in program's model
    for (auto& str = hashList.GetFirstLine(); !hashList.Eof(); str = hashList.GetNextLine())
        model.addHash(std::string(str));

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
    CreateStatusBar();
    SetStatusText( "Welcome to Gbuster!" );

}

void GFrame::loadMainUI(HashModel& model) {
    auto* mainPanel = new MainPanel(this, std::move(model));
    topSizer->Add(mainPanel, 0, wxEXPAND);

    Layout();
}

void GFrame::OnTestMD5(wxCommandEvent &event) {
//    auto *debugFrame = new DebugFrame(this, "Admin Panel",
//            wxDefaultPosition, wxSize(450, 600));
//    debugFrame->Show(true);
}