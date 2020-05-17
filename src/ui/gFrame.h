//
// Created by bailey on 5/8/20.
//

#ifndef GBUSTER_GFRAME_H
#define GBUSTER_GFRAME_H

#include <wx/wx.h>
#include "debugFrame.h"
#include "md5.h"

class GFrame: public wxFrame
{
public:
    GFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~GFrame() override = default;
private:
    // Event handlers //
    void OnLoad(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnTestMD5(wxCommandEvent& event);

    void loadMainUI();

    wxDECLARE_EVENT_TABLE();
};

#endif //GBUSTER_GFRAME_H
