//
// Created by bailey on 5/10/20.
//

#include "HashTestPanel.h"

#include <utility>

HashTestPanel::HashTestPanel(wxWindow* parent, const wxString& lbl, std::function<std::string(std::string)> fnc)
: wxPanel(parent)
{
    this->hashFunc = std::move(fnc);

    textBox = new wxTextCtrl(this, -1, wxT("Text to hash:"),
                             wxDefaultPosition, wxSize(450, 40));
    hashOutputLabel = new wxStaticText(this, -1,
                                       "Message Digest: ", wxDefaultPosition, wxSize(450, 100));
    hashButton = new wxButton(this, ID_HASH, lbl, wxDefaultPosition, wxDefaultSize);

    auto *boxSizer = new wxBoxSizer(wxVERTICAL);

    boxSizer->Add(textBox);
    boxSizer->AddSpacer(5);
    boxSizer->Add(hashButton);
    boxSizer->AddSpacer(10);
    boxSizer->Add(hashOutputLabel, 1, wxALL, 10);

    SetSizerAndFit(boxSizer);
}

void HashTestPanel::OnPress(wxCommandEvent &event) {
    std::string cleartext = getTextBoxValue();
    std::string digest = hashFunc(cleartext);
    hashOutputLabel->SetLabel("Message Digest: " + digest);
}

std::string HashTestPanel::getTextBoxValue() {
    return std::string(textBox->GetValue().mbc_str());
}

BEGIN_EVENT_TABLE(HashTestPanel, wxPanel)
    EVT_BUTTON(ID_HASH, HashTestPanel::OnPress)
END_EVENT_TABLE()