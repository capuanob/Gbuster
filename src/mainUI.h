//
// Created by bailey on 5/8/20.
//

#ifndef GBUSTER_MAINUI_H
#define GBUSTER_MAINUI_H

#include "ui/gFrame.h"
#include "wx/display.h" // Screen size and monitor handling

class UI: public wxApp {
private:
    wxFrame* frame;
    static const wxSize APPLICATION_SIZE; // Size of application window on start-up.
    static wxPoint getCenterOfDisplay(); // Finds the center position of the available screen-space, regardless of monitor count
public:
    bool OnInit() override; // Called upon startup, used to initialize program
    int OnExit() override;
};

#endif //GBUSTER_MAINUI_H
