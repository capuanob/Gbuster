//
// Created by bailey on 5/8/20.
//

#include "gFrame.h"

void GFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is a wxWidgets' Hello World sample", "About Hello World", wxOK | wxICON_INFORMATION);
}

void GFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void GFrame::OnLoad(wxCommandEvent &event) {
    return;
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
    SetStatusText( "Welcome to wxWidgets!" );

}

void GFrame::loadMainUI() {
    auto *list = new wxListCtrl();
}
