//
// Created by bailey on 5/27/20.
//

#include <iostream>
#include "wxProgressPanel.h"

void wxProgressPanel::SetGauges(const std::vector<range> &ranges) {
    threadRanges.resize(ranges.size());
    gauges.resize(ranges.size());

    for (int i = 0; i < ranges.size(); ++i) {
        const auto& range = ranges.at(i);
        this->threadRanges.at(i) = range; // Save each thread's total workload

        // Create gauge and labels
        auto* gaugeSizer = new wxBoxSizer(wxVERTICAL);
        wxString threadLabelText = "\tT" + std::to_string(i);
        auto* threadLabel = new wxStaticText(this, wxID_ANY, threadLabelText);
        gauges.at(i) = new wxGauge(this, wxID_ANY, MAX_RANGE, wxDefaultPosition, wxDefaultSize, wxVERTICAL);
        gaugeSizer->Add(gauges.at(i), 1, wxALIGN_CENTER);
        gaugeSizer->Add(threadLabel, 1, wxALIGN_CENTER);
        // Add to sizer
        topSizer->Add(gaugeSizer, 0, 0, barPadding);
        topSizer->AddSpacer(15); // Add space between each gauge
    }

    SetSizerAndFit(topSizer);
}

void wxProgressPanel::UpdateGauge(unsigned int gaugeIdx, unsigned long long int newVal) {
        assert(gaugeIdx < gauges.size());
        auto range = threadRanges.at(gaugeIdx); // Safely access thread's range
        auto progress = static_cast<unsigned int>((static_cast<double>(newVal) / static_cast<double>((range.second - range.first))) * MAX_RANGE); // Get rounded fraction of completion
        assert(progress >= 0 && progress <= MAX_RANGE); // between 0 and max

        gauges.at(gaugeIdx)->SetValue(progress);
}

void wxProgressPanel::FillProgressBar(unsigned int gaugeIdx) {
    assert(gaugeIdx < gauges.size());
    gauges.at(gaugeIdx)->SetValue(MAX_RANGE);
}
