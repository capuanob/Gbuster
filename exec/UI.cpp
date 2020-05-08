//
// Created by bailey on 5/8/20.
//

#include "UI.h"

bool UI::OnInit() {
    frame = new GFrame("Gbuster", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

int UI::OnExit() {
    delete frame;
    return 0;
}

// Instantiates the event table
wxBEGIN_EVENT_TABLE(GFrame, wxFrame)
                EVT_MENU(ID_Load, GFrame::OnLoad)
                EVT_MENU(wxID_EXIT, GFrame::OnExit)
                EVT_MENU(wxID_ABOUT, GFrame::OnAbout)
wxEND_EVENT_TABLE()

// Instantiate the application (main)
wxIMPLEMENT_APP(UI);