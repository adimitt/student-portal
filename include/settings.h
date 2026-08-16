#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

// Portal wide preferences. The defaults match the behaviour the portal
// had before settings were configurable, so an absent config file is safe.
struct Settings {
    std::string gradeScale = "ten-point";  // ten-point or strict
    bool roundPercentage = true;
    int decimalPlaces = 2;
    bool showBarChart = true;
};

class SettingsStore {
public:
    const Settings &current() const;
    void apply(const Settings &settings);

    bool usesStrictScale() const;
    void renderCurrent() const;

private:
    Settings settings_;
};

#endif
