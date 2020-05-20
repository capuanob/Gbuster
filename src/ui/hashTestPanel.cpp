//
// Created by bailey on 5/10/20.
//

#include "hashTestPanel.h"

hashTestPanel::hashTestPanel(wxWindow* parent, const wxString& lbl, std::function<std::string(std::string)> fnc)
: wxPanel(parent)
{
    this->hashFunc = std::move(fnc);

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

void hashTestPanel::OnPress(wxCommandEvent &event) {
    std::string cleartext = getTextBoxValue();
    std::string digest = hashFunc(cleartext);
    hashOutputLabel->SetLabel("Message Digest: " + digest);
}

std::string hashTestPanel::getTextBoxValue() {
    return std::string(textBox->GetValue().mbc_str());
}

BEGIN_EVENT_TABLE(hashTestPanel, wxPanel)
    EVT_BUTTON(ID_TEST_HASH, hashTestPanel::OnPress)
    EVT_TEXT(ID_HASH_TEXT_BOX, hashTestPanel::OnTextDidChange)
END_EVENT_TABLE()

void hashTestPanel::OnTextDidChange(wxCommandEvent &event) {
    wxString curr_str = event.GetString();

    if (charCount != nullptr) // Creation of textBox emits an EVT_TEXT, have to avoid that
        charCount->SetLabel(std::to_string(curr_str.length()) + " c");
}
