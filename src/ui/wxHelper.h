//
// Created by bailey on 5/27/20.
//

#ifndef GBUSTER_WXHELPER_H
#define GBUSTER_WXHELPER_H

#include <wx/window.h>
#include <wx/weakref.h>
/**
 * This file provides functions to remove commonly used design patterns and prevent bugs
 */

template <typename wxType, typename... TypeArgs>
void UniqueCreate(wxWeakRef<wxType>& wxPtr, TypeArgs... args) {
    static_assert(std::is_base_of_v<wxWindow, wxType>); // Ensure we are being passed a wxWindow descendant
    if (wxPtr != nullptr) {
        wxPtr->Destroy();
    }
    wxPtr = new wxType((args)...);
}


#endif //GBUSTER_WXHELPER_H
