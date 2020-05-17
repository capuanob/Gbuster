//
// Created by bailey on 5/8/20.
//

#ifndef GBUSTER_MAINUI_H
#define GBUSTER_MAINUI_H

#include "ui/gFrame.h"

class UI: public wxApp {
private:
    wxFrame* frame;
public:
    bool OnInit() override; // Called upon startup, used to initialize program
    int OnExit() override;
};

#endif //GBUSTER_MAINUI_H
