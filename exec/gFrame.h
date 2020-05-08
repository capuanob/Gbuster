//
// Created by bailey on 5/8/20.
//

#ifndef GBUSTER_GFRAME_H
#define GBUSTER_GFRAME_H

#include <memory>
#include <wx/wx.h>

// Unique identifiers for menu commands. As many must be defined, an enum element is used.
enum {
    ID_Load = 1
};

class GFrame: public wxFrame
{
public:
    GFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:

    // Event handlers //
    void OnLoad(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void loadMainUI();

    wxDECLARE_EVENT_TABLE();
};

#endif //GBUSTER_GFRAME_H
