#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by bailey on 5/8/20.
//

#include "mainUI.h"

const wxSize UI::APPLICATION_SIZE = wxSize(600, 500);

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
    int maxX = INT_MIN, maxW = 0, minHeight = INT_MAX;

    // Sum all monitor's widths and find minimum height
    for (int i = 0; i < monitorCount; ++i) {
        wxRect displaySize = wxDisplay(i).GetClientArea();
        if (displaySize.x > maxX) {
            maxX = displaySize.x;
            maxW = displaySize.width;
        }

        if (displaySize.height < minHeight)
            minHeight = displaySize.height;
    }

    // Get display that contains the center point
    int totalWidth = maxX + maxW;
    wxPoint centerPnt(static_cast<int>(totalWidth / monitorCount), minHeight);
    int centerDisplayIdx = wxDisplay::GetFromPoint(centerPnt);

    // Return center point
    if (centerDisplayIdx != -1) {
        auto centerDisplay = wxDisplay(centerDisplayIdx);
        auto screenRect = centerDisplay.GetClientArea();
        auto centerRect = static_cast<wxRect>(APPLICATION_SIZE).CenterIn(screenRect);
        return wxPoint(centerRect.x, centerRect.y);
    } else
        return wxDefaultPosition;
}

// Instantiates the event table
wxBEGIN_EVENT_TABLE(GFrame, wxFrame)
                EVT_MENU(ID_Load, GFrame::OnLoad)
                EVT_MENU(ID_TEST_MD5, GFrame::OnTestMD5)
                EVT_MENU(wxID_EXIT, GFrame::OnExit)
                EVT_MENU(wxID_ABOUT, GFrame::OnAbout)
wxEND_EVENT_TABLE()

// Instantiate the application (main)
wxIMPLEMENT_APP(UI);

#pragma clang diagnostic pop