//
// Created by bailey on 5/27/20.
//

#ifndef GBUSTER_WXPROGRESSPANEL_H
#define GBUSTER_WXPROGRESSPANEL_H

#include <vector>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/gauge.h>
#include <wx/stattext.h>
#include <assert.h>
using range = std::pair<unsigned long long, unsigned long long>;

constexpr const int MAX_RANGE = 1000; // Work with percentages, as long values do not fit

/**
 * This class serves to instantiate a specified amount of progress bars and handles their updating
 */
class wxProgressPanel : public wxPanel {
public:
    // Constructor
    explicit wxProgressPanel(wxWindow* parent) : wxPanel(parent), topSizer(new wxBoxSizer(wxHORIZONTAL)) {}

    // Public methods
    void SetGauges(const std::vector<range>& ranges); // Builds and displays progress bars

    /**
     * @brief Sets the gauge's value @ gaugeIdx to newVal
     * @param gaugeIdx : Index of gauge to be altered
     * @param newVal : Value to update to
     */
    void UpdateGauge(unsigned int gaugeIdx, unsigned long long int newVal);

    /**
     * Set the gauge's value @ gaugeIdx to MAX
     * @param gaugeIdx Index of gauge to alter
     */
    void FillProgressBar(unsigned int gaugeIdx);
private:
    std::vector<range> threadRanges; // Number of hashes each thread must iterate through
    wxVector<wxGauge*> gauges;  // Progress bars for each individual thread
    wxBoxSizer* topSizer;

    constexpr static inline int barPadding = 10;
};

#endif //GBUSTER_WXPROGRESSPANEL_H
