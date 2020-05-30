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

// Ensure a generic class is derived from wxWindow
template <class T>
concept wxDerivable = std::is_base_of<wxWindow, T>::value;

template <typename T, typename... TypeArgs> requires wxDerivable<T>
void UniqueCreate(wxWeakRef<T>& wxPtr, TypeArgs... args) {
    if (wxPtr != nullptr) {
        wxPtr->Destroy();
    }
    wxPtr = new T((args)...);
}


#endif //GBUSTER_WXHELPER_H
