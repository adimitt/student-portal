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

    // Config file is a flat key=value list. Unknown keys are reported and
    // skipped so an older binary can still read a newer config file.
    bool load(const std::string &path);
    bool save(const std::string &path) const;

private:
    static bool parseBool(const std::string &value);

    Settings settings_;
};

#endif
