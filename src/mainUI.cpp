//
// Created by bailey on 5/8/20.
//

#include "mainUI.h"

const wxSize UI::APPLICATION_SIZE = wxSize(1000, 500);

bool UI::OnInit() {
    auto centerPoint = getCenterOfDisplay();
    frame = new GFrame("Gbuster", centerPoint, APPLICATION_SIZE);
    frame->Show(true);

    SetTopWindow(frame);

    return true;
}

int UI::OnExit() {
    delete frame;
    return 0;
}

wxPoint UI::getCenterOfDisplay() {
    unsigned int monitorCount = wxDisplay::GetCount();

    // Store display information and sort by x offset
    std::vector<displayInfo> displays;
    displays.reserve(monitorCount);

    for (unsigned int i = 0; i < monitorCount; ++i)
            displays.emplace_back(i, wxDisplay(i).GetClientArea().x);
    std::sort(displays.begin(), displays.end(), [](const displayInfo& a, const displayInfo& b) {
        return a.second < b.second;
    });


    // Return center point
    unsigned int centerDisplayIdx = displays[displays.size() / 2].first;

    auto centerRect = static_cast<wxRect>(APPLICATION_SIZE).CenterIn(wxDisplay(centerDisplayIdx).GetClientArea());
    return wxPoint(centerRect.x, centerRect.y);
}

// Instantiates the event table
wxBEGIN_EVENT_TABLE(GFrame, wxFrame)
                EVT_MENU(ID_LOAD, GFrame::OnLoad)
                EVT_MENU(ID_SAVE, GFrame::OnSave)
                EVT_MENU(ID_TEST_MD5, GFrame::OnTestMD5)
                EVT_MENU(wxID_EXIT, GFrame::OnExit)
                EVT_MENU(wxID_ABOUT, GFrame::OnAbout)
wxEND_EVENT_TABLE()

// Instantiate the application (main)
wxIMPLEMENT_APP(UI);
