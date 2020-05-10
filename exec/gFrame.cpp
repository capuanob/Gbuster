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
    Byte bytes[] = {Byte("FF"), Byte("AB"), Byte("44"), Byte("56")};
    Word w(bytes, 4);
}


GFrame::GFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{

    auto *menuFile = new wxMenu;
    menuFile->Append(ID_Load, "&Load from file...\tCtrl-L, ",
            "Load a password hash dump from a file.");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    auto *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    auto *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, "&File" );
    menuBar->Append( menuHelp, "&Help" );

    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText( "Welcome to Gbuster!" );

}

void GFrame::loadMainUI() {

}
