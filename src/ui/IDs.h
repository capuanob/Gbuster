//
// Created by bailey on 5/10/20.
//

#ifndef GBUSTER_IDS_H
#define GBUSTER_IDS_H

#endif //GBUSTER_IDS_H

#include <wx/wx.h> // Needed for wxID_HIGHEST

enum IDs {
    ID_LOAD = wxID_HIGHEST + 1, // gFrame load hash list menu option
    ID_TEST_MD5, // gFrame debug menu option
    ID_SAVE, // gFrame save resolved hashes to file
    ID_TEST_HASH, // HashTestPanel button
    ID_HASH_TEXT_BOX, // HashTestPanel text box
    ID_CRACK, // mainPanel crack button
    ID_PROG_TIMER, // mainPanel timer for progress bar
    ID_TEMP_TIMER // mainPanel timer for polling CPU temperatures
};