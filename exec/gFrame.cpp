//
// Created by bailey on 5/8/20.
//

#include "gFrame.h"

void GFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This software provides capabilities for rapid hash-breaking using the parallel power of a GPU.", "About Gbuster", wxOK | wxICON_INFORMATION);
}

void GFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void GFrame::OnLoad(wxCommandEvent &event) {
    md5::getDigest("5r09r030450t0gd00sqallf0v0s0a0505slxlDKFKFLSL%#)@)!)!)@8");
}


GFrame::GFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{

    auto *menuFile = new wxMenu;
    menuFile->Append(ID_Load, "&Load from file...\tCtrl-L",
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

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText( "Welcome to Gbuster!" );

}

void GFrame::loadMainUI() {

}

void GFrame::OnTestMD5(wxCommandEvent &event) {
    auto *debugFrame = new DebugFrame(this, "Admin Panel",
            wxPoint(50, 50), wxSize(450, 600));
    debugFrame->Show(true);
}