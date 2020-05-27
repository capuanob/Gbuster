//
// Created by bailey on 5/10/20.
//

#include "hashTestPanel.h"

void HashTestPanel::OnPress(wxCommandEvent& event) {
    auto cleartext = getTextBoxValue();
    std::array<unsigned char, 16> digest{};
    int length = textBox->GetLineLength(0);
    hashFunc(cleartext, digest, length);
    auto str = md5::digestStr(digest);
    hashOutputLabel->SetLabel("Message Digest: " + str);
}

auto HashTestPanel::getTextBoxValue() -> std::array<unsigned char, Constants::MAX_PASSWORD_LEN> {
    auto cppStr = std::string(textBox->GetValue());
    const char* cStr = cppStr.c_str();
    std::array<unsigned char, Constants::MAX_PASSWORD_LEN> text_arr{};
    int len = textBox->GetLineLength(0);

    for (int i = 0; i < len && i < Constants::MAX_PASSWORD_LEN; ++i) {
        text_arr.at(i) = static_cast<unsigned char>(cStr[i]);
    }

    return text_arr;
}

BEGIN_EVENT_TABLE(HashTestPanel, wxPanel)
    EVT_BUTTON(ID_TEST_HASH, HashTestPanel::OnPress)
    EVT_TEXT(ID_HASH_TEXT_BOX, HashTestPanel::OnTextDidChange)
END_EVENT_TABLE()

void HashTestPanel::OnTextDidChange(wxCommandEvent &event) {
    wxString curr_str = event.GetString();

    if (charCount != nullptr) // Creation of textBox emits an EVT_TEXT, have to avoid that
        charCount->SetLabel(std::to_string(curr_str.length()) + " c");
}

HashTestPanel::HashTestPanel(wxWindow *parent, const wxString &lbl, hashFuncSig fnc)
: wxPanel(parent)
{
    this->hashFunc = fnc;

    charCount = new wxStaticText(this, -1, "c", wxDefaultPosition, wxDefaultSize);
    textBox = new wxTextCtrl(this, ID_HASH_TEXT_BOX, wxT("Text to hash:"),
                             wxDefaultPosition, wxSize(450, 40));
    hashOutputLabel = new wxStaticText(this, -1,
                                       "Message Digest: ", wxDefaultPosition, wxSize(450, 100));
    hashButton = new wxButton(this, ID_TEST_HASH, lbl, wxDefaultPosition, wxDefaultSize);

    auto *boxSizer = new wxBoxSizer(wxVERTICAL);
    auto *counterSizer = new wxBoxSizer(wxHORIZONTAL);

    boxSizer->Add(textBox);
    counterSizer->Add(charCount, 1);
    boxSizer->Add(counterSizer, 0, wxALIGN_RIGHT | wxRIGHT, 15);
    boxSizer->AddSpacer(5);
    boxSizer->Add(hashButton);
    boxSizer->AddSpacer(10);
    boxSizer->Add(hashOutputLabel, 1, wxALL, 10);

    SetSizerAndFit(boxSizer);
}
