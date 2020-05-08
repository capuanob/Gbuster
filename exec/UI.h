//
// Created by bailey on 5/8/20.
//

#ifndef GBUSTER_UI_H
#define GBUSTER_UI_H

#include "gFrame.h"

class UI: public wxApp {
private:
    wxFrame* frame;
public:
    bool OnInit() override; // Called upon startup, used to initialize program
    int OnExit() override;
};

#endif //GBUSTER_UI_H
