//
// Created by bailey on 5/10/20.
//

#ifndef GBUSTER_DEBUGFRAME_H
#define GBUSTER_DEBUGFRAME_H

#include <wx/frame.h>
#include "hashTestPanel.h"

class DebugFrame: public wxFrame {
public:
    DebugFrame(wxWindow* parent, const wxString& title, const wxPoint& pos, const wxSize& size);
    ~DebugFrame() override = default;

private:
    hashTestPanel* md5Panel;
};

#endif //GBUSTER_DEBUGFRAME_H
