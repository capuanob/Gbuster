//
// Created by bailey on 5/10/20.
//

#ifndef GBUSTER_DEBUGFRAME_H
#define GBUSTER_DEBUGFRAME_H

#include <wx/frame.h> // Frame inheritance
#include "hashTestPanel.h"
#include "md5.h"

class DebugFrame: public wxFrame {
public:
    DebugFrame(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size);


private:
    wxBoxSizer* topSizer; // Used for laying out the frame
     HashTestPanel* md5Panel; // Panel for testing md5
};

#endif //GBUSTER_DEBUGFRAME_H
